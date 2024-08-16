// 2081-01-27 (Lab-4)


#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to perform Monoalphabetic encryption or decryption
void monoalphabeticCipher(char *text, char *key, int encrypt) {
    int textLen = strlen(text);
    int i;

    // Loop through each character of the text
    for (i = 0; i < textLen; ++i) {
        char currentChar = text[i];

        // Only perform encryption/decryption on alphabetic characters
        if (isalpha(currentChar)) {
            char offset = islower(currentChar) ? 'a' : 'A';
            int keyIndex = tolower(currentChar) - 'a'; // Convert to lowercase for index

            // Perform encryption or decryption based on the flag
            if (encrypt)
                text[i] = islower(currentChar) ? tolower(key[keyIndex]) : toupper(key[keyIndex]);
            else {
                // Find the corresponding index in the key
                int j;
                for (j = 0; j < 26; ++j) {
                    if (tolower(key[j]) == tolower(currentChar)) {
                        keyIndex = j;
                        break;
                    }
                }
                text[i] = islower(currentChar) ? 'a' + keyIndex : 'A' + keyIndex;
            }
        }
    }
}

int main() {
    char key[27]; // Include space for the null terminator
    char text[1000];
    char result[1000]; // Store the result of encryption/decryption
    int choice;

    printf("Enter the key (26 unique letters): ");
    fgets(key, sizeof(key), stdin);

    // Remove newline character from the key
    key[strcspn(key, "\n")] = '\0';

    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);

    // Remove newline character from the text
    text[strcspn(text, "\n")] = '\0';

    printf("Enter 1 to encrypt or 0 to decrypt: ");
    scanf("%d", &choice);

    // Flush the input buffer
    while (getchar() != '\n');

    // Encrypt or decrypt based on user choice
    strcpy(result, text); // Copy input text to result
    monoalphabeticCipher(result, key, choice);

    printf("Result: %s\n", result);

    return 0;
}
