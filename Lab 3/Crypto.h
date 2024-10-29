#pragma once

#ifndef CRYPTO_H
#define CRYPTO_H

class Crypto {

public: 
	virtual	int Encrypt(const unsigned char* pSrc, unsigned int SrcSz, unsigned char* pOut, unsigned int& Outsz)=0;
	virtual	int Decrypt(const unsigned char* pSrc, unsigned int SrcSz, unsigned char* pOut, unsigned int& Outsz)=0;
};

#endif
