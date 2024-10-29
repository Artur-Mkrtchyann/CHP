#include "Cipher.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>

std::string Cipher::makeKey() {
    std::string alph = "abcdefghijklmnopqrstuvwxyz";
    std::string key = alph;

    srand(time(0));

    for (int i = key.length() - 1; i >= 0; i--) {
        int j = rand() % (i + 1);
        std::swap(key[i], key[j]);
    }

    return key;
}

std::string Cipher::encrypt(const std::string& str, const std::string& key) {
    std::string encryptedStr = str;

    for (int i = 0; i < encryptedStr.length(); i++) {
        if (encryptedStr[i] >= 'a' && encryptedStr[i] <= 'z') {
            int keyInd = (int)encryptedStr[i] - 'a';
            encryptedStr[i] = key[keyInd];
        }
    }

    return encryptedStr;
}

std::string Cipher::decrypt(const std::string& str, const std::string& key) {
    std::string decryptedStr = "";
    std::string alph = "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < str.length(); i++) {
        if (str[i] == ' ') {
            decryptedStr += ' ';
        } else {
            auto it = std::find(key.begin(), key.end(), str[i]);
            if (it != key.end()) {
                int index = std::distance(key.begin(), it);
                decryptedStr += alph[index];
            }
        }
    }

    return decryptedStr;
}

bool Cipher::checking(const std::string& str1, const std::string& str2) {
    return str1 == str2;
}