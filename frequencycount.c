#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 100
#define INITIAL_TABLE_SIZE 100

// Define a structure to hold a word and its frequency
typedef struct {
    char word[MAX_WORD_LENGTH];
    int frequency;
} WordEntry;

// Define a structure for the hash table
typedef struct {
    WordEntry *entries;
    int size;
    int count;
} HashTable;

// Function prototypes
HashTable* create_table(int size);
void insert_word(HashTable *table, const char *word);
int hash_function(const char *word, int size);
void print_table(HashTable *table);
void free_table(HashTable *table);
void normalize_word(char *word);

int main() {
    char paragraph[10000];
    HashTable *table;
    char word[MAX_WORD_LENGTH];
    int i, j;

    // Read the paragraph from the user
    printf("Enter a paragraph: ");
    fgets(paragraph, sizeof(paragraph), stdin);

    // Create a hash table for word frequencies
    table = create_table(INITIAL_TABLE_SIZE);

    // Tokenize the paragraph and insert words into the hash table
    i = 0;
    while (sscanf(paragraph + i, "%s", word) == 1) {
        normalize_word(word);
        if (strlen(word) > 0) {
            insert_word(table, word);
        }
        i += strlen(word) + 1; // Move to the next token
    }

    // Print the word frequencies
    printf("Word Frequencies:\n");
    print_table(table);

    // Free the hash table
    free_table(table);

    return 0;
}

// Function to create a hash table
HashTable* create_table(int size) {
    HashTable *table = (HashTable*)malloc(sizeof(HashTable));
    table->size = size;
    table->count = 0;
    table->entries = (WordEntry*)calloc(size, sizeof(WordEntry));
    return table;
}

// Function to normalize a word (convert to lowercase and remove punctuation)
void normalize_word(char *word) {
    char temp[MAX_WORD_LENGTH];
    int i, j = 0;
    for (i = 0; word[i]; i++) {
        if (isalpha(word[i])) {
            temp[j++] = tolower(word[i]);
        }
    }
    temp[j] = '\0';
    strcpy(word, temp);
}

// Hash function for the hash table
int hash_function(const char *word, int size) {
    unsigned long hash = 5381;
    int c;
    while ((c = *word++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % size;
}

// Function to insert a word into the hash table
void insert_word(HashTable *table, const char *word) {
    int index = hash_function(word, table->size);
    while (table->entries[index].frequency > 0 && strcmp(table->entries[index].word, word) != 0) {
        index = (index + 1) % table->size;
    }
    if (table->entries[index].frequency == 0) {
        strcpy(table->entries[index].word, word);
    }
    table->entries[index].frequency++;
}

// Function to print the hash table
void print_table(HashTable *table) {
    for (int i = 0; i < table->size; i++) {
        if (table->entries[i].frequency > 0) {
            printf("%s: %d\n", table->entries[i].word, table->entries[i].frequency);
        }
    }
}

// Function to free the hash table
void free_table(HashTable *table) {
    free(table->entries);
    free(table);
}
