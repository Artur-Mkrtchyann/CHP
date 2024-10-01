#include <iostream>
#include <cstring>
#include <algorithm>
#include <random>
#include <string>

const unsigned int TemplateSize = 256;

class Crypto {
public:
    virtual int Encrypt(const unsigned char* pSrc, unsigned int SrcSz, unsigned char* pOut, unsigned int& Outsz) = 0;
    virtual int Decrypt(const unsigned char* pSrc, unsigned int SrcSz, unsigned char* pOut, unsigned int& Outsz) = 0;
};

class Shablon : public Crypto {
public:
    Shablon();
    virtual ~Shablon();

    virtual int Encrypt(const unsigned char* pSrc, unsigned int SrcSz, unsigned char* pOut, unsigned int& Outsz);
    virtual int Decrypt(const unsigned char* pSrc, unsigned int SrcSz, unsigned char* pOut, unsigned int& Outsz);

    int SetTemplateTable(const unsigned char* pEncodeArr, const unsigned char* pDecodeArr, size_t size);

private:
    unsigned char mEncryptTable[2][TemplateSize];
    unsigned char mDecryptTable[2][TemplateSize];
    size_t mArrSize;
};

Shablon::Shablon() : mArrSize(0) {
    std::memset(mEncryptTable, 0, sizeof(mEncryptTable));
    std::memset(mDecryptTable, 0, sizeof(mDecryptTable));
}

Shablon::~Shablon() {}

int Shablon::Encrypt(const unsigned char* psource, unsigned int sourcesize, unsigned char* pout, unsigned int& outsize) {
    if (!psource || !pout || !sourcesize || outsize < sourcesize)
        return -1;

    for (unsigned int i = 0; i < sourcesize; ++i) {
        pout[i] = mEncryptTable[1][psource[i]];
    }
    return 0;
}

int Shablon::Decrypt(const unsigned char* psource, unsigned int sourcesize, unsigned char* pout, unsigned int& outsize) {
    if (!psource || !pout || !sourcesize || outsize < sourcesize)
        return -1;

    for (unsigned int i = 0; i < sourcesize; ++i) {
        pout[i] = mDecryptTable[1][psource[i]];
    }
    return 0;
}

int Shablon::SetTemplateTable(const unsigned char* pEncodeArr, const unsigned char* pDecodeArr, size_t size) {
    if (!pEncodeArr || !pDecodeArr || size != TemplateSize)
        return -1;

    std::memcpy(mEncryptTable[0], pEncodeArr, size);
    std::memcpy(mEncryptTable[1], pDecodeArr, size);

    std::memcpy(mDecryptTable[0], mEncryptTable[1], size);
    std::memcpy(mDecryptTable[1], mEncryptTable[0], size);

    unsigned int i, j;

    for (i = 0; i < size; ++i) {
        for (j = i; j < size; ++j) {
            if (i == mDecryptTable[0][j])
                break;
        }
        if (j != i) {
            std::swap(mDecryptTable[0][j], mDecryptTable[0][i]);
            std::swap(mDecryptTable[1][j], mDecryptTable[1][i]);
        }
    }
    mArrSize = size;

    return 0;
}

unsigned char encode_arr[TemplateSize];
unsigned char decode_arr[TemplateSize];

int InitTemplateKeytable(unsigned char* enc_arr, unsigned char* dec_arr, unsigned int TemplateSize) {
    if (!enc_arr || !dec_arr || !TemplateSize)
        return -1;

    for (unsigned int i = 0; i < TemplateSize; ++i) {
        dec_arr[i] = enc_arr[i] = i; // Identity mapping
    }

    // Shuffle the decode array
    unsigned seed = std::random_device{}(); // Use a random device for seeding
    std::shuffle(dec_arr, dec_arr + TemplateSize, std::default_random_engine(seed));

    return 0;
}

int main() {
    unsigned char src[1024], dest[1024], decrypt[1024];

    std::string str("Artur");
    unsigned int size = (unsigned int)str.size();

    std::strcpy((char*)src, str.c_str());

    std::cout << "Text to encrypt:\n" << src << std::endl;

    InitTemplateKeytable(encode_arr, decode_arr, TemplateSize);

    Shablon obj;

    obj.SetTemplateTable(encode_arr, decode_arr, TemplateSize);

    unsigned int encSize = size;
    if (obj.Encrypt(src, size, dest, encSize)) {
        std::cout << "Failed to Encrypt...\n";
        return -1;
    }

    dest[encSize] = '\0'; // Null-terminate the encrypted string
    std::cout << "Encrypted text:\n" << dest << std::endl;

    unsigned int decSize = size;
    if (obj.Decrypt(dest, encSize, decrypt, decSize)) {
        std::cout << "Failed to Decrypt...\n";
        return -2;
    }

    decrypt[decSize] = '\0'; // Null-terminate the decrypted string
    std::cout << "Decrypted text:\n" << decrypt << std::endl;

    if (std::strcmp((const char*)src, (const char*)decrypt)) {
        std::cout << "Failed" << std::endl;
    } else {
        std::cout << "Success" << std::endl;
    }

    return 0;
}
