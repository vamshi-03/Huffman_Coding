#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <vector>
#include <bitset>

using namespace std;

// Structure for a Huffman tree node
struct HuffmanNode {
    char data;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char data, int frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {}
};

// Comparison function for priority queue
struct Compare {
    bool operator()(HuffmanNode* left, HuffmanNode* right) {
        return left->frequency > right->frequency;
    }
};

// Function to build Huffman tree from the frequency table
HuffmanNode* buildHuffmanTree(map<char, int>& frequencyTable) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;

    for (const auto& pair : frequencyTable) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        HuffmanNode* left = pq.top();
        pq.pop();
        HuffmanNode* right = pq.top();
        pq.pop();

        HuffmanNode* newNode = new HuffmanNode('\0', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;

        pq.push(newNode);
    }

    return pq.top();
}

// Function to generate Huffman codes for each character
void generateHuffmanCodes(HuffmanNode* root, const string& code, map<char, string>& huffmanCodes) {
    if (!root) {
        return;
    }

    if (root->data != '\0') {
        huffmanCodes[root->data] = code;
    }

    generateHuffmanCodes(root->left, code + "0", huffmanCodes);
    generateHuffmanCodes(root->right, code + "1", huffmanCodes);
}

// Function to encode the input text using Huffman codes
string encodeText(const string& text, const map<char, string>& huffmanCodes) {
    string encodedText;
    for (char c : text) {
        encodedText += huffmanCodes.at(c);
    }
    return encodedText;
}

// Function to decode the encoded text using Huffman tree
string decodeText(const string& encodedText, HuffmanNode* root) {
    string decodedText;
    HuffmanNode* current = root;

    for (char bit : encodedText) {
        if (bit == '0') {
            current = current->left;
        } else {
            current = current->right;
        }

        if (current->data != '\0') {
            if(current->data != '\n')
            decodedText += current->data;
            current = root;
        }
    }
    return decodedText;
}

int main(int argc, char *argv[]) {

    string inputFileName = argv[1];
    string compressedFileName = inputFileName.substr(0,inputFileName.size()-4)+"_compressed.bin";
    string decompressedFileName = inputFileName.substr(0,inputFileName.size()-4)+"_decompressed.txt";

    // Reading the content of the input file
    ifstream inputFile(inputFileName, ios::in | ios::binary);
    if (!inputFile.is_open()) {
        cerr << "Error opening the input file." << endl;
        return 1;
    }

    string inputText((istreambuf_iterator<char>(inputFile)), (istreambuf_iterator<char>()));
    inputFile.close();

    map<char, int> frequencyTable;

    // Counting the frequency of each character in the input text
    for (char c : inputText) {
        frequencyTable[c]++;
    }

    // BUilding the Huffman tree
    HuffmanNode* root = buildHuffmanTree(frequencyTable);

    // Generation of  Huffman codes
    map<char, string> huffmanCodes;
    generateHuffmanCodes(root, "", huffmanCodes);

    // Encoding the input text
    string encodedText = encodeText(inputText, huffmanCodes);

    // Writing the encoded bits to a binary file
    ofstream compressedFile(compressedFileName, ios::out | ios::binary);
    if (!compressedFile.is_open()) {
        cerr << "Error opening the compressed file." << endl;
        return 1;
    }

    // Converting the binary string to binary data
    string binaryData;
    for (size_t i = 0; i < encodedText.size(); i += 8) {
        string byteString = encodedText.substr(i, 8);
        char byte = static_cast<char>(bitset<8>(byteString).to_ulong());
        binaryData.push_back(byte);
    }

    // writing content to compressed file 
    compressedFile.write(binaryData.c_str(), binaryData.size());
    compressedFile.close();

    // Decoding the compressed file by calling the function decodeText
    string decodedText = decodeText(encodedText, root);
    
    // opening decompressed file
    ofstream decompressedFile(decompressedFileName);
    if (!decompressedFile.is_open()) {
        cerr << "Error opening the decompressed file." << endl;
        return 1;
    }
    // writing content to decompressed file
    decompressedFile<<decodedText;
    

    decompressedFile.close();

    // Cleaning up and releasing memory
    delete root;

    // prompt message
    cout << "File compression and decompression completed." << endl;

    return 0;
}
