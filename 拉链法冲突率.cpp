#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

typedef struct UserInfo {
    char name[50];
    char address[100];
} UserInfo;

typedef struct HashNode {
    char phoneNumber[15];
    UserInfo user;
    struct HashNode* next;
} HashNode;

typedef struct {
    HashNode* table[TABLE_SIZE];
} HashTable;

unsigned int hashFunction1(const char* key) {
    unsigned int hash = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hash = hash * 31 + key[i];
    }
    return hash % TABLE_SIZE;
}

unsigned int hashFunction2(const char* key) {
    unsigned int hash = 5381;
    int c;

    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash % TABLE_SIZE;
}

void initializeHashTable(HashTable* hashTable) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable->table[i] = NULL;
    }
}

void insert(HashTable* hashTable, const char* phoneNumber, const char* name, const char* address, unsigned int (*hashFunction)(const char*)) {
    unsigned int index = hashFunction(phoneNumber);

    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    strcpy(newNode->phoneNumber, phoneNumber);
    strcpy(newNode->user.name, name);
    strcpy(newNode->user.address, address);
    newNode->next = NULL;

    newNode->next = hashTable->table[index];
    hashTable->table[index] = newNode;
}

int search(HashTable* hashTable, const char* phoneNumber, UserInfo* result, unsigned int (*hashFunction)(const char*)) {
    unsigned int index = hashFunction(phoneNumber);

    HashNode* current = hashTable->table[index];
    while (current != NULL) {
        if (strcmp(current->phoneNumber, phoneNumber) == 0) {
            *result = current->user;
            return 1;
        }
        current = current->next;
    }

    return 0;
}

float calculateConflictRate(HashTable* hashTable, char** testData, int testDataSize, unsigned int (*hashFunction)(const char*)) {
    int conflicts = 0;

    for (int i = 0; i < testDataSize; i++) {
        char phoneNumber[15];
        char name[50];
        char address[100];
        UserInfo result;

        printf("Enter phone number: ");
        scanf("%s", phoneNumber);

        printf("Enter name: ");
        scanf("%s", name);

        printf("Enter address: ");
        scanf("%s", address);

        insert(hashTable, phoneNumber, name, address, hashFunction);

        int found = search(hashTable, phoneNumber, &result, hashFunction);

        if (!found) {
            conflicts++;
        }
    }

    return (float)conflicts / testDataSize * 100.0;
}

float calculateAverageSearchLength(HashTable* hashTable, char** testData, int testDataSize, unsigned int (*hashFunction)(const char*)) {
    int totalProbes = 0;

    for (int i = 0; i < testDataSize; i++) {
        char phoneNumber[15];
        char name[50];
        char address[100];
        UserInfo result;

        printf("Enter phone number to search: ");
        scanf("%s", phoneNumber);

        int probes = 0;
        search(hashTable, phoneNumber, &result, hashFunction);

        totalProbes += probes;
    }

    return (float)totalProbes / testDataSize;
}

int main() {
    HashTable hashTable;
    initializeHashTable(&hashTable);

    int testDataSize;
    printf("Enter the number of data entries: ");
    scanf("%d", &testDataSize);

    char** testData = (char**)malloc(testDataSize * sizeof(char*));
    for (int i = 0; i < testDataSize; i++) {
        testData[i] = (char*)malloc(15 * sizeof(char));
    }

    float conflictRate1 = calculateConflictRate(&hashTable, testData, testDataSize, hashFunction1);
    printf("Conflict Rate (Hash Function 1): %.2f%%\n", conflictRate1);

    float conflictRate2 = calculateConflictRate(&hashTable, testData, testDataSize, hashFunction2);
    printf("Conflict Rate (Hash Function 2): %.2f%%\n", conflictRate2);

    float avgSearchLength1 = calculateAverageSearchLength(&hashTable, testData, testDataSize, hashFunction1);
    printf("Average Search Length (Hash Function 1): %.2f\n", avgSearchLength1);

    float avgSearchLength2 = calculateAverageSearchLength(&hashTable, testData, testDataSize, hashFunction2);
    printf("Average Search Length (Hash Function 2): %.2f\n", avgSearchLength2);

    for (int i = 0; i < testDataSize; i++) {
        free(testData[i]);
    }
    free(testData);

    return 0;
}
