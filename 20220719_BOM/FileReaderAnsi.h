#pragma once
#include "FileReaderBase.h"

class CFileReaderAnsi : public CFileReaderBase
{
public:
    CFileReaderAnsi();

    virtual BOOL Open(const TCHAR* file);
    virtual BOOL Write();
    virtual BOOL Write(const TCHAR* file);
};

