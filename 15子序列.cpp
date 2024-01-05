#include <stdio.h>
#include <stdlib.h>

// ��������ڵ�ṹ
typedef struct Node {
    int data;
    struct Node *prev;
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
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    return head;
}

// �ж��Ƿ��������еĵݹ麯��
int isSubsequence(Node *A, Node *B) {
    // ��� B Ϊ�գ���ʾ�Ѿ������� B ����Ԫ�أ����� 1
    if (B == NULL) {
        return 1;
    }
    
    // ��� A Ϊ�գ��� B ��Ϊ�գ���ʾ A �������˵� B ����ʣ��Ԫ�أ����� 0
    if (A == NULL) {
        return 0;
    }
    
    // �����ǰ A �� B �Ľڵ�ֵ��ȣ������ж���һ���ڵ�
    if (A->data == B->data) {
        return isSubsequence(A->next, B->next);
    }
    
    // �����ǰ A �� B �Ľڵ�ֵ����ȣ������ж� A ����һ���ڵ�
    return isSubsequence(A->next, B);
}

// ���Ժ���
int main() {
    // �������� A
    Node *A = createList();

    // �������� B
    Node *B = createList();

    // �ж� B �Ƿ��� A ��������
    if (isSubsequence(A, B)) {
        printf("��������");
    } else {
        printf("����������");
    }

    // �ͷ�������ռ�ڴ�
    Node *tmp;
    while (A != NULL) {
        tmp = A;
        A = A->next;
        free(tmp);
    }
    while (B != NULL) {
        tmp = B;
        B = B->next;
        free(tmp);
    }

    return 0;
}
