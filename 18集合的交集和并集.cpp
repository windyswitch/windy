#include<stdio.h> 
#include <stdlib.h>
#include <stdbool.h>

// �ڵ�Ķ���
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// �����½ڵ�
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        return NULL;
    }
    newNode->data = data;
    newNode->prev = newNode->next = newNode;
    return newNode;
}

// �����½ڵ㵽����
void insertNode(Node** head, int data) {
    Node* newNode = createNode(data);
    if (!(*head)) {
        *head = newNode;
        return;
    }
    newNode->prev = (*head)->prev;
    newNode->next = *head;
    (*head)->prev->next = newNode;
    (*head)->prev = newNode;
}

// ��ʾ����
void displayList(Node* head) {
    if (!head) {
        return;
    }
    Node* current = head;
    do {
        printf("%d ", current->data);
        current = current->next;
    } while (current != head);
    printf("\n");
}

// ���ڵ��Ƿ���������
bool contains(Node* head, int data) {
    if (!head) {
        return false;
    }
    Node* current = head;
    do {
        if (current->data == data) {
            return true;
        }
        current = current->next;
    } while (current != head);
    return false;
}

// ������������Ľ���
Node* intersection(Node* headA, Node* headB) {
    Node* result = NULL;
    Node* currentA = headA;
    if (!headA || !headB) {
        return NULL;
    }
    do {
        if (contains(headB, currentA->data)) {
            insertNode(&result, currentA->data);
        }
        currentA = currentA->next;
    } while (currentA != headA);
    return result;
}

// ������������Ĳ���
Node* unionList(Node* headA, Node* headB) {
    Node* result = NULL;
    Node* current = headA;
    if (!headA && !headB) {
        return NULL;
    }
    if (headA) {
        do {
            insertNode(&result, current->data);
            current = current->next;
        } while (current != headA);
    }
    if (headB) {
        current = headB;
        do {
            if (!contains(result, current->data)) {
                insertNode(&result, current->data);
            }
            current = current->next;
        } while (current != headB);
    }
    return result;
}

// ������
int main() {
    Node* setA = NULL;
    Node* setB = NULL;
    Node* intersec = NULL;
    Node* unionSet = NULL;

    // �ֶ���������
    printf("���뼯��A��Ԫ�أ�-1����:\n");
    while (true) {
        int data;
        scanf("%d", &data);
        if (data == -1) break;
        insertNode(&setA, data);
    }

    printf("���뼯��B��Ԫ�أ�-1����:\n");
    while (true) {
        int data;
        scanf("%d", &data);
        if (data == -1) break;
        insertNode(&setB, data);
    }

    // ��ʾ��ʼ����
    printf("����A: ");
    displayList(setA);
    printf("����B: ");
    displayList(setB);

    // ���㽻���Ͳ���
    intersec = intersection(setA, setB);
    unionSet = unionList(setA, setB);

    // ��ʾ���
    printf("����: ");
    displayList(intersec);
    printf("����: ");
    displayList(unionSet);

    // �ͷ��ڴ�
    // (����ʡ��)

    return 0;
}
