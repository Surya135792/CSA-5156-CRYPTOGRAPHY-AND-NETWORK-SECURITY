#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// English letter frequency (in percentage)
double english_freq[ALPHABET_SIZE] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153,
    0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056,
    2.758, 0.978, 2.360, 0.150, 1.974, 0.074
};

// Function to count the frequency of each letter in the ciphertext
void count_frequency(char *ciphertext, int *freq) {
    for (int i = 0; i < strlen(ciphertext); i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            freq[ciphertext[i] - 'A']++;
        } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            freq[ciphertext[i] - 'a']++;
        }
    }
}

// Function to sort the indices of the frequency array in descending order
void sort_by_frequency(int *freq, int *sorted_indices) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        sorted_indices[i] = i;
    }

    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (freq[sorted_indices[i]] < freq[sorted_indices[j]]) {
                int temp = sorted_indices[i];
                sorted_indices[i] = sorted_indices[j];
                sorted_indices[j] = temp;
            }
        }
    }
}

// Function to generate possible plaintexts
void generate_plaintexts(char *ciphertext, int *sorted_indices, int top_n, char possible_plaintexts[][1000]) {
    char english_sorted[ALPHABET_SIZE] = "etaoinshrdlucmfwypvbgkqjxz";
    
    for (int n = 0; n < top_n; n++) {
        for (int i = 0; i < strlen(ciphertext); i++) {
            if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
                possible_plaintexts[n][i] = english_sorted[(sorted_indices[ciphertext[i] - 'A'] + n) % ALPHABET_SIZE] - 'a' + 'A';
            } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
                possible_plaintexts[n][i] = english_sorted[(sorted_indices[ciphertext[i] - 'a'] + n) % ALPHABET_SIZE];
            } else {
                possible_plaintexts[n][i] = ciphertext[i];
            }
        }
        possible_plaintexts[n][strlen(ciphertext)] = '\0';
    }
}

int main() {
    char ciphertext[1000];
    int top_n;

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';  // Remove the newline character

    printf("Enter the number of top possible plaintexts to display: ");
    scanf("%d", &top_n);

    int freq[ALPHABET_SIZE] = {0};
    int sorted_indices[ALPHABET_SIZE];

    // Count the frequency of each letter in the ciphertext
    count_frequency(ciphertext, freq);

    // Sort the indices of the frequency array in descending order
    sort_by_frequency(freq, sorted_indices);

    // Generate possible plaintexts
    char possible_plaintexts[top_n][1000];
    generate_plaintexts(ciphertext, sorted_indices, top_n, possible_plaintexts);

    // Print the possible plaintexts
    printf("\nTop %d possible plaintexts:\n", top_n);
    for (int i = 0; i < top_n; i++) {
        printf("%d: %s\n", i + 1, possible_plaintexts[i]);
    }

    return 0;
}

