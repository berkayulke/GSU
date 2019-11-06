#include "b_tree.h"

int values[] = {65,60,82,97,50,62,80,85,87,98,99};
int xvalues[] = {22,15,15,10,111};

int main(){
    
    BTree* head = create_dbtree();
    int ar_size = sizeof(values)/sizeof(int);
    for(int i = 0; i < ar_size; i++){
        head = push_dbtree(head,values[i]);
    }
    print_tree(head);
    return 0;
}