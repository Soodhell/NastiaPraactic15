#include <stdio.h>

#include "parametrStruct.h"
#include "Tree.h"

#define Tree() initTree()
#define order(a) inOrderTraversal(a);

int main() {

    struct Tree* tree = initTree();
    struct InsertStruct insertStruct = {
            .root = NULL,
            .student = NULL
    };
    struct CreateStudent createStudent1 = {
            .firstName = "Ivan",
            .lastName = "Ivanov",
            .gender = true,
            .age = 22,
            .group = "ISP-206",
            .mathMark = 5,
            .physicsMark = 5,
            .chemistryMark = 5
    };

    insertStruct.student = (struct Student*)tree->createStudent(&createStudent1);
    tree->root = (struct TreeNode*)tree->insert(&insertStruct);

    insertStruct.root = tree->root;

    struct CreateStudent createStudent2 = {
            .firstName = "Natasha",
            .lastName = "Ivanova",
            .gender = false,
            .age = 22,
            .group = "ISP-206",
            .mathMark = 4,
            .physicsMark = 5,
            .chemistryMark = 3
    };

    insertStruct.student = (struct Student*)tree->createStudent(&createStudent2);
    tree->root = (struct TreeNode*)tree->insert(&insertStruct);

    insertStruct.root = tree->root;

    struct CreateStudent createStudent3 = {
            .firstName = "Nikita",
            .lastName = "Dobrunych",
            .gender = true,
            .age = 20,
            .group = "ISP-206",
            .mathMark = 5,
            .physicsMark = 3,
            .chemistryMark = 4
    };

    insertStruct.student = (struct Student*)tree->createStudent(&createStudent3);
    tree->root = (struct TreeNode*)tree->insert(&insertStruct);

    printf("Students sorted by last name:\n");
    tree->writeStudentsToFile("info.txt", tree, 3);

    int count = 0;

    struct TreeNode* nodes = tree->readStudentsFromFile("info.txt", &count);

    for (int i = 0; i < count; ++i) {
        nodes[i].student->print(nodes[i].student);
    }

    return 0;
}