#ifndef COLUMNARCIPHER_H
#define COLUMNARCIPHER_H

#include <vector>
#include <string>

class ColumnarCipher {
public:
    ColumnarCipher(int n);

    std::string encrypt(const std::string& text);
    std::string decrypt(const std::string& text);

private:
    int n;

    std::vector<std::vector<char>> generateKey(const std::string& text);
    std::vector<std::vector<char>> generateDecryptKey(const std::string& text);
};

#endif