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

enum b_fac
{
  D_LEFT,
  LEFT,
  EQ,
  RIGHT,
  D_RIGHT
};

typedef struct List
{
  int code;
  char *name;
  struct List *next;
  int b_fac;
} List;

typedef struct Tree
{
  int code;
  char *name;
  struct Tree *right;
  struct Tree *left;
  int b_fac;
} Tree;

int max(int n1, int n2);
int min(int n1, int n2);
int power(int base, int pow);

List *get_last(List *head);
List *push(List *head, int new_num, char *new_name);
void print_list(List *head, int space_between, int start_space);

Tree *insert_node(Tree *head, Tree *new);
Tree *create_node(int code, char *name);
Tree *find_min(Tree *head);
Tree *find_max(Tree *head);
int find_height(Tree *head);
Tree *get_prev(Tree *head, int value);
Tree *delete_node(Tree *head, int value);
List *get_level(Tree *head, int level);
void amazingly_print_tree(Tree *tree_head);
void print_tree(Tree *head, int order);
Tree *search_node(Tree *head, int value);

int get_balance_fac(Tree *head);
Tree *left_rotate_avl(Tree *head);
Tree *right_rotate_avl(Tree *head);
Tree *balance_tree(Tree *head);
Tree *insert_avl(Tree *head, Tree *new);
Tree *delete_avl(Tree *head, int value);
int is_balanced(Tree *head);

#endif