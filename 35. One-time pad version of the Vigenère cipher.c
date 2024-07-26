#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Function to generate a random key
void generate_key(int *key, size_t length) {
    for (size_t i = 0; i < length; i++) {
        key[i] = rand() % 26; // Generate random number between 0 and 25
    }
}

// Function to encrypt the plaintext using the key
void encrypt(char *plaintext, int *key, char *ciphertext) {
    size_t length = strlen(plaintext);
    for (size_t i = 0; i < length; i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            ciphertext[i] = ((plaintext[i] - 'A' + key[i]) % 26) + 'A';
        } else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            ciphertext[i] = ((plaintext[i] - 'a' + key[i]) % 26) + 'a';
        } else {
            ciphertext[i] = plaintext[i]; // Non-alphabet characters remain unchanged
        }
    }
    ciphertext[length] = '\0';
}

// Function to decrypt the ciphertext using the key
void decrypt(char *ciphertext, int *key, char *plaintext) {
    size_t length = strlen(ciphertext);
    for (size_t i = 0; i < length; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = ((ciphertext[i] - 'A' - key[i] + 26) % 26) + 'A';
        } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            plaintext[i] = ((ciphertext[i] - 'a' - key[i] + 26) % 26) + 'a';
        } else {
            plaintext[i] = ciphertext[i]; // Non-alphabet characters remain unchanged
        }
    }
    plaintext[length] = '\0';
}

int main() {
    srand(time(NULL)); // Seed the random number generator

    char plaintext[] = "This is a test message for the Vigenere cipher.";
    size_t length = strlen(plaintext);

    int *key = (int *)malloc(length * sizeof(int));
    char *ciphertext = (char *)malloc((length + 1) * sizeof(char));
    char *decryptedtext = (char *)malloc((length + 1) * sizeof(char));

    generate_key(key, length);
    encrypt(plaintext, key, ciphertext);
    decrypt(ciphertext, key, decryptedtext);

    printf("Plaintext: %s\n", plaintext);
    printf("Key: ");
    for (size_t i = 0; i < length; i++) {
        printf("%d ", key[i]);
    }
    printf("\nCiphertext: %s\n", ciphertext);
    printf("Decrypted: %s\n", decryptedtext);

    // Free allocated memory
    free(key);
    free(ciphertext);
    free(decryptedtext);

    return 0;
}
