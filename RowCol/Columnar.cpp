#include "Columnar.h"
#include <iostream>
#include <vector>
#include <string>

ColumnarCipher::ColumnarCipher(int n) : n(n) {}

std::vector<std::vector<char>> ColumnarCipher::generateKey(const std::string& text) {
    int rows = (text.size() + n - 1) / n;
    std::vector<std::vector<char>> matrix(rows, std::vector<char>(n, ' '));

    int k = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < n; j++) {
            if (k < text.length()) {
                matrix[i][j] = text[k++];
            }
        }
    }
    return matrix;
}

std::vector<std::vector<char>> ColumnarCipher::generateDecryptKey(const std::string& text) {
    int rows = (text.size() + n - 1) / n;
    std::vector<std::vector<char>> matrix(rows, std::vector<char>(n, ' '));

    int k = 0;
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < rows; i++) {
            if (k < text.length()) {
                matrix[i][j] = text[k++];
            }
        }
    }
    return matrix;
}

std::string ColumnarCipher::encrypt(const std::string& text) {
    std::string encrypted;
    auto matrix = generateKey(text);

    std::cout << "Encrypt key:" << std::endl;
    for (const auto& row : matrix) {
        for (char ch : row) {
            std::cout << ch << " ";
        }
        std::cout << std::endl;
    }

    for (int j = 0; j < n; j++) {
        for (int i = 0; i < matrix.size(); i++) {
            encrypted += matrix[i][j];
        }
    }

    return encrypted;
}

std::string ColumnarCipher::decrypt(const std::string& text) {
    std::string decrypted;
    auto matrix = generateDecryptKey(text);

    std::cout << "Decrypt key:" << std::endl;
    for (const auto& row : matrix) {
        for (char ch : row) {
            std::cout << ch << " ";
        }
        std::cout << std::endl;
    }

    for (const auto& row : matrix) {
        for (char ch : row) {
            decrypted += ch;
        }
    }

    return decrypted;
}