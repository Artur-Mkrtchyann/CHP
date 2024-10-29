#include <iostream>
#include "Cipher.h"

using namespace std;

int main() {
    Cipher cipher;

    string key = cipher.makeKey();

    string textToHash;
    cout << "Enter text to encrypt: ";
    getline(cin, textToHash);

    string encryptedText = cipher.encrypt(textToHash, key);

    cout << "Key: " << key << endl;
    cout << "Result: " << encryptedText << endl;

    string decrypted = cipher.decrypt(encryptedText, key);
    cout << "Decrypted: " << decrypted << endl;

    cout << (cipher.checking(decrypted, textToHash) ? "Ok" : "Something wrong!") << endl;

    return 0;
}