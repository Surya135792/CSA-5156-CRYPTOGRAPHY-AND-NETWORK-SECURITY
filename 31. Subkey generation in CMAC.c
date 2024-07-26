#include <stdio.h>
#include <stdint.h>
#include <string.h>

void print_hex(uint8_t *data, size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf("%02X", data[i]);
    }
    printf("\n");
}

void left_shift(uint8_t *output, uint8_t *input, size_t len) {
    int carry = 0;
    for (int i = len - 1; i >= 0; i--) {
        output[i] = (input[i] << 1) | carry;
        carry = (input[i] & 0x80) ? 1 : 0;
    }
}

void xor_with_constant(uint8_t *data, uint8_t constant, size_t len) {
    data[len - 1] ^= constant;
}

void generate_subkeys(uint8_t *k1, uint8_t *k2, uint8_t *key, size_t len) {
    uint8_t L[16] = {0}; // Assuming block size is at most 128 bits (16 bytes)
    uint8_t constant;

    // Constants for block sizes
    if (len == 8) {
        constant = 0x1B; // 64-bit block size
    } else if (len == 16) {
        constant = 0x87; // 128-bit block size
    } else {
        printf("Unsupported block size\n");
        return;
    }

    // Apply block cipher to a block of all zeroes (dummy here, should be replaced with actual cipher)
    // Here we're just simulating by copying the key directly (this is not how you should implement CMAC!)
    memcpy(L, key, len);

    // Generate K1
    left_shift(k1, L, len);
    if (L[0] & 0x80) {
        xor_with_constant(k1, constant, len);
    }

    // Generate K2
    left_shift(k2, k1, len);
    if (k1[0] & 0x80) {
        xor_with_constant(k2, constant, len);
    }
}

int main() {
    uint8_t key_64[8] = {0};  // Example key (should be result of block cipher of 0 bits)
    uint8_t key_128[16] = {0}; // Example key (should be result of block cipher of 0 bits)
    
    uint8_t k1_64[8], k2_64[8];
    uint8_t k1_128[16], k2_128[16];

    generate_subkeys(k1_64, k2_64, key_64, 8);
    generate_subkeys(k1_128, k2_128, key_128, 16);

    printf("64-bit K1: "); print_hex(k1_64, 8);
    printf("64-bit K2: "); print_hex(k2_64, 8);
    printf("128-bit K1: "); print_hex(k1_128, 16);
    printf("128-bit K2: "); print_hex(k2_128, 16);

    return 0;
}
