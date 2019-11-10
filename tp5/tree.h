#include <stdlib.h>
#include <stdio.h>

#ifndef __B_TREE_H_
#define __B_TREE_H_

typedef struct kd_node {
    int x;
    int y;
    char index;
    char* name;
}kd_node;

typedef struct kd_tree{
    kd_node* node;
    struct kd_tree* left;
    struct kd_tree* right;
}kd_tree;

kd_tree* create_empty_tree();
kd_node* create_node(int x,int y, char index,char* name);
kd_tree* create_tree(int x,int y, char index,char* name);

int is_leaf(kd_tree* root);
int level(kd_tree* root);

kd_tree* insert(kd_tree* root,kd_node* node);
kd_tree* init_tree();

kd_node* search_by_name(kd_tree* root,char* name);
kd_node* search_by_index(kd_tree* root,char index);

void print_inorder(kd_tree* root);
void print_preorder(kd_tree* root);
void print_postorder(kd_tree* root);

#endif