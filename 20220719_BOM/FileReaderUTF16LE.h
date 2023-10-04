#pragma once
#include "FileReaderBase.h"

class CFileReaderUtf16LE : public CFileReaderBase
{
public:
    CFileReaderUtf16LE();

    virtual BOOL Open(const TCHAR* file);
    virtual BOOL Write();
    virtual BOOL Write(const TCHAR* file);
};

