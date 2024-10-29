#include "Columnar.h"
#include <iostream>
#include <string>

int main() {
    int n;
    std::string text;

    std::cout << "Enter text: ";
    std::getline(std::cin, text);

    std::cout << "Enter number: ";
    std::cin >> n;

    ColumnarCipher cipher(n);

    std::string encrypted = cipher.encrypt(text);
    std::cout << "Encrypted text: " << encrypted << std::endl;

    std::string decrypted = cipher.decrypt(encrypted);
    std::cout << "Decrypted text: " << decrypted << std::endl;

    return 0;
}