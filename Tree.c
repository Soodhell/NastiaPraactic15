#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "Tree.h"
#include "parametrStruct.h"

void writeStudentTree(void*, FILE*);

void* initTree(){
    struct Tree* tree = malloc(sizeof(struct Tree));

    tree->root = NULL;

    tree->createStudent = createStudent;
    tree->createTreeNode = createTreeNode;
    tree->insert = insert;
    tree->writeStudentsToFile = writeStudentsToFile;
    tree->readStudentsFromFile = readStudentsFromFile;

    return tree;

}

void* insert(void* _insertStruct) {
    struct InsertStruct* insertStruct = _insertStruct;
    if (insertStruct->root == NULL) {
        return createTreeNode(insertStruct->student);
    }

    int cmp = strcmp(insertStruct->student->lastName, insertStruct->root->student->lastName);
    if (cmp < 0) {
        struct InsertStruct insertStruct1 = {
                .root = insertStruct->root->left,
                .student = insertStruct->student
        };
        insertStruct->root->left = insert(&insertStruct1);
    } else {
        struct InsertStruct insertStruct1 = {
                .root = insertStruct->root->right,
                .student = insertStruct->student
        };
        insertStruct->root->right = insert(&insertStruct1);
    }

    return insertStruct->root;
}

void inOrderTraversal(void* _root) {
    struct TreeNode* root = (struct TreeNode*)_root;
    if (root != NULL) {
        inOrderTraversal(root->left);
        root->student->print(root->student);
        inOrderTraversal(root->right);
    }
}

void writeString(FILE* file, const char* str) {
    if (str == NULL) {
        int len = 0;
        fwrite(&len, sizeof(int), 1, file);
        return;
    }
    int len = strlen(str) + 1; // +1 для '\0'
    fwrite(&len, sizeof(int), 1, file);
    fwrite(str, sizeof(char), len, file);
}

void writeStudent(FILE* file, struct TreeNode* node) {
    if (node == NULL) {
        return;
    }

    writeString(file, node->student->firstName);
    writeString(file, node->student->lastName);
    writeString(file, node->student->group);

    fwrite(&node->student->gender, sizeof(bool), 1, file);
    fwrite(&node->student->age, sizeof(int), 1, file);
    fwrite(&node->student->mathMark, sizeof(int), 1, file);
    fwrite(&node->student->physicsMark, sizeof(int), 1, file);
    fwrite(&node->student->chemistryMark, sizeof(int), 1, file);
}

void writeStudentsToFile(const char* filename, struct Tree* tree, int count){
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Failed to open file for writing");
        return;
    }

    fwrite(&count, sizeof(int), 1, file);
    writeStudentTree(tree->root, file);

    fclose(file);
}

void writeStudentTree(void* _root, FILE* filename) {
    struct TreeNode* root = (struct TreeNode*)_root;
    if (root != NULL) {
        writeStudentTree(root->left, filename);
        writeStudent(filename, root);
        writeStudentTree(root->right, filename);
    }
}

char* readString(FILE* file) {
    int len;
    if (fread(&len, sizeof(int), 1, file) != 1) {
        return NULL;
    }

    if (len == 0) {
        return NULL;
    }

    char* str = (char*)malloc(len);
    if (str == NULL) {
        return NULL;
    }

    if (fread(str, sizeof(char), len, file) != len) {
        free(str);
        return NULL;
    }

    return str;
}

struct TreeNode* readStudent(FILE* file) {
    struct TreeNode* node = malloc(sizeof(struct TreeNode));
    node->student = malloc(sizeof (struct Student));

    node->student->firstName = readString(file);
    node->student->lastName = readString(file);
    node->student->group = readString(file);

    fread(&node->student->gender, sizeof(bool), 1, file);
    fread(&node->student->age, sizeof(int), 1, file);
    fread(&node->student->mathMark, sizeof(int), 3, file);

    // Указатель на функцию не сохраняется/восстанавливается
    node->student->print = printStudent;

    return node;
}

// Функция для чтения массива структур из файла
struct TreeNode* readStudentsFromFile(const char* filename, int* outCount) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Failed to open file for reading");
        return NULL;
    }

    // Читаем количество структур
    int count;
    if (fread(&count, sizeof(int), 1, file) != 1) {
        fclose(file);
        return NULL;
    }

    struct TreeNode* students = malloc(count * sizeof(struct TreeNode));
    if (students == NULL) {
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < count; i++) {
        students[i] = *readStudent(file);
    }

    fclose(file);

    if (outCount) {
        *outCount = count;
    }
    return students;
}

void freeStudents(struct TreeNode* node, int count) {
    if (node == NULL) return;

    for (int i = 0; i < count; i++) {
        free((void*)node[i].student->firstName);
        free((void*)node[i].student->lastName);
        free((void*)node[i].student->group);
    }
    free(node);
}
