#include "student.h"

struct TreeNode {
    struct Student* student;
    struct TreeNode* left;
    struct TreeNode* right;
};

void* createTreeNode(void*);