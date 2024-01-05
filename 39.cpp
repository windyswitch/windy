#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* createNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct TreeNode* buildTree() {
    int data;
    printf("Enter node data (or -1 for null): ");
    scanf("%d", &data);

    if (data == -1) {
        return NULL;
    }

    struct TreeNode* newNode = createNode(data);

    printf("Enter left subtree for node %d:\n", data);
    newNode->left = buildTree();

    printf("Enter right subtree for node %d:\n", data);
    newNode->right = buildTree();

    return newNode;
}

int treeHeight(struct TreeNode* root) {
    if (root == NULL) {
        return 0;
    } else {
        int leftHeight = treeHeight(root->left);
        int rightHeight = treeHeight(root->right);
        return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    }
}

int treeDiameter(struct TreeNode* root) {
    if (root == NULL) {
        return 0;
    } else {
        int leftHeight = treeHeight(root->left);
        int rightHeight = treeHeight(root->right);

        int leftDiameter = treeDiameter(root->left);
        int rightDiameter = treeDiameter(root->right);

        return (leftHeight + rightHeight + 1) > (leftDiameter > rightDiameter ? leftDiameter : rightDiameter) ? (leftHeight + rightHeight + 1) : (leftDiameter > rightDiameter ? leftDiameter : rightDiameter);
    }
}

int main() {
    struct TreeNode* root = buildTree();

    int diameter = treeDiameter(root);
    printf("The diameter of the binary tree is: %d\n", diameter);

    free(root);

    return 0;
}
