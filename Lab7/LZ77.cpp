#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Token {
    int length, offset;
    char next_char;
};


vector<Token> compressLZ77(const string& input) {
    vector<Token> result;
    int n = input.size();

    int i = 0;
    while (i < n) {
        int max_len = 0, max_offset = 0;

        for (int j = max(i - 255, 0); j < i; ++j) {
            int len = 0;
            while (i + len < n && input[j + len] == input[i + len]) {
                len++;
            }
            if (len > max_len) {
                max_len = len;
                max_offset = i - j;
            }
        }

                    
        if (max_len > 0) {
            result.push_back({ max_len, max_offset, input[i + max_len] });
            i += max_len + 1;
        }
        else {
            result.push_back({ 0, 0, input[i] });
            i++;
        }
    }

    return result;
}

string decompressLZ77(const vector<Token>& tokens) {
    string result;

    for (const auto& token : tokens) {
        if (token.length > 0) {
            int start = result.size() - token.offset;
            for (int i = 0; i < token.length; ++i) {
                result += result[start + i];
            }
            result += token.next_char;
        }
        else {
            result += token.next_char;
        }
    }

    return result;
}
            
void printCompressed(const vector<Token>& tokens) {
    for (const auto& token : tokens) {
        cout << "(" << token.length << ", " << token.offset << ", '" << token.next_char << "') ";
    }
    cout << endl;
}

int main() {
    string input;
    cout << "Enter the string to compress: ";
    getline(cin, input);
 
    vector<Token> compressed = compressLZ77(input);
    cout << "Compressed data: ";
    printCompressed(compressed);

    string decompressed = decompressLZ77(compressed);
    cout << "Decompressed string: " << decompressed << endl;

    return 0;
}
