#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node* createTree() {
    int value;
    scanf("%d", &value);
    if (value == -1) {
        return NULL;
    }

    struct Node* node = createNode(value);
    node->left = createTree();
    node->right = createTree();
    return node;
}

int isFullTree(struct Node* root) {
    if (root == NULL) {
        return 1;
    }

    if (root->left == NULL && root->right == NULL) {
        return 1;
    }

    if (root->left != NULL && root->right != NULL) {
        return isFullTree(root->left) && isFullTree(root->right);
    }

    return 0;
}

int isCompleteTree(struct Node* root, int index, int node_count) {
    if (root == NULL) {
        return 1;
    }

    if (index >= node_count) {
        return 0;
    }

    return isCompleteTree(root->left, 2 * index + 1, node_count) && isCompleteTree(root->right, 2 * index + 2, node_count);
}

// countNodes ���������Ƴ�main������ȷ������ȫ����������
void countNodes(struct Node* node, int* node_count) {
    if (node == NULL) {
        return;
    }
    (*node_count)++;
    countNodes(node->left, node_count);
    countNodes(node->right, node_count);
}

int main() {
    printf("�밴�մ��ϵ��¡������ҵ�˳����������������Ľڵ�ֵ��-1��ʾ��λ����Ϊ�գ���\n");

    struct Node* root = createTree();

    int node_count = 0;
    countNodes(root, &node_count);

    if (isFullTree(root)) {
        printf("�ö�����������������\n");
    } else {
        printf("�ö�������������������\n");
    }

    if (isCompleteTree(root, 0, node_count)) {
        printf("�ö���������ȫ��������\n");
    } else {
        printf("�ö�����������ȫ��������\n");
    }

    // Add code here to free the allocated memory of the binary tree to prevent memory leaks.

    return 0;
}
