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
	// �����ڵ带 console �� ����Ϸ��� ��� ��带 �ٲپ� �־�� �Ѵ�.
	// https://stackoverflow.com/questions/12015571/how-to-print-unicode-character-in-c
	_setmode(_fileno(stdout), _O_U16TEXT);

	// ���� ��θ� �о�ͼ�, �Ϻ� AAA ��� ���ϱ�
	TCHAR path[MAX_PATH] = { 0 };
	::GetCurrentDirectory(MAX_PATH, path);
	_tcscat_s(path, MAX_PATH, _T("\\AAA"));

	// ��� ����ϱ� ��������, ���� ��θ� AAA ������ ����
	::SetCurrentDirectory(path);

	// �Ϻ� ��ο� �ִ� �̹��� ���� ��� ��������
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
			// sndPlaySound �� �̿��� ���
			sndPlaySound(wfd.cFileName, SND_SYNC);
#elif 0
			// PlaySound �� �̿��� ���
			PlaySound(wfd.cFileName, NULL,  SND_SYNC);
#elif 1
			// mciSendString �� �̿��� ���
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
			// DirectShow �� �̿��� ���
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
