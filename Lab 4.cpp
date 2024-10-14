#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<vector<char>> generateKey(int n, const string& text) {
    int rows = (text.size() + n - 1) / n;
    vector<vector<char>> matrix(rows, vector<char>(n, ' '));

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

vector<vector<char>> generateDecriptKey(int n, const string& text) {
    int rows = (text.size() + n - 1) / n;
    vector<vector<char>> matrix(rows, vector<char>(n, ' '));

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

string encript(int n, const string& text) {
    string encripted = "";
    vector<vector<char>> matrix = generateKey(n, text);

    cout << "Encrypt key:" << endl;
    for (const auto& row : matrix) {
        for (char ch : row) {
            cout << ch << " ";
        }
        cout << endl;
    }

    for (int j = 0; j < n; j++) {
        for (int i = 0; i < matrix.size(); i++) {
            encripted += matrix[i][j];
        }
    }

    return encripted;
}

string decript(int n, const string& text) {
    string decripted = "";
    vector<vector<char>> matrix = generateDecriptKey(n, text);

    cout << "Decrypt key:" << endl;
    for (const auto& row : matrix) {
        for (char ch : row) {
            cout << ch << " ";
        }
        cout << endl;
    }

    for (const auto& row : matrix) {
        for (char ch : row) {
            decripted += ch;
        }
    }

    return decripted;
}

int main() {
    int n;
    string text;

    cout << "Enter text: ";
    getline(cin, text);

    cout << "Enter number: ";
    cin >> n;

    string encripted = encript(n, text);
    cout << "Encrypted text: " << encripted << endl;

    string decripted = decript(n, encripted);
    cout << "Decrypted text: " << decripted << endl;

    return 0;
}
