#include <stddef.h>
#include "Cesar.h"
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>

Cesar::Cesar() : mArrSize(0)
{
}

Cesar::~Cesar()
{
}

int Cesar::Encrypt(const unsigned char* psource, unsigned int sourcesize, unsigned char* pout, unsigned int& outsize)
{
	if (!psource || !pout || !sourcesize || !outsize || outsize< sourcesize)
		return -1;

	for (unsigned int i = 0; i < sourcesize; ++i)
	{
		pout[i] = mEncryptTable[1][ psource[i] ];
	}
	return 0;
}

int Cesar::Decrypt(const unsigned char* psource, unsigned int sourcesize, unsigned char* pout, unsigned int& outsize)
{
	if (!psource || !pout || !sourcesize || !outsize || outsize < sourcesize)
		return -1;

	for (unsigned int i = 0; i < sourcesize; ++i)
	{
		pout[i] = mDecryptTable[1][ psource[i] ];
	}
	return 0;
}

int Cesar::SetTemplateTable(const unsigned char* pEncodeArr, const unsigned char* pDecodeArr, size_t size)
{
	if (!pEncodeArr || !pDecodeArr || !size)
		return -1;

	std::memcpy(mEncryptTable[0], pEncodeArr, size);
	std::memcpy(mEncryptTable[1], pDecodeArr, size);

	std::memcpy(mDecryptTable[0], mEncryptTable[1], size);
	std::memcpy(mDecryptTable[1], mEncryptTable[0], size);

	unsigned int i, j;

	for (i = 0; i < size; ++i)
	{
		for (j = i; j < size; ++j)
		{
			if (i == mDecryptTable[0][j])
				break;
		}
		if (j != i)
		{
			std::swap(mDecryptTable[0][j], mDecryptTable[0][i]);
			std::swap(mDecryptTable[1][j], mDecryptTable[1][i]);
		}
	}
	mArrSize = size;

/****
	std::cout << "\n\nSetTemplateTable\n\n";
	for (i = 0; i < TemplateSize; ++i)
	{
		std::cout << (unsigned int)mDecryptTable[0][i] << ' ';
	}

	std::cout << "\n\nSetTemplateTable second\n\n";

	for (i = 0; i < TemplateSize; ++i)
	{
		std::cout << (unsigned int)mDecryptTable[1][i] << ' ';
	}

	std::cout << "\n\nSetTemplateTable end\n\n";
*****/

	return 0;
}