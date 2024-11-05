#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <algorithm>


class Caesar {
public:
    Caesar() : mShift(3) {}
    ~Caesar() {}

    void SetShift(int shift) {
        mShift = shift % 26;
    }

    int Encrypt(const unsigned char* pSrc, unsigned int SrcSz, unsigned char* pOut, unsigned int& OutSz) {
        if (!pSrc || !pOut || !SrcSz || OutSz < SrcSz)
            return -1;

        for (unsigned int i = 0; i < SrcSz; ++i) {
            pOut[i] = ShiftChar(pSrc[i], mShift);
        }

        OutSz = SrcSz;
        return 0;
    }

    int Decrypt(const unsigned char* pSrc, unsigned int SrcSz, unsigned char* pOut, unsigned int& OutSz) {
        if (!pSrc || !pOut || !SrcSz || OutSz < SrcSz)
            return -1;

        for (unsigned int i = 0; i < SrcSz; ++i) {
            pOut[i] = ShiftChar(pSrc[i], -mShift);
        }

        OutSz = SrcSz;
        return 0;
    }

private:
    unsigned char ShiftChar(unsigned char ch, int shift) {
        if (ch >= 'A' && ch <= 'Z') {
            return 'A' + (ch - 'A' + shift + 26) % 26;
        } else if (ch >= 'a' && ch <= 'z') {
            return 'a' + (ch - 'a' + shift + 26) % 26;
        } else {
            return ch;
        }
    }

    int mShift;
};

// --- Run-Length Encoding (RLE) ---
class RLE {
public:
    std::string compress(const std::string& input) {
        std::stringstream result;
        int count = 1;

        for (size_t i = 1; i <= input.size(); ++i) {
            if (i < input.size() && input[i] == input[i - 1]) {
                ++count;
            } else {
                result << input[i - 1];
                result << (char)count;
                count = 1;
            }
        }

        return result.str();
    }

    std::string decompress(const std::string& input) {
        std::stringstream result;

        for (size_t i = 0; i < input.size(); i += 2) {
            char ch = input[i];
            int count = (char)input[i + 1];

            result << std::string(count, ch);
        }

        return result.str();
    }
};

int main() {
    Caesar cipher;
    RLE rle;
    std::string input;

    // Step 1: Input the original message
    std::cout << "Enter text to encrypt and compress: ";
    std::getline(std::cin, input);

    // Step 2: Caesar encryption
    unsigned int size = input.size();
    unsigned char encrypted[100] = {0};
    unsigned int outsize = size;
    cipher.SetShift(4);

    cipher.Encrypt((const unsigned char*)input.c_str(), size, encrypted, outsize);

    std::string encryptedStr((char*)encrypted, outsize);
    std::cout << "Encrypted with Caesar Cipher: " << encryptedStr << std::endl;

    // Step 3: RLE compression
    std::string compressed = rle.compress(encryptedStr);
    std::cout << "Compressed with RLE: " << compressed << std::endl;

    // Step 4: RLE decompression
    std::string decompressed = rle.decompress(compressed);
    std::cout << "Decompressed from RLE: " << decompressed << std::endl;

    // Step 5: Caesar decryption
    unsigned char decrypted[100] = {0};
    outsize = decompressed.size();
    cipher.Decrypt((const unsigned char*)decompressed.c_str(), outsize, decrypted, outsize);

    std::string finalDecrypted((char*)decrypted, outsize);
    std::cout << "Decrypted with Caesar Cipher: " << finalDecrypted << std::endl;

    // Verify if the decrypted text matches the original input
    if (input == finalDecrypted) {
        std::cout << "Success:!" << std::endl;
    } else {
        std::cout << "Error:!" << std::endl;
    }

    return 0;
}
