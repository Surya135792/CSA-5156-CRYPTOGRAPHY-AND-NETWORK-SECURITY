#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Initial Permutation Table
int IP[] = { 58, 50, 42, 34, 26, 18, 10, 2,
             60, 52, 44, 36, 28, 20, 12, 4,
             62, 54, 46, 38, 30, 22, 14, 6,
             64, 56, 48, 40, 32, 24, 16, 8,
             57, 49, 41, 33, 25, 17, 9, 1,
             59, 51, 43, 35, 27, 19, 11, 3,
             61, 53, 45, 37, 29, 21, 13, 5,
             63, 55, 47, 39, 31, 23, 15, 7 };

// Final Permutation Table
int FP[] = { 40, 8, 48, 16, 56, 24, 64, 32,
             39, 7, 47, 15, 55, 23, 63, 31,
             38, 6, 46, 14, 54, 22, 62, 30,
             37, 5, 45, 13, 53, 21, 61, 29,
             36, 4, 44, 12, 52, 20, 60, 28,
             35, 3, 43, 11, 51, 19, 59, 27,
             34, 2, 42, 10, 50, 18, 58, 26,
             33, 1, 41, 9, 49, 17, 57, 25 };

// Example S-box
int S_BOX[8][4][16] = {
    // S1
    {
        {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
    },
    // S2
    // ... (Other S-boxes should be defined here)
};

uint64_t initial_permutation(uint64_t input) {
    uint64_t output = 0;
    for (int i = 0; i < 64; i++) {
        output <<= 1;
        output |= (input >> (64 - IP[i])) & 0x01;
    }
    return output;
}

uint64_t final_permutation(uint64_t input) {
    uint64_t output = 0;
    for (int i = 0; i < 64; i++) {
        output <<= 1;
        output |= (input >> (64 - FP[i])) & 0x01;
    }
    return output;
}

uint32_t feistel(uint32_t half_block, uint64_t subkey) {
    // Expansion, substitution using S-boxes, and permutation should be implemented here.
    // This is a simplified version that just XORs with the subkey.
    return half_block ^ (uint32_t)subkey;
}

uint64_t des_encrypt(uint64_t plaintext, uint64_t key) {
    uint64_t permuted_block = initial_permutation(plaintext);
    uint32_t left = (permuted_block >> 32) & 0xFFFFFFFF;
    uint32_t right = permuted_block & 0xFFFFFFFF;

    for (int round = 0; round < 16; round++) {
        uint64_t subkey = key;  // Simplified key schedule for demonstration
        uint32_t temp = right;
        right = left ^ feistel(right, subkey);
        left = temp;
    }

    uint64_t pre_output = ((uint64_t)right << 32) | left;
    uint64_t ciphertext = final_permutation(pre_output);
    return ciphertext;
}

uint64_t des_decrypt(uint64_t ciphertext, uint64_t key) {
    uint64_t permuted_block = initial_permutation(ciphertext);
    uint32_t left = (permuted_block >> 32) & 0xFFFFFFFF;
    uint32_t right = permuted_block & 0xFFFFFFFF;

    for (int round = 0; round < 16; round++) {
        uint64_t subkey = key;  // Simplified key schedule for demonstration
        uint32_t temp = left;
        left = right ^ feistel(left, subkey);
        right = temp;
    }

    uint64_t pre_output = ((uint64_t)left << 32) | right;
    uint64_t plaintext = final_permutation(pre_output);
    return plaintext;
}

int main() {
    uint64_t plaintext = 0x0123456789ABCDEF;
    uint64_t key = 0x133457799BBCDFF1;

    uint64_t ciphertext = des_encrypt(plaintext, key);
    uint64_t decrypted_text = des_decrypt(ciphertext, key);

    printf("Plaintext: 0x%016llX\n", plaintext);
    printf("Ciphertext: 0x%016llX\n", ciphertext);
    printf("Decrypted: 0x%016llX\n", decrypted_text);

    return 0;
}
