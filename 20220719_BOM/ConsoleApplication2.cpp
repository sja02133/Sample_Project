// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ConsoleApplication2.h"
#include "FileReaderAnsi.h"
#include "FileReaderUtf8.h"
#include "FileReaderUtf16LE.h"
#include "FileReaderUtf16BE.h"


#define FILE_FOLDER	_T(".\\AAA")

const TCHAR FILE_NAME[4][MAX_PATH] = {
	_T("A1.txt"),
	_T("A2.txt"),
	_T("A3.txt"),
	_T("A4.txt")
};

int main()
{
	for (int i = 0; i < 4; i++)
	{
		eBOM bom = eBOM::eNoneBom;
		CString fname = FILE_FOLDER;
		fname += _T("\\");
		fname += FILE_NAME[i];

		if (!GetBomType(fname, bom))
			continue;

		CString answer = _T("\n내 이름은 XXX입니다.");
		CFileReaderBase* base = NULL;

		switch (bom) {
		case eBOM::eNoneBom:
			base = new CFileReaderAnsi;
			break;
		case eBOM::eUTF8:
			base = new CFileReaderUtf8;
			break;
		case eBOM::eUTF16LE:
			base = new CFileReaderUtf16LE;
			break;
		case eBOM::eUTF16BE:
			base = new CFileReaderUtf16BE;
			break;
		default:
			continue;
		}

		base->Open(fname);
		base->AddBuffer((WCHAR*)(LPCWSTR)answer);

		switch (bom) {
		case eBOM::eNoneBom:
			base->AddBuffer((WCHAR*)L"\nAnsi");
			break;
		case eBOM::eUTF8:
			base->AddBuffer((WCHAR*)L"\nUtf8");
			break;
		case eBOM::eUTF16LE:
			base->AddBuffer((WCHAR*)L"\nUtf16LE");
			break;
		case eBOM::eUTF16BE:
			base->AddBuffer((WCHAR*)L"\nUtf16BE");
			break;
		default:
			continue;
		}

		fname = fname.Left(fname.GetLength() - 4);
		fname += _T("_1.txt");
		base->Write(fname);

		delete base;
	}

	return 0;
}


// BOM 타입을 검출하는 함수
BOOL GetBomType(const TCHAR* filepath, eBOM& bom)
{
	BYTE b[3] = { 0 };
	size_t len = 0;
	FILE* pf = NULL;
	bom = eBOM::eNoneBom;
	errno_t err = _tfopen_s(&pf, filepath, _T("rb"));
	if (err != ERROR_SUCCESS)
		goto RETURN_FALSE;

	if(pf == NULL)
		goto RETURN_FALSE;

	len = fread(b, 1, 3, pf);
	if (len < 2)
		goto RETURN_FALSE;
	else if (len == 2) {
		if (b[0] == 0xFE && b[1] == 0xFF)
			bom = eBOM::eUTF16BE;
		else if (b[0] == 0xFF && b[1] == 0xFE)
			bom = eBOM::eUTF16LE;
	}
	else {
		if (b[0] == 0xEF && b[1] == 0xBB && b[2] == 0xBF)
			bom = eBOM::eUTF8;
		else if (b[0] == 0xFE && b[1] == 0xFF)
			bom = eBOM::eUTF16BE;
		else if (b[0] == 0xFF && b[1] == 0xFE)
			bom = eBOM::eUTF16LE;
	}

	if (pf)
		fclose(pf);
	return TRUE;

RETURN_FALSE:
	if (pf)
		fclose(pf);
	return FALSE;
}