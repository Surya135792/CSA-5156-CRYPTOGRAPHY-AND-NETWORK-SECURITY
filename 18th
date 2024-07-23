#include <stdio.h>
#include <stdint.h>
uint64_t initial_key = 0x133457799BBCDFF1;
int PC1[56] = {
    57, 49, 41, 33, 25, 17,  9,
     1, 58, 50, 42, 34, 26, 18,
    10,  2, 59, 51, 43, 35, 27,
    19, 11,  3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
     7, 62, 54, 46, 38, 30, 22,
    14,  6, 61, 53, 45, 37, 29,
    21, 13,  5, 28, 20, 12,  4
};
int key_shifts[16] = {
    1, 1, 2, 2, 2, 2, 2, 2, 
    1, 2, 2, 2, 2, 2, 2, 1
};
int PC2[48] = {
    14, 17, 11, 24,  1,  5,
     3, 28, 15,  6, 21, 10,
    23, 19, 12,  4, 26,  8,
    16,  7, 27, 20, 13,  2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};
uint64_t permute_choice1(uint64_t key) {
    uint64_t permuted_key = 0;
    for (int i = 0; i < 56; i++) {
        permuted_key <<= 1;
        permuted_key |= (key >> (64 - PC1[i])) & 0x01;
    }
    return permuted_key;
}
void split_key(uint64_t key, uint32_t *C, uint32_t *D) {
    *C = (key >> 28) & 0x0FFFFFFF;
    *D = key & 0x0FFFFFFF;
}
uint32_t left_shift(uint32_t key, int shifts) {
    return ((key << shifts) | (key >> (28 - shifts))) & 0x0FFFFFFF;
}
uint64_t permute_choice2(uint32_t C, uint32_t D) {
    uint64_t combined_key = ((uint64_t)C << 28) | D;
    uint64_t subkey = 0;
    for (int i = 0; i < 48; i++) {
        subkey <<= 1;
        subkey |= (combined_key >> (56 - PC2[i])) & 0x01;
    }
    return subkey;
}
int main() {
    uint64_t permuted_key = permute_choice1(initial_key);
    uint32_t C = 0, D = 0;
    split_key(permuted_key, &C, &D);
    uint64_t subkeys[16];
    for (int round = 0; round < 16; round++) {
        C = left_shift(C, key_shifts[round]);
        D = left_shift(D, key_shifts[round]);
        subkeys[round] = permute_choice2(C, D);
    }
    for (int round = 0; round < 16; round++) {
        printf("Subkey %2d: %012lx\n", round + 1, subkeys[round]);
    }
    return 0;
}
