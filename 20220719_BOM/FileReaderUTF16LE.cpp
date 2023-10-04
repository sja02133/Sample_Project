#include "FileReaderUtf16LE.h"
#include <iostream>

CFileReaderUtf16LE::CFileReaderUtf16LE() : CFileReaderBase() {
	m_bom = eBOM::eUTF16LE;
}


BOOL CFileReaderUtf16LE::Open(const TCHAR* file)
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

	// BOM 코드 2바이트 제거
	int rlen = s32.st_size - 2;

	// 사용할 버퍼와 임시 버퍼 할당
	try {
		m_buffer = new WCHAR[rlen + 1];
	}
	catch (std::bad_alloc ex) {
		if (m_buffer)
			delete[] m_buffer;
		m_buffer = NULL;
		return FALSE;
	}

	// BOM 코드 2바이트 읽어서 버리기
	if (fread(m_buffer, 1, 2, pf) != 2) {
		if (m_buffer)
			delete[] m_buffer;
		m_buffer = NULL;
		m_buffer_len = 0;
		return FALSE;
	}

	// 임시 버퍼에 데이터 읽기
	m_buffer_len = rlen;
	if (fread(m_buffer, 1, m_buffer_len, pf) != m_buffer_len) {
		if (m_buffer)
			delete[] m_buffer;
		m_buffer = NULL;
		m_buffer_len = 0;
		return FALSE;
	}

	// 이건 그대로 유니코드이다.
	m_buffer_len /= 2;
	m_buffer[m_buffer_len] = 0;
	_tcscpy_s(m_filepath, MAX_PATH, file);
	fclose(pf);

	return TRUE;
}

BOOL CFileReaderUtf16LE::Write()
{
	return Write(m_filepath);
}

BOOL CFileReaderUtf16LE::Write(const TCHAR* file)
{
	FILE* pf = NULL;
	errno_t err = _tfopen_s(&pf, file, _T("w, ccs=UNICODE"));
	if (err != ERROR_SUCCESS || pf == NULL)
		return FALSE;

	fwrite(m_buffer, 1, m_buffer_len * 2, pf);
	fclose(pf);
	return TRUE;
}

