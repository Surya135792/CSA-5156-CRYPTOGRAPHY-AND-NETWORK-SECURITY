#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void generate_random_k(char *k, size_t length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (size_t i = 0; i < length; i++) {
        int key = rand() % (sizeof(charset) - 1);
        k[i] = charset[key];
    }
    k[length] = '\0';
}

void dsa_sign(const char *message, char *signature) {
    // Simulating DSA signature
    char k[9]; // Random k for DSA (8 characters + null terminator)
    generate_random_k(k, 8);
    sprintf(signature, "DSA_SIG(%s,%s)", message, k);
}

void rsa_sign(const char *message, char *signature) {
    // Simulating RSA signature
    sprintf(signature, "RSA_SIG(%s)", message);
}

int main() {
    srand(time(NULL)); // Seed the random number generator

    const char *message = "This is a test message";
    char dsa_signature1[50];
    char dsa_signature2[50];
    char rsa_signature1[50];
    char rsa_signature2[50];

    // Simulating DSA signatures for the same message
    dsa_sign(message, dsa_signature1);
    dsa_sign(message, dsa_signature2);

    // Simulating RSA signatures for the same message
    rsa_sign(message, rsa_signature1);
    rsa_sign(message, rsa_signature2);

    printf("Message: %s\n", message);
    printf("DSA Signature 1: %s\n", dsa_signature1);
    printf("DSA Signature 2: %s\n", dsa_signature2);
    printf("RSA Signature 1: %s\n", rsa_signature1);
    printf("RSA Signature 2: %s\n", rsa_signature2);

    return 0;
}
