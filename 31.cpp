#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(char data);
Node* buildTree();
void findPath(Node* root, char target, char path[], int depth);

int main() {
    printf("Please enter the binary tree data:\n");
    Node* root = buildTree();

    char targetNode;
    printf("\nEnter the target node: ");
    scanf(" %c", &targetNode);

    printf("Finding path to node %c:\n", targetNode);
    char path[100];
    findPath(root, targetNode, path, 0);

    free(root);

    return 0;
}

Node* createNode(char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* buildTree() {
    char data;
    scanf(" %c", &data);

    if (data == 'N') {
        return NULL;
    }

    Node* root = createNode(data);

    printf("Enter left subtree for %c:\n", data);
    root->left = buildTree();

    printf("Enter right subtree for %c:\n", data);
    root->right = buildTree();

    return root;
}

void findPath(Node* root, char target, char path[], int depth) {
    if (root == NULL) {
        printf("%c is not in the tree.\n", target);
        return;
    }

    path[depth] = root->data;
    depth++;

    if (root->data == target && root->left == NULL && root->right == NULL) {
        printf("Path: ");
        for (int i = 0; i < depth; i++) {
            printf("%c ", path[i]);
        }
        printf("\n");
    }

    findPath(root->left, target, path, depth);
    findPath(root->right, target, path, depth);
}
