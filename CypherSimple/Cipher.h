#ifndef CIPHER_H
#define CIPHER_H

#include <string>

class Cipher {
public:
    std::string makeKey();

    std::string encrypt(const std::string& str, const std::string& key);

    std::string decrypt(const std::string& str, const std::string& key);

    bool checking(const std::string& str1, const std::string& str2);
};

#endif