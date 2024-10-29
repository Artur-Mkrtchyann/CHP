#pragma once

#ifndef SHABLON_H
#define SHABLON_H

#include <stddef.h>

const unsigned int TemplateSize = 256;

class Caesar
{
public:
    Caesar();
    virtual ~Caesar();

    virtual int Encrypt(const unsigned char* pSrc, unsigned int SrcSz, unsigned char* pOut, unsigned int& OutSz);

    virtual int Decrypt(const unsigned char* pSrc, unsigned int SrcSz, unsigned char* pOut, unsigned int& OutSz);

    void SetShift(int shift);

    void PrintData(const unsigned char* data, unsigned int size);

private:
    unsigned char ShiftChar(unsigned char ch, int shift);

    int mShift;
    size_t mArrSize;
};

#endif
