#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

extern int xs[],ys[];
extern char* names[];

int main(){
    kd_tree* root = init_tree();
    int i = 3;
    kd_node* search_node = create_node(xs[i],ys[i],'A'+i,names[i]);
    print_inorder(root);
    return 0;
}