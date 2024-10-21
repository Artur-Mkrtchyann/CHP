#include <iostream>
#include <string>

using namespace std;

class RLE {
public:
    string encode(const string& message) {
        string encoded_message;
        int i = 0;

        while (i < message.length()) {
            char char_to_encode = message[i];
            int count = 1;

            // krknvelu qanaky
            while (i + 1 < message.length() && message[i + 1] == char_to_encode) {
                count++;
                i++;
            }

            encoded_message += to_string(count); 
            encoded_message += char_to_encode; 
            i++;
        }

        return encoded_message;
    }

    string decode(const string& encoded_message) {
        string decoded_message;
        int i = 0;

        while (i < encoded_message.length()) {
            // krknvoxneri qanak
            string count_str;
            while (isdigit(encoded_message[i])) {
                count_str += encoded_message[i];
                i++;
            }
            int count = stoi(count_str); 

            char character = encoded_message[i];
            decoded_message.append(count, character); 
            i++;
        }

        return decoded_message;
    }
};

int main() {
    string message;
    cout << "Skzbnakan text: ";
    getline(cin, message);

    RLE rle;

    string encoded_message = rle.encode(message);
    cout << "Kodavorvac: " << encoded_message << endl;

    string decoded_message = rle.decode(encoded_message);
    cout << "Vercanvac: " << decoded_message << endl;

    return 0;
}
