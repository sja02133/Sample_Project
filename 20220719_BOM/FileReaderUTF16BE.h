#pragma once
#include "FileReaderBase.h"

class CFileReaderUtf16BE : public CFileReaderBase
{
public:
    CFileReaderUtf16BE();

    virtual BOOL Open(const TCHAR* file);
    virtual BOOL Write();
    virtual BOOL Write(const TCHAR* file);
};

