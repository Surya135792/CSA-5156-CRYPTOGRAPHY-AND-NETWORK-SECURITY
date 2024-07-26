#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to compute the GCD
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to find the modular inverse of a modulo m
int mod_inverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 0) {
            return x;
        }
    }
    return -1;
}

// Function to encrypt the plaintext using the affine cipher
void affine_encrypt(char *plaintext, int a, int b, char *ciphertext) {
    size_t length = strlen(plaintext);
    for (size_t i = 0; i < length; i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            ciphertext[i] = ((a * (plaintext[i] - 'A') + b) % 26) + 'A';
        } else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            ciphertext[i] = ((a * (plaintext[i] - 'a') + b) % 26) + 'a';
        } else {
            ciphertext[i] = plaintext[i]; // Non-alphabet characters remain unchanged
        }
    }
    ciphertext[length] = '\0';
}

// Function to decrypt the ciphertext using the affine cipher
void affine_decrypt(char *ciphertext, int a, int b, char *plaintext) {
    int a_inv = mod_inverse(a, 26); // Compute the modular inverse of a
    if (a_inv == -1) {
        printf("Invalid key (a): No modular inverse exists.\n");
        return;
    }

    size_t length = strlen(ciphertext);
    for (size_t i = 0; i < length; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = ((a_inv * ((ciphertext[i] - 'A') - b + 26)) % 26) + 'A';
        } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            plaintext[i] = ((a_inv * ((ciphertext[i] - 'a') - b + 26)) % 26) + 'a';
        } else {
            plaintext[i] = ciphertext[i]; // Non-alphabet characters remain unchanged
        }
    }
    plaintext[length] = '\0';
}

int main() {
    char plaintext[] = "Affine Caesar Cipher Example";
    int a = 5; // The value of a should be coprime with 26
    int b = 8; // The value of b can be any integer
    char ciphertext[100];
    char decryptedtext[100];

    // Check if a is valid
    if (gcd(a, 26) != 1) {
        printf("Invalid key (a): It must be coprime with 26.\n");
        return 1;
    }

    // Encrypt the plaintext
    affine_encrypt(plaintext, a, b, ciphertext);
    // Decrypt the ciphertext
    affine_decrypt(ciphertext, a, b, decryptedtext);

    // Print results
    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: %s\n", ciphertext);
    printf("Decrypted: %s\n", decryptedtext);

    return 0;
}
