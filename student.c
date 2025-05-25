#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "parametrStruct.h"
#include "student.h"

void printStudent(void* _student) {
    struct Student* student = (struct Student*)_student;
    printf("LastName: %s, FirstName: %s, ", student->lastName, student->firstName);
    printf("Gender: ");
    if (student->gender) printf("male, "); else printf("female, ");
    printf("Age: %d, Group: %s, Math: %d, Physics: %d, Chemistry: %d\n",
           student->age, student->group, student->mathMark,
           student->physicsMark, student->chemistryMark);
}

void* createStudent(void* _createStudent) {

    struct CreateStudent* createStudent = _createStudent;

    struct Student* student = (struct Student*)malloc(sizeof(struct Student));
    student->firstName = createStudent->firstName;
    student->lastName = createStudent->lastName;
    student->gender = createStudent->gender;
    student->age = createStudent->age;
    student->group = createStudent->group;
    student->chemistryMark = createStudent->chemistryMark;
    student->physicsMark = createStudent->physicsMark;
    student->mathMark = createStudent->mathMark;
    student->print = printStudent;
    return student;
}