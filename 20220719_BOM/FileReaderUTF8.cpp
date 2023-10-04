#include "FileReaderUtf8.h"
#include <iostream>

CFileReaderUtf8::CFileReaderUtf8() : CFileReaderBase() {
	m_bom = eBOM::eUTF8;
}


BOOL CFileReaderUtf8::Open(const TCHAR* file)
{
	// 파일 크기 계산
	struct _stat s32 = { 0 };
	if (_tstat(file, &s32) != ERROR_SUCCESS)
		return FALSE;
	Close();

	// 파일 열기
	FILE* pf = NULL;
	errno_t err = _tfopen_s(&pf, file, _T("rb"));
	if (err != ERROR_SUCCESS || pf == NULL)
		return FALSE;

	// BOM 코드 3바이트 제거
	int rlen = s32.st_size - 3;

	// 사용할 버퍼와 임시 버퍼 할당
	BYTE* temp = NULL;
	try {
		m_buffer = new WCHAR[rlen + 1];
		temp = new BYTE[rlen + 1];
	}
	catch (std::bad_alloc ex) {
		if (m_buffer)
			delete[] m_buffer;
		m_buffer = NULL;

		if (temp)
			delete[] temp;
		return FALSE;
	}

	// BOM 코드 3바이트 읽어서 버리기
	if (fread(temp, 1, 3, pf) != 3) {
		if (m_buffer)
			delete[] m_buffer;
		m_buffer = NULL;

		if (temp)
			delete[] temp;
		m_buffer_len = 0;
		return FALSE;
	}

	// 임시 버퍼에 데이터 읽기
	m_buffer_len = rlen;
	if (fread(temp, 1, m_buffer_len, pf) != m_buffer_len) {
		if (m_buffer)
			delete[] m_buffer;
		m_buffer = NULL;
		m_buffer_len = 0;
		return FALSE;
	}
	temp[m_buffer_len] = 0;

	// 유니코드로 변환하여 저장.
	m_buffer_len = ::MultiByteToWideChar(CP_UTF8, MB_PRECOMPOSED, (LPCCH)temp, m_buffer_len, m_buffer, m_buffer_len);
	m_buffer[m_buffer_len] = 0;
	_tcscpy_s(m_filepath, MAX_PATH, file);
	fclose(pf);

	delete[] temp;
	return TRUE;
}

BOOL CFileReaderUtf8::Write()
{
	return Write(m_filepath);
}

BOOL CFileReaderUtf8::Write(const TCHAR* file)
{
	FILE* pf = NULL;
	errno_t err = _tfopen_s(&pf, file, _T("w, ccs=UTF-8"));
	if (err != ERROR_SUCCESS || pf == NULL)
		return FALSE;

	fwrite(m_buffer, 1, m_buffer_len*2, pf);
	fclose(pf);
	return TRUE;
}

