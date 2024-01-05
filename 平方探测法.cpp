#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

typedef struct {
    char name[50];
    char address[100];
} UserInfo;

typedef struct {
    char phoneNumber[15];
    UserInfo user;
} HashNode;

typedef struct {
    HashNode* table[TABLE_SIZE];
} HashTable;

unsigned int hashFunction(const char* key) {
    unsigned int hash = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hash = hash * 31 + key[i];
    }
    return hash % TABLE_SIZE;
}

unsigned int quadraticProbe(unsigned int index, unsigned int attempt, unsigned int tableSize) {
    return (index + attempt * attempt) % tableSize;
}

void initializeHashTable(HashTable* hashTable) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable->table[i] = NULL;
    }
}

void insert(HashTable* hashTable, const char* phoneNumber, const char* name, const char* address) {
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    strcpy(newNode->phoneNumber, phoneNumber);
    strcpy(newNode->user.name, name);
    strcpy(newNode->user.address, address);

    unsigned int index = hashFunction(phoneNumber);

    unsigned int attempt = 0;
    while (hashTable->table[index] != NULL) {
        index = quadraticProbe(index, ++attempt, TABLE_SIZE);
    }

    hashTable->table[index] = newNode;
}

int search(HashTable* hashTable, const char* phoneNumber, UserInfo* result) {
    unsigned int index = hashFunction(phoneNumber);

    unsigned int attempt = 0;
    while (hashTable->table[index] != NULL && strcmp(hashTable->table[index]->phoneNumber, phoneNumber) != 0) {
        index = quadraticProbe(index, ++attempt, TABLE_SIZE);
    }

    if (hashTable->table[index] != NULL && strcmp(hashTable->table[index]->phoneNumber, phoneNumber) == 0) {
        *result = hashTable->table[index]->user;
        return attempt + 1; // Return the number of probes
    }

    return -1;
}

int main() {
    HashTable hashTable;
    initializeHashTable(&hashTable);

    char phoneNumber[15];
    char name[50];
    char address[100];

    printf("Enter phone number: ");
    scanf("%s", phoneNumber);

    printf("Enter name: ");
    scanf("%s", name);

    printf("Enter address: ");
    scanf("%s", address);

    insert(&hashTable, phoneNumber, name, address);

    UserInfo result;
    int probes = search(&hashTable, phoneNumber, &result);

    if (probes != -1) {
        printf("Data found:\n");
        printf("Name: %s\n", result.name);
        printf("Address: %s\n", result.address);
        printf("Number of probes: %d\n", probes);
    } else {
        printf("Data not found.\n");
    }

    return 0;
}

