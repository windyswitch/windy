#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10
#define TEST_DATA_SIZE 1000 // 调整为你需要的测试数据大小

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

int search(HashTable* hashTable, const char* phoneNumber, UserInfo* result, int* probes) {
    unsigned int index = hashFunction(phoneNumber);

    unsigned int attempt = 0;
    while (hashTable->table[index] != NULL && strcmp(hashTable->table[index]->phoneNumber, phoneNumber) != 0) {
        index = quadraticProbe(index, ++attempt, TABLE_SIZE);
        (*probes)++;
    }

    if (hashTable->table[index] != NULL && strcmp(hashTable->table[index]->phoneNumber, phoneNumber) == 0) {
        *result = hashTable->table[index]->user;
        return 1; // Data found
    }

    return 0; // Data not found
}

float calculateConflictRate(HashTable* hashTable, char** testData, int testDataSize) {
    int conflicts = 0;

    for (int i = 0; i < testDataSize; i++) {
        char name[50];
        char address[100];
        UserInfo result;

        // Generate random name and address for testing (not used in search)
        sprintf(name, "Name%d", i);
        sprintf(address, "Address%d", i);

        int probes = 0;
        int found = search(hashTable, testData[i], &result, &probes);

        if (!found) {
            // Conflict occurred
            conflicts++;
        }
    }

    return (float)conflicts / testDataSize * 100.0;
}

float calculateAverageSearchLength(HashTable* hashTable, char** testData, int testDataSize) {
    int totalProbes = 0;

    for (int i = 0; i < testDataSize; i++) {
        char name[50];
        char address[100];
        UserInfo result;

        // Generate random name and address for testing (not used in search)
        sprintf(name, "Name%d", i);
        sprintf(address, "Address%d", i);

        int probes = 0;
        search(hashTable, testData[i], &result, &probes);

        totalProbes += probes;
    }

    return (float)totalProbes / testDataSize;
}

int main() {
    HashTable hashTable;
    initializeHashTable(&hashTable);

    // Generate and insert test data
    char** testData = (char**)malloc(TEST_DATA_SIZE * sizeof(char*));
    for (int i = 0; i < TEST_DATA_SIZE; i++) {
        testData[i] = (char*)malloc(15 * sizeof(char));
        sprintf(testData[i], "%010d", rand() % 10000000000); // Generate random phone numbers
        insert(&hashTable, testData[i], "RandomName", "RandomAddress");
    }

    // Calculate conflict rate
    float conflictRate = calculateConflictRate(&hashTable, testData, TEST_DATA_SIZE);
    printf("Conflict Rate: %.2f%%\n", conflictRate);

    // Calculate average search length
    float avgSearchLength = calculateAverageSearchLength(&hashTable, testData, TEST_DATA_SIZE);
    printf("Average Search Length: %.2f\n", avgSearchLength);

    // Clean up
    for (int i = 0; i < TEST_DATA_SIZE; i++) {
        free(testData[i]);
    }
    free(testData);

    return 0;
}
