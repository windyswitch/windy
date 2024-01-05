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

int areTreesIdentical(struct TreeNode* root1, struct TreeNode* root2) {
    if (root1 == NULL && root2 == NULL) {
        return 1;
    }

    if (root1 == NULL || root2 == NULL) {
        return 0;
    }

    return (root1->data == root2->data) &&
           areTreesIdentical(root1->left, root2->left) &&
           areTreesIdentical(root1->right, root2->right);
}

int isSubtree(struct TreeNode* root1, struct TreeNode* root2) {
    if (root2 == NULL) {
        return 1;
    }

    if (root1 == NULL) {
        return 0;
    }

    if (areTreesIdentical(root1, root2)) {
        return 1;
    }

    return isSubtree(root1->left, root2) || isSubtree(root1->right, root2);
}

struct TreeNode* buildTree() {
    int data;
    scanf("%d", &data);

    if (data == -1) {
        return NULL;
    }

    struct TreeNode* root = createNode(data);

    printf("Enter left child of %d: ", data);
    root->left = buildTree();

    printf("Enter right child of %d: ", data);
    root->right = buildTree();

    return root;
}

int main() {
    printf("Enter the data for B1 tree (Enter -1 for a NULL node): \n");
    struct TreeNode* B1 = buildTree();

    printf("Enter the data for B2 tree (Enter -1 for a NULL node): \n");
    struct TreeNode* B2 = buildTree();

    if (isSubtree(B1, B2)) {
        printf("包含相同结构子树\n");
    } else {
        printf("不包含相同结构子树\n");
    }

    free(B1);
    free(B2);

    return 0;
}
