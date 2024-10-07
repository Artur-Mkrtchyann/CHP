#pragma once

// Abstract base class for crypto classes.
 
class Crypto {

public: 
	virtual	int Encrypt(const unsigned char* pSrc, unsigned int SrcSz, unsigned char* pOut, unsigned int& Outsz)=0;
	virtual	int Decrypt(const unsigned char* pSrc, unsigned int SrcSz, unsigned char* pOut, unsigned int& Outsz)=0;

};