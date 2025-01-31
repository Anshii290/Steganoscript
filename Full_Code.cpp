#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>

// Hash Map-based encoding for Selective Hiding Method
std::string selectiveHidingEncode(const std::string& plainText, const std::string& secretMessage) {
    std::stringstream ss(plainText);
    std::string word;
    std::vector<std::string> words;
    size_t messageIndex = 0;

    // Create a hash map to map secret message characters to plain text characters directly
    std::unordered_map<char, char> encodingMap;
    for (size_t i = 0; i < secretMessage.length() && i < plainText.length(); ++i) {
        encodingMap[plainText[i]] = secretMessage[i];
    }

    // Embedding secret characters into the text by modifying each character directly
    std::string encodedText;
    for (size_t i = 0; i < plainText.length(); ++i) {
        if (messageIndex < secretMessage.length() && encodingMap.count(plainText[i])) {
            encodedText += encodingMap[plainText[i]];  // Embed the secret character
            messageIndex++;
        } else {
            encodedText += plainText[i];  // Retain original character if not encoding
        }
    }
    return encodedText;
}

// Decoding with hash map for Selective Hiding
std::string selectiveHidingDecode(const std::string& encodedText) {
    std::string decodedMessage;
    for (char ch : encodedText) {
        if (isalpha(ch) || isdigit(ch)) { // Assuming secret message is alphanumeric
            decodedMessage += ch;
        }
    }
    return decodedMessage;
}

// File Handling Functions
std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string text, line;
    if (file.is_open()) {
        while (getline(file, line)) {
            text += line + "\n";
        }
        file.close();
    } else {
        std::cerr << "Unable to open file.\n";
    }
    return text;
}

void writeFile(const std::string& filename, const std::string& text) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << text;
        file.close();
        std::cout << "File saved: " << filename << std::endl;
    } else {
        std::cerr << "Unable to save file.\n";
    }
}

// Main Menu
void displayMenu() {
    std::cout << "\n--- Stegano Script CLI ---\n";
    std::cout << "1. Encode using Selective Hiding with Hash Map\n";
    std::cout << "2. Decode using Selective Hiding\n";
    std::cout << "3. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    int choice;
    do {
        displayMenu();
        std::cin >> choice;

        std::string plainText, secretMessage, encodedText, decodedMessage;
        std::string inputFilename, outputFilename;
        
        switch (choice) {
            case 1:
                std::cout << "Enter plain text file name: ";
                std::cin >> inputFilename;
                plainText = readFile(inputFilename);
                std::cout << "Enter secret message: ";
                std::cin >> secretMessage;
                encodedText = selectiveHidingEncode(plainText, secretMessage);
                std::cout << "Enter output file name for encoded text: ";
                std::cin >> outputFilename;
                writeFile(outputFilename, encodedText);
                break;

            case 2:
                std::cout << "Enter encoded file name: ";
                std::cin >> inputFilename;
                encodedText = readFile(inputFilename);
                decodedMessage = selectiveHidingDecode(encodedText);
                std::cout << "Decoded Message: " << decodedMessage << std::endl;
                break;

            case 3:
                std::cout << "Exiting...\n";
                break;

            default:
                std::cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 3);

    return 0;
}
