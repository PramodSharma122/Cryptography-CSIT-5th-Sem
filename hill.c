// 2081-01-29 (Lab-6)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Function to convert a character to its corresponding numerical value (A=0, B=1, ..., Z=25)
int charToNum(char ch) {
    return toupper(ch) - 'A';
}

// Function to convert a numerical value to its corresponding character (0=A, 1=B, ..., 25=Z)
char numToChar(int num) {
    return num + 'A';
}

// Function to calculate the determinant of a 2x2 matrix
int determinant(int matrix[2][2]) {
    return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

// Function to calculate the modular inverse of a number
int modInverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    // Apply extended Euclid Algorithm
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    // Make x1 positive
    if (x1 < 0)
        x1 += m0;

    return x1;
}

// Function to calculate the cofactor of a 2x2 matrix
void cofactor(int matrix[2][2], int cofactorMatrix[2][2]) {
    cofactorMatrix[0][0] = matrix[1][1];
    cofactorMatrix[0][1] = -matrix[0][1];
    cofactorMatrix[1][0] = -matrix[1][0];
    cofactorMatrix[1][1] = matrix[0][0];
}

// Function to calculate the adjoint of a 2x2 matrix
void adjoint(int matrix[2][2], int adjMatrix[2][2]) {
    adjMatrix[0][0] = matrix[1][1];
    adjMatrix[0][1] = -matrix[0][1];
    adjMatrix[1][0] = -matrix[1][0];
    adjMatrix[1][1] = matrix[0][0];
}

// Function to perform matrix multiplication
void matrixMultiply(int a[2][2], int b[2], int result[2]) {
    result[0] = a[0][0] * b[0] + a[0][1] * b[1];
    result[1] = a[1][0] * b[0] + a[1][1] * b[1];
}

// Function to encrypt using the Hill cipher
void hillEncrypt(char *plaintext, int key[2][2], char *ciphertext) {
    int len = strlen(plaintext);
    int i, j;

    for (i = 0; i < len; i += 2) {
        int block[2], result[2];
        block[0] = charToNum(plaintext[i]);
        block[1] = (i + 1 < len) ? charToNum(plaintext[i + 1]) : charToNum('X'); // Pad with 'X' if necessary
        matrixMultiply(key, block, result);
        ciphertext[i] = numToChar(result[0] % 26);
        ciphertext[i + 1] = numToChar(result[1] % 26);
    }
    ciphertext[len] = '\0';
}

// Function to decrypt using the Hill cipher
void hillDecrypt(char *ciphertext, int key[2][2], char *plaintext) {
    int len = strlen(ciphertext);
    int i, j;

    // Calculate the determinant of the key matrix
    int det = determinant(key);

    // Calculate the modular inverse of the determinant
    int detInverse = modInverse(det, 26);

    // Calculate the adjoint of the key matrix
    int adjMatrix[2][2];
    adjoint(key, adjMatrix);

    // Calculate the inverse key matrix
    int invKey[2][2];
    for (i = 0; i < 2; ++i) {
        for (j = 0; j < 2; ++j) {
            invKey[i][j] = (adjMatrix[i][j] * detInverse) % 26;
            if (invKey[i][j] < 0)
                invKey[i][j] += 26;
        }
    }

    // Decrypt the ciphertext
    for (i = 0; i < len; i += 2) {
        int block[2], result[2];
        block[0] = charToNum(ciphertext[i]);
        block[1] = charToNum(ciphertext[i + 1]);
        matrixMultiply(invKey, block, result);
        plaintext[i] = numToChar(result[0] % 26);
        plaintext[i + 1] = numToChar(result[1] % 26);
    }
    plaintext[len] = '\0';
}

int main() {
    char plaintext[1000];
    char ciphertext[1000];
    char decrypted[1000];
    int key[2][2] = {{3, 2}, {5, 7}}; // Example key matrix

    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    // Remove newline character from input string
    plaintext[strcspn(plaintext, "\n")] = '\0';

    // Encrypt the plaintext
    hillEncrypt(plaintext, key, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    // Decrypt the ciphertext
    hillDecrypt(ciphertext, key, decrypted);
    printf("Decrypted plaintext: %s\n", decrypted);

    return 0;
}
