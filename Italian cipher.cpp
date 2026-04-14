#include <iostream>
#include <string>
#include <cctype>
#include <limits>

using namespace std;

const int ITALIAN_ALPHABET_SIZE = 21;

// Check if character is in Italian alphabet
bool isItalian(char ch) {
    ch = toupper(ch);
    return (ch >= 'A' && ch <= 'I') || (ch >= 'L' && ch <= 'V') || (ch == 'Z');
}

// Convert Italian letter to number (A=0 ... Z=20)
int letterToNumber(char ch) {
    ch = toupper(ch);
    if (ch >= 'A' && ch <= 'I') return ch - 'A';
    if (ch >= 'L' && ch <= 'V') return ch - 'A' - 2;
    if (ch == 'Z') return 20;
    return -1; // Not Italian
}

// Convert number to Italian letter
char numberToLetter(int numb) {
    if (numb <= 8) return 'A' + numb;
    if (numb <= 19) return 'A' + numb + 2;
    return 'Z';
}

// GCD function
int computeGCD(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Modular inverse
int modularInverse(int a, int m) {
    for (int i = 1; i < m; i++) {
        if ((a * i) % m == 1) return i;
    }
}

int main() {
    char continueChoice = 'y';

    do {
        cout << "\n=== ITALIAN AFFINE CIPHER ===\n";
        cout << "Allowed letters: A B C D E F G H I L M N O P Q R S T U V Z\n";
        cout << "Any other letter will be rejected.\n";

        cout << "\n1. Encrypt\n2. Decrypt\n3. Exit\nChoice: ";
        int operation;
        cin >> operation;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (operation == 3) break;
        if (operation != 1 && operation != 2 ) {
            cout << "Invalid choice!\n";
            continue;
        }

        // Input message
        string message;
        cout << "Enter message: ";
        getline(cin, message);

        // Validate message
        for (char ch : message) {
            if (isalpha(ch) && !isItalian(ch)) {
                cout << "ERROR: Only Italian letters are allowed! Invalid: " << ch << endl;
                goto retry;
            }
        }

        // Input keys
        int keyA, keyB;
           cout <<"Enter key a (any integer): ";
           cin >> keyA;
           cout << "Enter key b (any integer): ";
           cin >> keyB;

        // Normalize keys to 0-20
        keyA = ((keyA % ITALIAN_ALPHABET_SIZE) + ITALIAN_ALPHABET_SIZE) % ITALIAN_ALPHABET_SIZE;
        keyB = ((keyB % ITALIAN_ALPHABET_SIZE) + ITALIAN_ALPHABET_SIZE) % ITALIAN_ALPHABET_SIZE;

        // Check coprime
        if (computeGCD(keyA, ITALIAN_ALPHABET_SIZE) != 1) {
            cout << "ERROR: Key 'a' must be coprime with 21! Valid values: 1,2,4,5,8,10,11,13,16,17,19,20\n";
            goto retry;
        }

        if (operation == 1) {
            // ENCRYPTION
            string encryptedText = "";
            for (char ch : message) {
                if (isalpha(ch)) {
                    int idx = letterToNumber(ch);
                    int encIdx = (modularInverse(keyA,ITALIAN_ALPHABET_SIZE) * idx + keyB) % ITALIAN_ALPHABET_SIZE;
                    char encChar = numberToLetter(encIdx);
                    if (islower(ch)) encChar = tolower(encChar);
                    encryptedText += encChar;
                } else {
                    encryptedText += ch;
                }
            }

            // Compute decryption key
            int keyAInverse = modularInverse(keyA, ITALIAN_ALPHABET_SIZE);

            cout << "\nEncrypted text: " << encryptedText << endl;

        } else {
            // DECRYPTION
            string decryptedText = "";
            for (char ch : message) {
                if (isalpha(ch)) {
                    int idx = letterToNumber(ch);
                    int decIdx = (keyA * (idx - keyB)) % ITALIAN_ALPHABET_SIZE;
                    if (decIdx < 0) decIdx += ITALIAN_ALPHABET_SIZE;
                    char decChar = numberToLetter(decIdx);
                    if (islower(ch)) decChar = tolower(decChar);
                    decryptedText += decChar;
                } else {
                    decryptedText += ch;
                }
            }
            cout << "\nDecrypted text: " << decryptedText << endl;
        }

    retry:
        cout << "\nDo you want to continue? (y/n): ";
        cin >> continueChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (continueChoice == 'y' || continueChoice == 'Y');

    cout << "\nProgram ended. Arrivederci!\n";
    return 0;
}