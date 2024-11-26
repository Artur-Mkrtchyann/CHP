#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>

using namespace std;

class Node {
public:
    char character;
    int count;
    Node* left;
    Node* right;

    Node(char c, int co) : character(c), count(co), left(nullptr), right(nullptr) {}

    // Modify comparison to dereference Node* pointers
    bool operator>(const Node& other) const {
        return count > other.count || (count == other.count && character > other.character);
    }
};

// Custom comparator for priority queue to compare pointers to Node objects
struct CompareNode {
    bool operator()(Node* left, Node* right) {
        return *left > *right;  // Dereference the pointers to compare the actual Node objects
    }
};

class HuffmanTree {
public:
    Node* root;

    HuffmanTree(const string& text) {
        unordered_map<char, int> freq;
        for (char c : text) freq[c]++;

        // Use priority_queue with the custom comparator
        priority_queue<Node*, vector<Node*>, CompareNode> pq;
        for (const auto& p : freq)
            pq.push(new Node(p.first, p.second));

        while (pq.size() > 1) {
            Node* left = pq.top(); pq.pop();
            Node* right = pq.top(); pq.pop();
            Node* newNode = new Node('\0', left->count + right->count);
            newNode->left = left;
            newNode->right = right;
            pq.push(newNode);
        }

        root = pq.top();
    }

    void generateCodes(Node* node, const string& code, unordered_map<char, string>& codes) {
        if (!node) return;
        if (!node->left && !node->right) {
            codes[node->character] = code;
            return;
        }
        generateCodes(node->left, code + "0", codes);
        generateCodes(node->right, code + "1", codes);
    }

    string encode(const string& text, const unordered_map<char, string>& codes) {
        string encoded;
        for (char c : text)
            encoded += codes.at(c);
        return encoded;
    }

    string decode(const string& encoded) {
        string decoded;
        Node* current = root;
        for (char bit : encoded) {
            current = (bit == '0') ? current->left : current->right;
            if (!current->left && !current->right) {
                decoded += current->character;
                current = root;
            }
        }
        return decoded;
    }
};

int main() {
    string text;
    cout << "Enter text: ";
    getline(cin, text);

    HuffmanTree tree(text);

    unordered_map<char, string> huffmanCodes;
    tree.generateCodes(tree.root, "", huffmanCodes);

    cout << "Huffman codes: " << endl;
    for (const auto& pair : huffmanCodes)
        cout << pair.first << ": " << pair.second << endl;

    string encoded = tree.encode(text, huffmanCodes);
    cout << "Encoded: " << encoded << endl;
    
    string decoded = tree.decode(encoded);
    cout << "Decoded: " << decoded << endl;

    return 0;
}
