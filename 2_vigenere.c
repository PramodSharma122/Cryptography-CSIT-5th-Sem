// 2081-01-26 (Lab-2)

#include <stdio.h>
#include <string.h>
#include <ctype.h>

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
    char text[1000];
    char key[100];
    int choice;

    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter the key: ");
    scanf("%s", key);

    printf("Enter 1 to encrypt or 0 to decrypt: ");
    scanf("%d", &choice);

    // Encrypt or decrypt based on user choice
    vigenereCipher(text, key, choice);

    printf("Result: %s\n", text);

    return 0;
}
