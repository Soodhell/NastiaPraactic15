#include <stdbool.h>

struct Student {
    const char* firstName;
    const char* lastName;
    bool gender;
    int age;
    const char* group;
    int mathMark;
    int physicsMark;
    int chemistryMark;

    void (*print)(void*);
};

void printStudent(void*);
void* createStudent(void*);