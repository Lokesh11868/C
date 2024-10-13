#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOOM_SIZE 1000 // Size of the bit array
#define NUM_HASH_FUNCTIONS 3 // Number of hash functions

// The bit array for the Bloom filter
unsigned char bloom_filter[BLOOM_SIZE];

// Hash functions
int hash1(const char *str);
int hash2(const char *str);
int hash3(const char *str);

// Bloom filter functions
void add_to_bloom(const char *str);
int is_in_bloom(const char *str);

// Main function to demonstrate the Bloom Filter
int main() {
    // Initialize the bloom filter to 0
    memset(bloom_filter, 0, BLOOM_SIZE);

    // Add some strings to the Bloom filter
    add_to_bloom("hello");
    add_to_bloom("world");
    add_to_bloom("example");

    // Check for some strings in the Bloom filter
    printf("Is 'hello' in bloom filter? %s\n", is_in_bloom("hello") ? "Yes" : "No");
    printf("Is 'test' in bloom filter? %s\n", is_in_bloom("test") ? "Yes" : "No");
    printf("Is 'world' in bloom filter? %s\n", is_in_bloom("world") ? "Yes" : "No");
    printf("Is 'example' in bloom filter? %s\n", is_in_bloom("example") ? "Yes" : "No");

    return 0;
}

// Sample hash functions
int hash1(const char *str) {
    int hash = 5381;
    while (*str) {
        hash = ((hash << 5) + hash) + *str++;
    }
    return hash % BLOOM_SIZE;
}

int hash2(const char *str) {
    int hash = 0;
    while (*str) {
        hash = (hash * 31 + *str++) % BLOOM_SIZE;
    }
    return hash;
}

int hash3(const char *str) {
    int hash = 0;
    while (*str) {
        hash = (hash * 17 + *str++) % BLOOM_SIZE;
    }
    return hash;
}

// Add a string to the Bloom filter
void add_to_bloom(const char *str) {
    int hash1_value = hash1(str);
    int hash2_value = hash2(str);
    int hash3_value = hash3(str);

    bloom_filter[hash1_value] = 1;
    bloom_filter[hash2_value] = 1;
    bloom_filter[hash3_value] = 1;
}

// Check if a string is possibly in the Bloom filter
int is_in_bloom(const char *str) {
    int hash1_value = hash1(str);
    int hash2_value = hash2(str);
    int hash3_value = hash3(str);

    return bloom_filter[hash1_value] && bloom_filter[hash2_value] && bloom_filter[hash3_value];
}
