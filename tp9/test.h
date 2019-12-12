#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>

#ifndef __TEST_H_
#define __TEST_H_

#define COURS_AMOUNT 3

enum Credit
{
    F,
    CC,
    CB,
    BB,
    BA,
    AA
};

typedef struct Student
{
    char *name;
    char *surname;
    int notes[COURS_AMOUNT];
    enum Credit credits[COURS_AMOUNT];
    float average;
} Student;

typedef struct StudentNode
{
    Student *student;
    struct StudentNode *next;
    struct StudentNode *prev;
} StudentNode;

typedef struct StudentTree
{
    Student *student;
    struct StudentTree *left;
    struct StudentTree *right;
} StudentTree;

StudentNode *create_empty_class();
void add_student(StudentNode **head, Student *student);
Student *create_student(char *name, char *surname, int *notes, enum Credit *credits, float average);
int is_class_empty(StudentNode *head);

void print_class(StudentNode *head);
void print_student(Student *student);
void print_tree(StudentTree *head);

void str_sort(char **names, char **surnames, int size);
enum Credit note_to_credit(int note);
char *credit_to_string(enum Credit credit);

StudentTree *create_empty_tree();
void add_student_to_tree(StudentTree **head, Student *student);

#endif