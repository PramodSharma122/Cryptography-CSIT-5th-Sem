//  2081-01-28 (Lab-5)

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

// Function to preprocess the key and generate the Playfair matrix
void preprocessKey(char key[], char playfairMatrix[SIZE][SIZE]) {
    int i, j, k;
    char alphabet[26] = "ABCDEFGHIKLMNOPQRSTUVWXYZ"; // Ignoring 'J'

    printf("Key before preprocessing: %s\n", key);

    // Remove duplicate characters from the key
    int keyLen = strlen(key);
    for (i = 0; i < keyLen; ++i) {
        if (key[i] == 'J')
            key[i] = 'I'; // Replace 'J' with 'I'
        for (j = i + 1; j < keyLen;) {
            if (key[j] == key[i]) {
                for (k = j; k < keyLen; ++k) {
                    key[k] = key[k + 1];
                }
                --keyLen;
            } else {
                ++j;
            }
        }
    }

    printf("Key after preprocessing: %s\n", key);

    // Fill the Playfair matrix with the key
    k = 0;
    for (i = 0; i < SIZE; ++i) {
        for (j = 0; j < SIZE; ++j) {
            if (k < keyLen) {
                playfairMatrix[i][j] = key[k++];
            } else {
                // Fill the remaining cells with the alphabet
                int index = (i * SIZE + j) - keyLen;
                playfairMatrix[i][j] = alphabet[index];
            }
        }
    }
}

// Function to find the positions of a character in the Playfair matrix
void findPosition(char playfairMatrix[SIZE][SIZE], char ch, int *row, int *col) {
    if (ch == 'J')
        ch = 'I'; // Replace 'J' with 'I'

    int i, j;
    for (i = 0; i < SIZE; ++i) {
        for (j = 0; j < SIZE; ++j) {
            if (playfairMatrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to encrypt or decrypt using the Playfair cipher
void playfairCipher(char playfairMatrix[SIZE][SIZE], char text[], int encrypt) {
    int len = strlen(text);
    int i;

    // Replace 'J' with 'I' and remove non-alphabetic characters
    char processedText[len * 2]; // Make enough space for double the length
    int processedLen = 0;
    for (i = 0; i < len; ++i) {
        if (isalpha(text[i])) {
            processedText[processedLen++] = toupper(text[i]);
            if (text[i] == 'J')
                processedText[processedLen++] = 'I'; // Replace 'J' with 'I'
        }
    }
    processedText[processedLen] = '\0'; // Null-terminate the string

    // Pad the text with 'X' if its length is odd
    if (processedLen % 2 != 0) {
        processedText[processedLen++] = 'X';
        processedText[processedLen] = '\0'; // Null-terminate the string
    }

    // Encrypt or decrypt the processed text
    for (i = 0; i < processedLen; i += 2) {
        int row1, col1, row2, col2;
        findPosition(playfairMatrix, processedText[i], &row1, &col1);
        findPosition(playfairMatrix, processedText[i + 1], &row2, &col2);

        // Same row
        if (row1 == row2) {
            text[i] = playfairMatrix[row1][(col1 + (encrypt ? 1 : -1) + SIZE) % SIZE];
            text[i + 1] = playfairMatrix[row2][(col2 + (encrypt ? 1 : -1) + SIZE) % SIZE];
        }
        // Same column
        else if (col1 == col2) {
            text[i] = playfairMatrix[(row1 + (encrypt ? 1 : -1) + SIZE) % SIZE][col1];
            text[i + 1] = playfairMatrix[(row2 + (encrypt ? 1 : -1) + SIZE) % SIZE][col2];
        }
        // Rectangle
        else {
            text[i] = playfairMatrix[row1][col2];
            text[i + 1] = playfairMatrix[row2][col1];
        }
    }
}

int main() {
    char key[100]; // Adjusted size to accommodate longer keys
    char playfairMatrix[SIZE][SIZE];
    char text[1000];
    int choice;

    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);

    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter 1 to encrypt or 0 to decrypt: ");
    scanf("%d", &choice);

    // Remove newline characters from input strings
    key[strcspn(key, "\n")] = '\0';
    text[strcspn(text, "\n")] = '\0';

    printf("Key: %s\n", key);
    printf("Text: %s\n", text);
    printf("Choice: %d\n", choice);

    // Preprocess the key and generate the Playfair matrix
    preprocessKey(key, playfairMatrix);

    // Encrypt or decrypt based on user choice
    playfairCipher(playfairMatrix, text, choice);

    printf("Result: %s\n", text);

    return 0;
}
