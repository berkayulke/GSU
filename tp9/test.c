#include "test.h"

StudentNode *create_empty_class()
{
    StudentNode *head = malloc(sizeof(StudentNode));
    head->next = NULL;
    head->prev = NULL;
    head->student = malloc(sizeof(Student));

    head->student->average = 0.0f;
    head->student->name = NULL;
    head->student->surname = NULL;
    for (int i = 0; i < COURS_AMOUNT; i++)
    {
        head->student->notes[i] = 0;
        head->student->credits[i] = F;
    }

    return head;
}

void add_student(StudentNode **head, Student *student)
{
    StudentNode *cur = *head;
    if (is_class_empty(cur))
    {
        Student *temp = cur->student;
        cur->student = student;
        free(temp);
        return;
    }

    while (cur->next)
        cur = cur->next;

    StudentNode *new = malloc(sizeof(StudentNode));
    new->student = student;
    new->prev = cur;
    new->next = NULL;

    cur->next = new;
}

void str_sort(char **names, char **surnames, int size)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (strcmp(names[i], names[j]) < 0)
            {
                char *temp = names[i];
                names[i] = names[j];
                names[j] = temp;

                temp = surnames[i];
                surnames[i] = surnames[j];
                surnames[j] = temp;
            }
}

enum Credit note_to_credit(int note)
{
    if (note < 50)
        return F;
    else if (note < 60)
        return CC;
    else if (note < 70)
        return CB;
    else if (note < 80)
        return BB;
    else if (note < 90)
        return BA;
    else
        return AA;
}

Student *create_student(char *name, char *surname, int *notes, enum Credit *credits, float average)
{
    Student *new = malloc(sizeof(Student));
    new->name = strdup(name);
    new->surname = strdup(surname);

    for (int i = 0; i < COURS_AMOUNT; i++)
    {
        new->notes[i] = notes[i];
        new->credits[i] = credits[i];
    }

    new->average = average;

    return new;
}

int is_class_empty(StudentNode *head)
{
    return (head->student->name == NULL);
}

void print_student(Student *student)
{
    if (!student)
        return;

    printf("Name: %s\n", student->name);
    printf("Surname: %s\n", student->surname);

    printf("Notes: { ");
    for (int i = 0; i++ < COURS_AMOUNT;)
        printf("%i, ", student->notes[i]);

    printf("\b\b }\nCredits: { ");
    for (int i = 0; i++ < COURS_AMOUNT;)
        printf("%i, ", student->credits[i]);

    printf("\b\b }\nAverage: %.2f\n\n", student->average);
}

void print_class(StudentNode *head)
{
    for (StudentNode *cur = head; cur; cur = cur->next)
        print_student(cur->student);
}

void add_student_from_list(StudentNode **head, char **names, char **surnames, int size)
{
    srand(time(NULL));
    str_sort(names, surnames, size);

    int ar[COURS_AMOUNT];
    enum Credit cre[COURS_AMOUNT];
    int mean = 0;
    for (int i = 0; i < size; i++)
    {
        for (int i = 0; i < COURS_AMOUNT; i++)
        {
            ar[i] = rand() % 101;
            cre[i] = note_to_credit(ar[i]);
            mean += cre[i];
        }
        add_student(head, create_student(names[i], surnames[i], ar, cre, mean / COURS_AMOUNT));
    }
}

void encrypt_class(StudentNode **head)
{
    for (StudentNode *cur = *head; cur; cur = cur->next)
        cur->student->average *= cur->student->name[0] * cur->student->surname[0];
}

StudentTree *create_empty_tree()
{
    StudentTree *head = malloc(sizeof(StudentTree));
    head->left = NULL;
    head->right = NULL;

    head->student = malloc(sizeof(Student));
    head->student->average = 0.0f;
    head->student->name = NULL;
    head->student->surname = NULL;
    for (int i = 0; i < COURS_AMOUNT; i++)
    {
        head->student->notes[i] = 0;
        head->student->credits[i] = F;
    }

    return head;
}

void add_student_to_tree(StudentTree **head, Student *student)
{
    StudentTree *cur = *head;
    if (cur->student->name == NULL)
    {
        Student *temp = cur->student;
        cur->student = student;
        free(temp);
        return;
    }
    while (cur)
    {
        if (strcmp(cur->student->name, student->name) < 0)
        {
            if (cur->left)
                cur = cur->left;
            else
            {
                cur->left = create_empty_tree();
                Student *temp = cur->left->student;
                cur->left->student = student;
                free(temp);
                return
            }
        }
        else
        {
            if (cur->right)
                cur = cur->right;
            else
            {
                cur->right = create_empty_tree();
                Student *temp = cur->right->student;
                cur->right->student = student;
                free(temp);
                return
            }
        }
    }
}