#include "FileReaderBase.h"
#include <iostream>

CFileReaderBase::CFileReaderBase() 
{ 
    Init(); 
}

CFileReaderBase::~CFileReaderBase() 
{ 
    Close();
}

void CFileReaderBase::Close() 
{
    if (m_buffer)
        delete[] m_buffer;
    Init();
}

const WCHAR* CFileReaderBase::GetBuffer(UINT& len) 
{
    len = m_buffer_len;
    return m_buffer;
}

void CFileReaderBase::Init() 
{
    m_bom = eBOM::eNoneBom;
    m_buffer = NULL;
    m_buffer_len = 0;
    m_filepath[0] = 0;
}

BOOL CFileReaderBase::AddBuffer(WCHAR* data) 
{
    if (data == NULL || data[0] == 0)
		return TRUE;

	size_t len = wcslen(data);
	size_t newlen = m_buffer_len + len + 1;
	WCHAR* newbuf = m_buffer;
	try {
		m_buffer = new WCHAR[newlen];
	}
    catch (std::bad_alloc ex) {
        m_buffer = newbuf;
        return FALSE;
    }

    memcpy(m_buffer, newbuf, m_buffer_len * sizeof(WCHAR));
    memcpy(&m_buffer[m_buffer_len], data, len * sizeof(WCHAR));
    m_buffer_len = m_buffer_len + (UINT)len;
    m_buffer[m_buffer_len] = 0;

    delete[] newbuf;
    return TRUE;
}

void CFileReaderBase::Print()
{
    if (m_buffer_len == 0)
        return;

    wprintf(L"%s\n", m_buffer);
}
