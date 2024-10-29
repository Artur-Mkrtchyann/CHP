#include <stddef.h>
#include "Caesar.h"
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>

Caesar::Caesar() : mArrSize(0), mShift(3)
{
}

Caesar::~Caesar()
{
}

unsigned char Caesar::ShiftChar(unsigned char ch, int shift)
{
    if (ch >= 'A' && ch <= 'Z')
    {
        return 'A' + (ch - 'A' + shift + 26) % 26;
    }
    else if (ch >= 'a' && ch <= 'z')
    {
        return 'a' + (ch - 'a' + shift + 26) % 26;
    }
    else
    {
        return ch;
    }
}

int Caesar::Encrypt(const unsigned char* psource, unsigned int sourcesize, unsigned char* pout, unsigned int& outsize)
{
    if (!psource || !pout || !sourcesize || outsize < sourcesize)
        return -1;

    for (unsigned int i = 0; i < sourcesize; ++i)
    {
        pout[i] = ShiftChar(psource[i], mShift);
    }

    outsize = sourcesize;
    return 0;
}

int Caesar::Decrypt(const unsigned char* psource, unsigned int sourcesize, unsigned char* pout, unsigned int& outsize)
{
    if (!psource || !pout || !sourcesize || outsize < sourcesize)
        return -1;

    for (unsigned int i = 0; i < sourcesize; ++i)
    {
        pout[i] = ShiftChar(psource[i], -mShift);
    }

    outsize = sourcesize;
    return 0;
}

void Caesar::SetShift(int shift)
{
    mShift = shift % 26;
}

void Caesar::PrintData(const unsigned char* data, unsigned int size)
{
    for (unsigned int i = 0; i < size; ++i)
    {
        std::cout << data[i];
    }
    std::cout << std::endl;
}
