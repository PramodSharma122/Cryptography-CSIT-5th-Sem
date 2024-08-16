// 2081-01-26 (Lab-3)

#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to generate autokey based on the input key and text
void generateAutoKey(char *key, char *text, char *autoKey) {
    int keyLen = strlen(key);
    int textLen = strlen(text);

    // Copy the key to the beginning of the autokey
    strcpy(autoKey, key);

    // Append the text to the autokey
    for (int i = 0, j = keyLen; i < textLen; ++i, ++j) {
        if (autoKey[j] == '\0') {
            autoKey[j] = text[i];
            autoKey[j + 1] = '\0';
        }
    }
}

// Function to perform Vigenère encryption or decryption
void vigenereCipher(char *text, char *key, int encrypt) {
    int textLen = strlen(text);
    int keyLen = strlen(key);
    int i, j;

    // Loop through each character of the text
    for (i = 0, j = 0; i < textLen; ++i) {
        char currentChar = text[i];

        // Only perform encryption/decryption on alphabetic characters
        if (isalpha(currentChar)) {
            char offset = islower(currentChar) ? 'a' : 'A';
            char keyChar = key[j % keyLen];
            char keyOffset = islower(keyChar) ? 'a' : 'A';

            // Perform encryption or decryption based on the flag
            if (encrypt)
                text[i] = ((currentChar - offset) + (keyChar - keyOffset)) % 26 + offset;
            else
                text[i] = ((currentChar - offset) - (keyChar - keyOffset) + 26) % 26 + offset;

            // Move to the next character in the key
            ++j;
        }
    }
}

int main() {
    char key[100];
    char text[1000];
    char autoKey[1100]; // Slightly larger to accommodate the autokey
    int choice;

    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);

    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);

    // Remove newline characters from input strings
    key[strcspn(key, "\n")] = '\0';
    text[strcspn(text, "\n")] = '\0';

    // Generate autokey
    generateAutoKey(key, text, autoKey);

    printf("AutoKey: %s\n", autoKey);

    printf("Enter 1 to encrypt or 0 to decrypt: ");
    scanf("%d", &choice);

    // Encrypt or decrypt based on user choice
    vigenereCipher(text, autoKey, choice);

    printf("Result: %s\n", text);

    return 0;
}
