#include "FileReaderAnsi.h"
#include <iostream>

CFileReaderAnsi::CFileReaderAnsi() : CFileReaderBase() {
	m_bom = eBOM::eNoneBom;
}


BOOL CFileReaderAnsi::Open(const TCHAR* file)
{
	// ���� ũ�� ���
	struct _stat s32 = { 0 };
	if (_tstat(file, &s32) != ERROR_SUCCESS)
		return FALSE;
	Close();

	// ���� ����
	FILE* pf = NULL;
	errno_t err = _tfopen_s(&pf, file, _T("rb"));
	if (err != ERROR_SUCCESS || pf == NULL)
		return FALSE;

	// ����� ���ۿ� �ӽ� ���� �Ҵ�
	BYTE* temp = NULL;
	try {
		m_buffer = new WCHAR[s32.st_size + 1];
		temp = new BYTE[s32.st_size + 1];
	}
	catch (std::bad_alloc ex) {
		if (m_buffer)
			delete[] m_buffer;
		m_buffer = NULL;

		if (temp)
			delete[] temp;
		return FALSE;
	}

	// �ӽ� ���ۿ� ������ �б�
	m_buffer_len = s32.st_size;
	if (fread(temp, 1, m_buffer_len, pf) != m_buffer_len) {
		if (m_buffer)
			delete[] m_buffer;
		m_buffer = NULL;
		m_buffer_len = 0;
		return FALSE;
	}
	temp[m_buffer_len] = 0;

	// �����ڵ�� ��ȯ�Ͽ� ����.
	m_buffer_len = ::MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, (LPCCH)temp, m_buffer_len, m_buffer, m_buffer_len);
	m_buffer[m_buffer_len] = 0;
	_tcscpy_s(m_filepath, MAX_PATH, file);
	fclose(pf);

	delete[] temp;
	return TRUE;
}

BOOL CFileReaderAnsi::Write()
{
	return Write(m_filepath);
}

BOOL CFileReaderAnsi::Write(const TCHAR* file)
{
	FILE* pf = NULL;
	errno_t err = _tfopen_s(&pf, file, _T("w"));
	if (err != ERROR_SUCCESS || pf == NULL)
		return FALSE;

	CW2A temp(m_buffer);
	fwrite(temp, 1, strlen(temp), pf);
	fclose(pf);
	return TRUE;
}

