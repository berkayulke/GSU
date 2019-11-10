#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

extern int xs[],ys[];
extern char* names[];
extern int second_index_ar[];
extern int alpabeth[];
extern int alpa_size;

int main(){
    kd_tree* root = init_second_tree();

    kd_node* cases[3];

    cases[0] = create_node(25,25,'X',"Terlikciler Sokagi");
    cases[1] = create_node(14,34,'X',"Ic Cebeci Han");
    cases[2] = create_node(5,27,'X',"Hatip Emin Han");

    for(int i = 0; i < 3; ++i){
        kd_node* nearest = search_coordinate(root,cases[i]);
        print_node(nearest);
    }

    return 0;
}