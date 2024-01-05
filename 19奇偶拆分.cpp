#include <stdio.h>
#include <stdlib.h>

// ��������ڵ�ṹ
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// ��������
Node *createList() {
    int num;
    printf("�������������У���0�������룩��");
    Node *head = NULL;
    Node *tail = NULL;

    while (scanf("%d", &num) == 1 && num != 0) {
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->data = num;
        newNode->next = NULL;
        
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    
    return head;
}

// ������ֳ�����λ�ú�ż��λ����������
void splitList(Node *L, Node **L1, Node **L2) {
    Node *odd = NULL; // ����λ������ͷָ��
    Node *even = NULL; // ż��λ������ͷָ��
    Node *oddPtr = NULL; // ����λ������βָ��
    Node *evenPtr = NULL; // ż��λ������βָ��
    int count = 1;

    while (L != NULL) {
        // ����λ����ż�Խ��ڵ�����Ӧ������
        if (count % 2 == 1) { // ����λ��
            if (odd == NULL) {
                odd = L;
                oddPtr = L;
            } else {
                oddPtr->next = L;
                oddPtr = oddPtr->next;
            }
        } else { // ż��λ��
            if (even == NULL) {
                even = L;
                evenPtr = L;
            } else {
                evenPtr->next = L;
                evenPtr = evenPtr->next;
            }
        }

        L = L->next;
        count++;
    }

    // �����������β�ڵ�ָ���ÿ�
    if (oddPtr != NULL) {
        oddPtr->next = NULL;
    }
    if (evenPtr != NULL) {
        evenPtr->next = NULL;
    }

    // ���ؽ��
    *L1 = odd;
    *L2 = even;
}

// ��ӡ����
void printList(Node *L) {
    while (L != NULL) {
        printf("%d ", L->data);
        L = L->next;
    }
    printf("\n");
}

// �ͷ�������ռ�ڴ�
void freeList(Node *L) {
    Node *tmp;
    while (L != NULL) {
        tmp = L;
        L = L->next;
        free(tmp);
    }
}

// ���Ժ���
int main() {
    // ��������
    Node *list = createList();

    // �ָ�����Ϊ����λ�ú�ż��λ����������
    Node *oddList, *evenList;
    splitList(list, &oddList, &evenList);

    // ��ӡ���
    printf("L1: ");
    printList(oddList);
    printf("L2: ");
    printList(evenList);

    // �ͷ�������ռ�ڴ�
    freeList(oddList);
    freeList(evenList);

    return 0;
}
