#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef __TREE_H_
#define __TREE_H_

enum print_types
{
  PRE,
  IN,
  POST,
  LEVEL
};

typedef struct List
{
  int code;
  char *name;
  struct List *next;
} List;

typedef struct Tree
{
  int code;
  char *name;
  struct Tree *right;
  struct Tree *left;
} Tree;

int max(int n1, int n2);
int power(int base, int pow);
List *get_last(List *head);
List *push(List *head, int new_num, char *new_name);
void print_list(List *head, int space_between, int start_space);

Tree *create_node(int code, char *name);
Tree *find_min(Tree *head);
Tree *find_max(Tree *head);
int find_height(Tree *head);
Tree *get_prev(Tree *head, int value);
Tree *delete_node(Tree *head, int value);
Tree *insert_node(Tree *head, Tree *new);
void print_tree(Tree *head, int order);
List *get_level(Tree *head, int level);
void amazingly_print_tree(Tree *tree_head);
Tree* search_node(Tree* head,int value);

#endif