#include "b_tree.h"
#include <stdlib.h>
#include <stdio.h>

int cmpfunc (const void * a, const void * b) {
   if(*(int*)a == 0){ return *(int*)a;}
   else if (*(int*)b == 0){ return *(int*)b;}
   return ( *(int*)a - *(int*)b );
}

void sort(int* ar[2]){
    qsort(ar,M,sizeof(int),cmpfunc);
}

void swap_array(int** ar1,int **ar2){
    int *tmp = *ar1;
    *ar1 = *ar2;
    *ar2 = tmp;
}

void print_tree(BTree* head){
    printf("Root->");
    for(int i = 0 ; i < M-1; i++){
        printf(" %i",head->values[i]);
    }

    printf("\n");

    for(int i =0; i< M;i++){
        printf("Chl%i->",i);
        if(head->childs[i]){
            print_tree(head->childs[i]);
        }
        printf("\n");
    }
}

void print_root(BTree* head){
    printf("Root->");
    for(int i = 0 ; i < M-1; i++){
        printf(" %i",head->values[i]);
    }
}

BTree* create_dbtree(){    

    BTree* root = malloc(sizeof(BTree));
    root->values[0] = root->values[1] = 0;

    for(int i = 0; i < M ; i ++){
        root->childs[i] = NULL;
        if(i!=M-1)
            root->values[i] = 0;
    }

    return root;
}

int search_dbtree(BTree**head,int search_value){

    if(!head) return 0;

    BTree* root = *head; 

    int child_index = 0;

    for(int i = 0; i < M-1 ; i++){
        //root'un kendi değerlerine bak
        if(root->values[i] == search_value)
            return 1;
        //eğer şimdiki değerden büyükse childin indeksini artsın
        else if(search_value > root->values[i])
            child_index = i+1;
        //eğer şimdiki değerden küçükse bundan bi önceki ile arasında olacak
        //döngüyü durdur bundan önceki indeks child üzerinde arama yap
        else 
            break;
    }

    //çocukta searchi çağır,eğer çocuk boşsa search false döndürecek
    return search_dbtree(&(root->childs[child_index]),search_value);
}

BTree* push_dbtree(BTree* head,int val){
    BTree* root = head;

    //check if root is empty
    if(root->values[0] == 0){
        root->values[0] = val;
        return root;
    }

    //find proper child to add 
    int child_index = 0;
    for(int i = 0; i < M-1 ; i++){
        if(val > root->values[i] && root->values[i]){
            child_index = i+1;
            break;
        }
    }
    BTree* child = root->childs[child_index];
    if(!root->childs[child_index])
        root->childs[child_index] = create_dbtree();
    
    //if child has at least 1 empty spot, fill it 
    if(root->childs[child_index]->values[M-2] == 0){
        //root->childs[child_index] = push_dbtree(root->childs[child_index], val);
        //sort it
        for(int i = 0 ; i < M ; i++){
            if(root->childs[child_index]->values[i] == 0){
                root->childs[child_index]->values[i] = val;
                sort(root->childs[child_index]->values);
                break;
            }
        }
    }
    
    //if child is full
    else{
        //eğer rootta boş yer varsa ona eleman taşıcam
        if(root->values[M-2]==0){
            //bu noktada child'ı bölüp root'a eleman taşı

            //önce ortadaki elemanı bulmak için taşan halini bul
            int over_fill[3] = {child->values[0],child->values[1],val};
            qsort(over_fill,M,sizeof(int),cmpfunc); 

            //root'a ortanca elemanı yükselt ve sırala
            int mean = over_fill[1];
            root->values[M-2] = mean;
            sort(root->values);

            //çocukta sadece bir eleman kalıcak
            root->childs[child_index]->values[0] = over_fill[0];
            for(int i = 1; i < M-1; i++){
                root->childs[child_index]->values[i] = 0;
            }

            //normalde boş olan bi çocuğa taşan çocuktan bir eleman gelicek ve sıralanacak

            root->childs[M-1] = create_dbtree();
            root->childs[M-1]->values[0] = over_fill[2];

            //root'un çocuklarını da değerleri gibi sıralarsam
            //sonunda olması gerektiği hale gelir
            for(int i = 1; i < M ; i++){
                for(int j = 0; j < M-1; j++){
                    //kıyaslamayı her dizinin 0. elemanı için yap
                    //eğer çocuk varsa 0. elemanı da olmalı
                    if(root->childs[i] && root->childs[i+1]){
                        if(root->childs[i]->values[0] > root->childs[i+1]->values[0]){
                            swap_array(root->childs[i]->values,root->childs[i+1]->values);
                        }
                        else if(root->childs[i]->values[0] == 0){
                            swap_array(root->childs[i]->values,root->childs[i+1]->values);
                        }
                    }
                }
            }

        }

    }
    return root;
}