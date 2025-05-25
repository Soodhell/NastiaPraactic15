#include "parametrStruct.h"
#include "node.h"
#include <stdlib.h>

void* createTreeNode(void* _student) {
    struct Student* student = (struct Student*)_student;
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->student = student;
    node->left = NULL;
    node->right = NULL;
    return node;
}