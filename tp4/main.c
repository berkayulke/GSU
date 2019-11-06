#include "b_tree.h"

void swap_array(int** ar1,int **ar2);

int values[] = {61,60,82,97,50,62,80,85,87,98,99};
// 85 kada insert edebiliyor sonrasında hata veriyor
// Eğer seg fault alırsanız tekrar compile etmeden tekrar çalıştırmayı deneyin
int main(){

    BTree* head = create_dbtree();
    int ar_size = sizeof(values)/sizeof(int);
    for(int i = 0; i < ar_size; i++){
        head = push_dbtree(head,values[i]);
    }
    for(int i = 0 ; i < M-1; i++){
        printf("Root->%i. = %i\n",i,head->values[i]);
    }
    for(int i = 0 ; i < M; i++){
       for(int j = 0 ;j < M-1; j++){
           if(head->childs[i])
               printf("Child%i->%i. = %i\n",i,j,head->childs[i]->values[j]);
        }
    }
    return 0;
}