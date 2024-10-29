#include "RLE.h"
#include <sstream>
#include <cctype>

std::string RLE::compress(const std::string& input) {
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

std::string RLE::decompress(const std::string& input) {
    std::stringstream result;

    for (size_t i = 0; i < input.size(); i += 2) {
        char ch = input[i];
        int count = (char)input[i + 1];

        result << std::string(count, ch);
    }

    return result.str();
}