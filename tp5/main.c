#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

extern int xs[],ys[];
extern char* names[];
extern int second_index_ar[];
extern int alpabeth[];
extern int alpa_size;

int main(){

    kd_tree* root = init_tree();

    kd_tree* xd = init_second_tree();
    print_inorder(xd);

    return 0;
}