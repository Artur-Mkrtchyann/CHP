#ifndef RLE_H
#define RLE_H

#include <string>

class RLE {
public:
    std::string compress(const std::string& input);

    std::string decompress(const std::string& input);
};

#endif