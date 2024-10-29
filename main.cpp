#include "RLE.h"
#include <iostream>
#include <string>

int main() {
    RLE rle;
    std::string input;

    std::cout << "Enter text to compress: ";
    std::getline(std::cin, input);

    std::string compressed = rle.compress(input);
    std::cout << "Compressed text: " << compressed << std::endl;

    std::string decompressed = rle.decompress(compressed);
    std::cout << "Decompressed text: " << decompressed << std::endl;

    if (input == decompressed) {
        std::cout << "Success: Original and decompressed texts match!" << std::endl;
    } else {
        std::cout << "Error: Original and decompressed texts do not match!" << std::endl;
    }

    return 0;
}