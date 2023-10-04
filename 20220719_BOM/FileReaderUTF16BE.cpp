#include "FileReaderUtf16BE.h"
#include <iostream>

union Be2Le {
	WCHAR p;
	BYTE b[2];
};

CFileReaderUtf16BE::CFileReaderUtf16BE() : CFileReaderBase() {
	m_bom = eBOM::eUTF16BE;
}


BOOL CFileReaderUtf16BE::Open(const TCHAR* file)
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

	// BOM �ڵ� 2����Ʈ ����
	int rlen = s32.st_size - 2;

	// ����� ���ۿ� �ӽ� ���� �Ҵ�
	try {
		m_buffer = new WCHAR[rlen + 1];
	}
	catch (std::bad_alloc ex) {
		if (m_buffer)
			delete[] m_buffer;
		m_buffer = NULL;
		return FALSE;
	}

	// BOM �ڵ� 2����Ʈ �о ������
	if (fread(m_buffer, 1, 2, pf) != 2) {
		if (m_buffer)
			delete[] m_buffer;
		m_buffer = NULL;
		m_buffer_len = 0;
		return FALSE;
	}

	// �ӽ� ���ۿ� ������ �б�
	m_buffer_len = rlen;
	if (fread(m_buffer, 1, m_buffer_len, pf) != m_buffer_len) {
		if (m_buffer)
			delete[] m_buffer;
		m_buffer = NULL;
		m_buffer_len = 0;
		return FALSE;
	}

	// �̰� �״�� �����ڵ��̴�.
	m_buffer_len /= 2;
	m_buffer[m_buffer_len] = 0;

	// ������ �ٲ��ش�.
	Be2Le bl;
	for (UINT i = 0; i < m_buffer_len; i++) {
		bl.p = m_buffer[i];
		BYTE b = bl.b[0];
		bl.b[0] = bl.b[1];
		bl.b[1] = b;
		m_buffer[i] = bl.p;
	}

	_tcscpy_s(m_filepath, MAX_PATH, file);
	fclose(pf);

	return TRUE;
}

BOOL CFileReaderUtf16BE::Write()
{
	return Write(m_filepath);
}

BOOL CFileReaderUtf16BE::Write(const TCHAR* file)
{
	FILE* pf = NULL;
	errno_t err = _tfopen_s(&pf, file, _T("wb"));
	if (err != ERROR_SUCCESS || pf == NULL)
		return FALSE;

	// BOM �ڵ带 ���� ����ش�.
	BYTE bom[2] = { 0xFE, 0xFF };
	fwrite(bom, 1, 2, pf);

	Be2Le bl;
	// ������ �ٽ� ������� �ٲ㼭, 2����Ʈ�� ����ش�.
	// �ƴϸ� ���ο� ���۸� �����, ������ �ٲ۴����� �ѹ��� ���� �� �� �ִ�.
	for (UINT i = 0; i < m_buffer_len; i++) {
		bl.p = m_buffer[i];
		BYTE b = bl.b[0];
		bl.b[0] = bl.b[1];
		bl.b[1] = b;
		fwrite(bl.b, 1, 2, pf);
	}

	fclose(pf);
	return TRUE;
}

