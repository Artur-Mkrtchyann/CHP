#include <iostream>
#include <string>

using namespace std;

int main() {
    string mixed = "qwertyuiopasdfghjklzxcvbnm"; 
    string text, result;

    cout << "Greq text: ";
    getline(cin, text); 

    for (char c : text) {
        if (isalpha(c)) { 
            char encryptedChar = mixed[tolower(c) - 'a']; 
            result += (c >= 'A' && c <= 'Z') ? (encryptedChar - 'a' + 'A') : encryptedChar;
        } else {
            result += c; 
        }
    }

    cout << "Gaxtnagrvac text: " << result << endl; 

    return 0;
}
