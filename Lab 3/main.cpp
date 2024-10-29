#include "Caesar.h"
#include <string.h>
#include <iostream>
#include <algorithm>
#include <random>
#include <cstring>

using namespace std;

#define BUF_SIZE  1024

int main()
{
    Caesar cipher;
    cipher.SetShift(4);

    const char* message = "Hello, World! 123";
    unsigned int size = std::strlen(message);
    unsigned char encrypted[100] = {0};
    unsigned char decrypted[100] = {0};
    unsigned int outsize = size;

    cipher.Encrypt((const unsigned char*)message, size, encrypted, outsize);
    std::cout << "Encrypted: ";
    cipher.PrintData(encrypted, outsize);

    cipher.Decrypt(encrypted, outsize, decrypted, outsize);
    std::cout << "Decrypted: ";
    cipher.PrintData(decrypted, outsize);

    return 0;
}
