#pragma once
#include "FileReaderBase.h"

class CFileReaderUtf8 : public CFileReaderBase
{
public:
    CFileReaderUtf8();

    virtual BOOL Open(const TCHAR* file);
    virtual BOOL Write();
    virtual BOOL Write(const TCHAR* file);
};

