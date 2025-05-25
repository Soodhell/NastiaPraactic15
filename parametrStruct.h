#include <stdbool.h>

struct InsertStruct{
    struct TreeNode* root;
    struct Student* student;
};


struct CreateStudent{
    const char* firstName;
    const char* lastName;
    bool gender;
    int age;
    const char* group;
    int mathMark;
    int physicsMark;
    int chemistryMark;
};