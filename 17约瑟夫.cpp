#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertNode(struct Node** head, int data) {
    struct Node* newNode = createNode(data);

    if (*head == NULL) {
        *head = newNode;
        newNode->next = *head;
    } else {
        struct Node* temp = *head;
        while (temp->next != *head) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = *head;
    }
}

void deleteNode(struct Node** head, struct Node* target) {
    if (*head == NULL || target == NULL) {
        return;
    }

    if (*head == target) {
        struct Node* lastNode = *head;
        while (lastNode->next != *head) {
            lastNode = lastNode->next;
        }

        if (*head == (*head)->next) {
            free(*head);
            *head = NULL;
        } else {
            lastNode->next = (*head)->next;
            free(*head);
            *head = lastNode->next;
        }
    } else {
        struct Node* temp = *head;
        while (temp->next != *head && temp->next != target) {
            temp = temp->next;
        }

        if (temp->next == target) {
            temp->next = target->next;
            free(target);
        }
    }
}

void josephus(struct Node** head, int k, int totalPeople) {
    if (*head == NULL) {
        printf("The list is empty\n");
        return;
    }

    struct Node* current = *head;
    struct Node* next;

    printf("Elimination sequence: ");
    while (*head != (*head)->next) {
        for (int i = 1; i < k; i++) {
            current = current->next;
        }

        printf("%d ", current->data);

        next = current->next;
        deleteNode(head, current);
        current = next;
    }

    printf("\nLast remaining person: %d\n", (*head)->data);
}

void printList(struct Node* head) {
    if (head == NULL) {
        printf("The list is empty\n");
        return;
    }

    struct Node* temp = head;
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != head);

    printf("\n");
}

int main() {
    struct Node* head = NULL;
    int totalPeople, k, inputData;

    printf("Enter the total number of people: ");
    scanf("%d", &totalPeople);

    printf("Enter the counting interval (k): ");
    scanf("%d", &k);

    printf("Enter the values for the nodes:\n");
    for (int i = 1; i <= totalPeople; i++) {
        insertNode(&head, i);
    }

    printf("Initial list: ");
    printList(head);

    josephus(&head, k, totalPeople);

    return 0;
}

