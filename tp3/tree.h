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

Tree *create_node(int code, char *name);
Tree *find_min(Tree *head);
Tree *find_max(Tree *head);
Tree *delete_node(Tree *head, int value);
void amazingly_print_tree(Tree *tree_head);

#endif