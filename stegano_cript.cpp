#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// Function to encode the secret message into plain text (Selective Hiding)
string encodeSelectiveHiding(const string& plainText, const string& binaryMessage) {
    string encodedText = plainText;
    size_t binaryIndex = 0;

    for (size_t i = 0; i < plainText.length() && binaryIndex < binaryMessage.length(); ++i) {
        if (isalpha(plainText[i])) { // Encode only alphabetic characters
            if (binaryMessage[binaryIndex] == '1') {
                encodedText[i] = toupper(plainText[i]); // Capitalize for '1'
            } else {
                encodedText[i] = tolower(plainText[i]); // Lowercase for '0'
            }
            binaryIndex++;
        }
    }

    // Ensure all binary bits are encoded
    if (binaryIndex < binaryMessage.length()) {
        cerr << "Error: Plain text is too short to hide the entire binary message." << endl;
        return "";
    }
    return encodedText;
}

// Function to decode the binary message from encoded text (Selective Hiding)
string decodeSelectiveHiding(const string& encodedText) {
    string binaryMessage;

    for (char c : encodedText) {
        if (isalpha(c)) {
            binaryMessage += (isupper(c) ? '1' : '0');
        }
    }
    return binaryMessage;
}

// Function to encode the binary message using Whitespace Method
string encodeWhitespace(const string& plainText, const string& binaryMessage) {
    string encodedText;
    size_t binaryIndex = 0;

    for (char c : plainText) {
        encodedText += c;

        if (binaryIndex < binaryMessage.length()) {
            if (binaryMessage[binaryIndex] == '1') {
                encodedText += "  "; // Double space for '1'
            } else {
                encodedText += " "; // Single space for '0'
            }
            binaryIndex++;
        }
    }

    // Ensure all binary bits are encoded
    if (binaryIndex < binaryMessage.length()) {
        cerr << "Error: Plain text is too short to hide the entire binary message." << endl;
        return "";
    }
    return encodedText;
}

// Function to decode the binary message from encoded text (Whitespace Method)
string decodeWhitespace(const string& encodedText) {
    string binaryMessage;
    size_t i = 0;

    while (i < encodedText.length()) {
        if (encodedText[i] == ' ') {
            if (i + 1 < encodedText.length() && encodedText[i + 1] == ' ') {
                binaryMessage += '1';
                i += 2; // Skip double space
            } else {
                binaryMessage += '0';
                i += 1; // Skip single space
            }
        } else {
            i++;
        }
    }
    return binaryMessage;
}

int main() {
    int choice;
    string plainText, binaryMessage, encodedText, decodedMessage, fileName;

    cout << "Welcome to Stegano Script\n";
    cout << "1. Encode (Selective Hiding)\n";
    cout << "2. Decode (Selective Hiding)\n";
    cout << "3. Encode (Whitespace Method)\n";
    cout << "4. Decode (Whitespace Method)\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore(); // Ignore newline character from previous input

    switch (choice) {
        case 1:
            cout << "Enter plain text: ";
            getline(cin, plainText);
            cout << "Enter binary message to hide: ";
            getline(cin, binaryMessage);
            encodedText = encodeSelectiveHiding(plainText, binaryMessage);

            if (!encodedText.empty()) {
                cout << "Enter file name to save encoded text: ";
                cin >> fileName;
                ofstream outFile(fileName);
                outFile << encodedText;
                outFile.close();
                cout << "Encoded text saved to " << fileName << endl;
            }
            break;

        case 2:
            cout << "Enter file name containing the encoded text: ";
            cin >> fileName;
            {
                ifstream inFile(fileName);
                if (inFile) {
                    getline(inFile, encodedText, '\0');
                    inFile.close();
                    decodedMessage = decodeSelectiveHiding(encodedText);
                    cout << "Decoded Binary Message: " << decodedMessage << endl;
                } else {
                    cerr << "Error: File not found.\n";
                }
            }
            break;

        case 3:
            cout << "Enter plain text: ";
            getline(cin, plainText);
            cout << "Enter binary message to hide: ";
            getline(cin, binaryMessage);
            encodedText = encodeWhitespace(plainText, binaryMessage);

            if (!encodedText.empty()) {
                cout << "Enter file name to save encoded text: ";
                cin >> fileName;
                ofstream outFile(fileName);
                outFile << encodedText;
                outFile.close();
                cout << "Encoded text saved to " << fileName << endl;
            }
            break;

        case 4:
            cout << "Enter file name containing the encoded text: ";
            cin >> fileName;
            {
                ifstream inFile(fileName);
                if (inFile) {
                    getline(inFile, encodedText, '\0');
                    inFile.close();
                    decodedMessage = decodeWhitespace(encodedText);
                    cout << "Decoded Binary Message: " << decodedMessage << endl;
                } else {
                    cerr << "Error: File not found.\n";
                }
            }
            break;

        default:
            cerr << "Invalid choice!\n";
            break;
    }

    return 0;
}

