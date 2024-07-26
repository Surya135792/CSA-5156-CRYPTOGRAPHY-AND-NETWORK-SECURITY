#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
uint64_t des_encrypt(uint64_t plaintext, uint64_t key);
uint64_t des_decrypt(uint64_t ciphertext, uint64_t key);
void pad_data(uint8_t *data, size_t data_len, size_t block_size, uint8_t *padded_data) {
    size_t padding_len = block_size - (data_len % block_size);
    memcpy(padded_data, data, data_len);
    padded_data[data_len] = 0x80; 
    memset(padded_data + data_len + 1, 0, padding_len - 1); 
}

void ecb_mode(uint8_t *plaintext, size_t plaintext_len, uint64_t key, uint8_t *ciphertext) {
    uint64_t block;
    for (size_t i = 0; i < plaintext_len; i += 8) {
        memcpy(&block, plaintext + i, 8);
        block = des_encrypt(block, key);
        memcpy(ciphertext + i, &block, 8);
    }
}

void cbc_mode(uint8_t *plaintext, size_t plaintext_len, uint64_t key, uint64_t iv, uint8_t *ciphertext) {
    uint64_t block, prev_block = iv;
    for (size_t i = 0; i < plaintext_len; i += 8) {
        memcpy(&block, plaintext + i, 8);
        block ^= prev_block;
        block = des_encrypt(block, key);
        memcpy(ciphertext + i, &block, 8);
        prev_block = block;
    }
}

void cfb_mode(uint8_t *plaintext, size_t plaintext_len, uint64_t key, uint64_t iv, uint8_t *ciphertext) {
    uint64_t block, encrypted_iv = iv;
    for (size_t i = 0; i < plaintext_len; i += 8) {
        encrypted_iv = des_encrypt(encrypted_iv, key);
        memcpy(&block, plaintext + i, 8);
        block ^= encrypted_iv;
        memcpy(ciphertext + i, &block, 8);
        encrypted_iv = block;
    }
}

int main() {
    uint64_t key = 0x133457799BBCDFF1;
    uint64_t iv = 0x1234567890ABCDEF;
    uint8_t plaintext[] = "This is a test message for ECB, CBC, and CFB modes.";
    size_t plaintext_len = strlen((char *)plaintext);

    size_t block_size = 8;
    size_t padded_len = ((plaintext_len / block_size) + 1) * block_size;
    uint8_t *padded_plaintext = (uint8_t *)malloc(padded_len);
    pad_data(plaintext, plaintext_len, block_size, padded_plaintext);

    uint8_t *ecb_ciphertext = (uint8_t *)malloc(padded_len);
    uint8_t *cbc_ciphertext = (uint8_t *)malloc(padded_len);
    uint8_t *cfb_ciphertext = (uint8_t *)malloc(padded_len);

    ecb_mode(padded_plaintext, padded_len, key, ecb_ciphertext);
    cbc_mode(padded_plaintext, padded_len, key, iv, cbc_ciphertext);
    cfb_mode(padded_plaintext, padded_len, key, iv, cfb_ciphertext);

    printf("Plaintext: %s\n", plaintext);
    printf("Padded Plaintext: ");
    for (size_t i = 0; i < padded_len; i++) printf("%02X ", padded_plaintext[i]);
    printf("\nECB Ciphertext: ");
    for (size_t i = 0; i < padded_len; i++) printf("%02X ", ecb_ciphertext[i]);
    printf("\nCBC Ciphertext: ");
    for (size_t i = 0; i < padded_len; i++) printf("%02X ", cbc_ciphertext[i]);
    printf("\nCFB Ciphertext: ");
    for (size_t i = 0; i < padded_len; i++) printf("%02X ", cfb_ciphertext[i]);
    printf("\n");

    free(padded_plaintext);
    free(ecb_ciphertext);
    free(cbc_ciphertext);
    free(cfb_ciphertext);

    return 0;
}

uint64_t des_encrypt(uint64_t plaintext, uint64_t key) {

    return plaintext ^ key; 
}

uint64_t des_decrypt(uint64_t ciphertext, uint64_t key) {

    return ciphertext ^ key; 
}
