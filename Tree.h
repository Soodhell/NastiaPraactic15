#include "node.h"

struct Tree {
    struct TreeNode* root;

    void* (*createStudent)(void*);
    void* (*createTreeNode)(void*);
    void* (*insert)(void*);
    void (*writeStudentsToFile)(const char*, struct Tree*, int);
    struct TreeNode* (*readStudentsFromFile)(const char*, int*);
};

void* insert(void*);
void inOrderTraversal(void*);
void* initTree();
void writeStudentsToFile(const char*, struct Tree*, int);
struct TreeNode* readStudentsFromFile(const char*, int*);