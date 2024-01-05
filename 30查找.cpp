#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode* insert(TreeNode* root, int key) {
    if (root == NULL) {
        TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
        newNode->data = key;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    if (key < root->data) {
        root->left = insert(root->left, key);
    } else if (key > root->data) {
        root->right = insert(root->right, key);
    }

    return root;
}

int findPath(TreeNode* root, int key) {
    if (root == NULL) {
        return 0;
    }

    printf("%d ", root->data);

    if (key == root->data) {
        return 1;
    } else if (key < root->data) {
        if (findPath(root->left, key)) {
            return 1;
        }
    } else {
        if (findPath(root->right, key)) {
            return 1;
        }
    }

    return 0;
}

void destroyTree(TreeNode* root) {
    if (root != NULL) {
        destroyTree(root->left);
        destroyTree(root->right);
        free(root);
    }
}

int main() {
    TreeNode* root = NULL;
    int n, key;

    printf("Enter the number of nodes in the tree: ");
    scanf("%d", &n);

    printf("Enter the values of the nodes: ");
    for (int i = 0; i < n; ++i) {
        scanf("%d", &key);
        root = insert(root, key);
    }

    printf("Enter the key to find: ");
    scanf("%d", &key);

    printf("Path for %d: ", key);
    if (findPath(root, key)) {
        printf("\n");
    } else {
        printf("Not found\n");
    }

    destroyTree(root);

    return 0;
}
