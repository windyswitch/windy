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

int insert(HashTable* hashTable, const char* phoneNumber, const char* name, const char* address) {
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    strcpy(newNode->phoneNumber, phoneNumber);
    strcpy(newNode->user.name, name);
    strcpy(newNode->user.address, address);

    unsigned int index = hashFunction1(phoneNumber);
    int conflicts = 0;

    while (hashTable->table[index] != NULL) {
        index = (index + 1) % TABLE_SIZE;
        conflicts++;
    }

    hashTable->table[index] = newNode;
    return conflicts;
}

int main() {
    HashTable hashTable;
    initializeHashTable(&hashTable);

    char phoneNumber[15];
    char name[50];
    char address[100];

    int totalConflicts = 0;
    int totalInserts = 0;

    for (int i = 0; i < 3; i++) {  // Insert three test cases
        printf("Enter phone number: ");
        scanf("%s", phoneNumber);

        printf("Enter name: ");
        scanf("%s", name);

        printf("Enter address: ");
        scanf("%s", address);

        int conflicts = insert(&hashTable, phoneNumber, name, address);
        totalConflicts += conflicts;
        totalInserts++;

        printf("Conflicts for this insert: %d\n", conflicts);
    }

    double conflictRate = (double)totalConflicts / totalInserts;

    printf("\nTotal conflicts: %d\n", totalConflicts);
    printf("Total inserts: %d\n", totalInserts);
    printf("Conflict rate: %.2f%%\n", conflictRate * 100);

    return 0;
}
