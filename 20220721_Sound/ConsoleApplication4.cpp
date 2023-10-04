// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <atlstr.h>

#include <mmsystem.h>
#pragma comment (lib, "winmm.lib")

#include <dshow.h>
#include <cstdio>
#pragma comment(lib, "strmiids.lib") 

#include <vector>
#include <io.h>
#include <fcntl.h>
#define FILE_FOLDER	_T(".\\AAA")

#include "ConsoleApplication4.h"

int PrintMciError(int err) {
	if (err == 0)
		return 0;
	TCHAR str[MAX_PATH] = { 0 };
	mciGetErrorString(err, str, MAX_PATH);
	_tprintf(_T("mci error> %s\n"), str);

	return err;
}

int main()
{
	// 유니코드를 console 에 출력하려면 출력 모드를 바꾸어 주어야 한다.
	// https://stackoverflow.com/questions/12015571/how-to-print-unicode-character-in-c
	_setmode(_fileno(stdout), _O_U16TEXT);

	// 현재 경로를 읽어와서, 하부 AAA 경로 더하기
	TCHAR path[MAX_PATH] = { 0 };
	::GetCurrentDirectory(MAX_PATH, path);
	_tcscat_s(path, MAX_PATH, _T("\\AAA"));

	// 경로 계산하기 귀찬으니, 현재 경로를 AAA 폴더로 변경
	::SetCurrentDirectory(path);

	// 하부 경로에 있는 이미지 파일 목록 가져오기
	std::vector<CString> sounds;
	WIN32_FIND_DATA wfd;

	CString savepath = path;
	savepath += _T("\\");

	_tcscat_s(path, MAX_PATH, _T("\\*.*"));
	
	HANDLE handle = ::FindFirstFile(path, &wfd);
	if (handle)
	{
		while (::FindNextFile(handle, &wfd))
		{
			if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				continue;

			CString ful = savepath + wfd.cFileName;

#if 0
			// sndPlaySound 를 이용한 방식
			sndPlaySound(wfd.cFileName, SND_SYNC);
#elif 0
			// PlaySound 를 이용한 방식
			PlaySound(wfd.cFileName, NULL,  SND_SYNC);
#elif 1
			// mciSendString 를 이용한 방식
			// https://stackoverflow.com/questions/57237134/issue-when-trying-to-play-mp3-file-via-mcisendstring-mcierr-cannot-load-driver
			// http://www.codecguide.com/configuration_tips.htm?version=1710
			// https://docs.microsoft.com/ko-kr/windows/win32/multimedia/sending-a-command
			CString command;
			command.Format(_T("open \"%s\" type mpegvideo alias MediaFile"), (LPTSTR)(LPCTSTR)ful);
			if (PrintMciError(mciSendString(command, NULL, 0, 0)) == ERROR_SUCCESS) {
				_tprintf(_T("Play : %s\n"), (LPTSTR)(LPCTSTR)ful);

				// command.Format(_T("play MediaFile wait"));
				command.Format(_T("play MediaFile from 1 to 3000 wait"));
				if (PrintMciError(mciSendString(command, NULL, 0, 0)) == ERROR_SUCCESS) {
				
					command.Format(_T("stop MediaFile"));
					PrintMciError(mciSendString(command, NULL, 0, 0));
				}
				
				command.Format(_T("close MediaFile"));
				PrintMciError(mciSendString(command, NULL, 0, 0));
			}

#elif 1
			// DirectShow 를 이용한 방식
			// https://cplusplus.com/forum/windows/114060/
			IGraphBuilder* pGraph = NULL;
			IMediaControl* pControl = NULL;
			IMediaEvent* pEvent = NULL;

			// Initialize the COM library.
			HRESULT hr = ::CoInitialize(NULL);
			if (FAILED(hr))
			{
				::printf("ERROR - Could not initialize COM library");
				return 0;
			}

			// Create the filter graph manager and query for interfaces.
			hr = ::CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
				IID_IGraphBuilder, (void**)&pGraph);
			if (FAILED(hr))
			{
				::printf("ERROR - Could not create the Filter Graph Manager.");
				return 0;
			}

			hr = pGraph->QueryInterface(IID_IMediaControl, (void**)&pControl);
			hr = pGraph->QueryInterface(IID_IMediaEvent, (void**)&pEvent);

			// Build the graph.
			hr = pGraph->RenderFile((LPTSTR)(LPCTSTR)ful, NULL);
			if (SUCCEEDED(hr))
			{
				// Run the graph.
				hr = pControl->Run();
				if (SUCCEEDED(hr))
				{
					// Wait for completion.
					long evCode;
					_tprintf(_T("Play : %s\n"), (LPTSTR)(LPCTSTR)ful);
					pEvent->WaitForCompletion(INFINITE, &evCode);

					// Note: Do not use INFINITE in a real application, because it
					// can block indefinitely.
				}
			}
			// Clean up in reverse order.
			pEvent->Release();
			pControl->Release();
			pGraph->Release();
			::CoUninitialize();
#endif
		}
		FindClose(handle);
	}

	return 0;
}
