#include <stdlib.h>
#include <stdio.h>

#ifndef __B_TREE_H_
#define __B_TREE_H_

#define M 3 

typedef struct BTree
{
  int values[M-1];
  struct BTree* childs[M];
} BTree;

BTree* create_dbtree();
BTree* push_dbtree(BTree* head,int val);
int is_leaf(BTree** head);
void sort_values(int** ar, int array_size);

#endif