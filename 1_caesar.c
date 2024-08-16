// Q1. To implement caesar cipher (Encryption and Decryption). 2081-01-25 (Lab-1).

/*
Encryption
    CT=(PT+3) mod 26
Decryption
    PT=(CT-3) mod 26
*/

#include <stdio.h>
#include <string.h>

// Function to encrypt a message using Caesar cipher
void encrypt(char message[], int shift) {
    int i;
    char ch;
    for(i = 0; message[i] != '\0'; ++i) {
        ch = message[i];
        
        if(ch >= 'a' && ch <= 'z') {
            ch = ch + shift;
            if(ch > 'z') {
                ch = ch - 'z' + 'a' - 1;
            }
            message[i] = ch;
        }
        else if(ch >= 'A' && ch <= 'Z') {
            ch = ch + shift;
            if(ch > 'Z') {
                ch = ch - 'Z' + 'A' - 1;
            }
            message[i] = ch;
        }
    }
}

// Function to decrypt a message using Caesar cipher
void decrypt(char message[], int shift) {
    int i;
    char ch;
    for(i = 0; message[i] != '\0'; ++i) {
        ch = message[i];
        
        if(ch >= 'a' && ch <= 'z') {
            ch = ch - shift;
            if(ch < 'a') {
                ch = ch + 'z' - 'a' + 1;
            }
            message[i] = ch;
        }
        else if(ch >= 'A' && ch <= 'Z') {
            ch = ch - shift;
            if(ch < 'A') {
                ch = ch + 'Z' - 'A' + 1;
            }
            message[i] = ch;
        }
    }
}

int main() {
    char message[100];
    int shift, choice;
    
    printf("Enter a message to encrypt: ");
    fgets(message, sizeof(message), stdin);
    printf("Enter the shift value: ");
    scanf("%d", &shift);
    
    printf("Enter 1 to encrypt or 2 to decrypt: ");
    scanf("%d", &choice);
    
    switch(choice) {
        case 1:
            encrypt(message, shift);
            printf("Encrypted message: %s\n", message);
            break;
        case 2:
            decrypt(message, shift);
            printf("Decrypted message: %s\n", message);
            break;
        default:
            printf("Invalid choice.\n");
    }
    
    return 0;
}
