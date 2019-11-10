#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tree.h"

int xs[] = {16,5,4,6,3,4,4,5,16,25,32,39,46,45,45,44,32,26};
int ys[] = {43,33,22,17,10,5,4,2,3,2,3,2,7,13,17,24,29,31};
char* names[] = {"ORUCULER","CEBECI HAN","LUTFULLAH",
"YORGANCILAR","BODRUM HAN","FESCILER","HACI HUSNU",
"BEYAZIT","CARSIKAPI","SOGUCLU HAN","MERDIVENLI", 
"KURKCUCLER", "NURUOSMANIYE","SANDAL BEDESTENI",
"KILITCILER","MAHMUT PASA", "MERCAN", "TACIRLER"};

int max(int a,int b){
    if( a > b)
        return a;
    return b;
}

kd_node* create_node(int x,int y, char index,char* name){
    kd_node* node = malloc(sizeof(kd_node));
    node->x = x;
    node->y = y;
    node->index = index;
    node->name = strdup(name);
    return node;
}

kd_tree* create_empty_tree(){
    kd_tree* root = malloc(sizeof(kd_tree));
    
    root->node = NULL;
    root->left = NULL;
    root->right = NULL;

    return root;
}

kd_tree* create_tree(int x,int y, char index,char* name){
    kd_tree* root = create_empty_tree();
    root->node = create_node(x,y,index,name);
    return root;
}

int is_leaf(kd_tree* root){
    if(!root) return 1;
    if(root->left||root->right)
        return 0;
    return 1;
}

int level(kd_tree* root){
    if(is_leaf(root))
        return 1;
    else 
        return 1 + max(level(root->left),level(root->right));
}

kd_tree* insert(kd_tree* root,kd_node* node){
    if(!root){
        kd_tree* new = create_empty_tree();
        new->node = node;
        return new;
    }
    if(1){
        if(node->x < root->node->x)
            root->left = insert(root->left,node);
        else
            root->right = insert(root->right,node);
    }
    else{
        if(node->y < root->node->y)
            root->left = insert(root->left,node);
        else
            root->right = insert(root->right,node);
    }
}

kd_tree* init_tree(){
    int size = sizeof(xs)/sizeof(int);
    int size2 = sizeof(names)/sizeof(char*);

    kd_tree* root = create_tree(28,16,'T',"CEVAHIR BEDESTENI MERKEZ");
    for(int i = 0; i < size; i++){
        kd_node* node = create_node(xs[i],ys[i],'A' + i,names[i]);
        root = insert(root,node);
        printf("Basarıyla eklendi:  %i,%i,%c,%s\n",xs[i],ys[i],'A' + i,names[i]);
    }
    return root;
}

kd_node* search_by_name(kd_tree* root,char* name){
    if(!root) 
        return NULL;
    if(!strcmp(root->node->name,name)){
        return root->node;
    }
    else{
        kd_node* left_res = search_by_name(root->left,name);
        kd_node* right_res = search_by_name(root->right,name);
        if(left_res) 
            return left_res;
        return right_res;
    }
}

kd_node* search_by_index(kd_tree* root,char index){
    if(!root) 
        return NULL;
    if(root->node->index == index){
        return root->node;
    }
    else{
        kd_node* left_res = search_by_index(root->left,index);
        kd_node* right_res = search_by_index(root->right,index);
        if(left_res) 
            return left_res;
        return right_res;
    }
}

void print_inorder(kd_tree* root){
    if(!root)
        return;
    print_inorder(root->left);
    kd_node* cur = root->node;
    printf("(%.2i,%.2i) '%c' %s\n",cur->x,cur->y,cur->index,cur->name);
    print_inorder(root->right);
}

void print_preorder(kd_tree* root){
    if(!root)
        return;
    kd_node* cur = root->node;
    printf("(%.2i,%.2i) '%c' %s\n",cur->x,cur->y,cur->index,cur->name);
    print_inorder(root->left);
    print_inorder(root->right);
}

void print_postorder(kd_tree* root){
    if(!root)
        return;
    print_inorder(root->left);
    print_inorder(root->right);
    kd_node* cur = root->node;
    printf("(%.2i,%.2i) '%c' %s\n",cur->x,cur->y,cur->index,cur->name);
}