#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

string encrypt(const string& text, const string& mixed) {
    string result;
    for (char c : text) {
        if (isalpha(c)) {
            char encryptedChar = mixed[tolower(c) - 'a']; 
            result += (c >= 'A' && c <= 'Z') ? (encryptedChar - 'a' + 'A') : encryptedChar;
        } else {
            result += c; 
        }
    }
    return result;
}

string decrypt(const string& text, const string& mixed) {
    string result;
    unordered_map<char, char> reverseMap;
    
    for (int i = 0; i < 26; ++i) {
        reverseMap[mixed[i]] = 'a' + i;
        reverseMap[toupper(mixed[i])] = 'A' + i;
    }
    
    for (char c : text) {
        if (isalpha(c)) {
            result += reverseMap[c];
        } else {
            result += c; 
        }
    }
    return result;
}

int main() {
    string mixed = "qwertyuiopasdfghjklzxcvbnm"; 
    string text, encryptedText, decryptedText;

    cout << "Greq text Gaxtnagrman hamar: ";
    getline(cin, text);

    encryptedText = encrypt(text, mixed);
    cout << "Gaxtnagrvac text: " << encryptedText << endl;

    
    decryptedText = decrypt(encryptedText, mixed);
    cout << "Vercanvac text: " << decryptedText << endl;

    if (text == decryptedText) {
        cout << "Decrypt katarvel e: Skzbanakan texty nuynn e inj vercanvacy." << endl;
    } else {
        cout << "error: chi hamynknum texty." << endl;
    }

    return 0;
}