#include "b_tree.h"

void sort_values(int* ar[2], int array_size){
    int* a = *ar;
    for (int i = 0; i < (array_size - 1); ++i){
      for (int j = 0; j < array_size - 1 - i; ++j ){
           if (a[j] > a[j+1]){
                int temp = a[j+1];
                a[j+1] = a[j];
                a[j] = temp;
            }
        }
    }
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

/*
            //sort values
            int * a = root->values;
            for (int i = 0; i < (M -2); ++i){
                for (int j = 0; j < M- 2 - i; ++j ){
                    if (a[j] > a[j+1] && a[j+1] !=0 ){
                        int temp = a[j+1];
                        a[j+1] = a[j];
                        a[j] = temp;
                    }
                }
            }
*/

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
        if(val > root->values[i])
            child_index = i+1;
        else break;
    }
    BTree* child = root->childs[child_index];
    if(!root->childs[child_index])
        root->childs[child_index] = create_dbtree();
    
    //if child has at least 1 empty spot, fill it 
    if(root->childs[child_index]->values[M-2] == 0){
        root->childs[child_index] = push_dbtree(root->childs[child_index], val);
        //sort it
        int * a = root->childs[child_index]->values;
        for (int i = 0; i < (M -2); ++i){
            for (int j = 0; j < M- 2 - i; ++j ){
                if (a[j] > a[j+1] && a[j+1] !=0 ){
                    int temp = a[j+1];
                    a[j+1] = a[j];
                    a[j] = temp;
                }
            }
        }
    }
    
    //if child is full
    else{
        //eğer rootta boş yer varsa ona eleman taşıcam
        if(root->values[M-2]==0){
            //bu noktada child'ı bölüp root'a eleman taşı
            //önce ortadaki elemanı bulmak için taşan halini sırala
            int over_fill[M] = {child->values[0],child->values[1],val};
        
            //sort it
            int * a = over_fill;
            for (int i = 0; i < (M -2); ++i){
                for (int j = 0; j < M- 2 - i; ++j ){
                    if (a[j] > a[j+1] && a[j+1] !=0 ){
                        int temp = a[j+1];
                        a[j+1] = a[j];
                        a[j] = temp;
                    }
                }
            }

            //root'a ortanca elemanı yükseltmek için nereye gideceğini bul 
            int mean = over_fill[1];
            int mean_index = child_index-1;

            //gideceği yere eklemeden önce bütün değerleri bi sağa kaydır 
            for(int i = M-3; i != mean_index; i--){
                root->values[i+1] = root->values[i];
            }

            //ortancayı yerine koy
            root->values[mean_index] = mean;

            //çocukları da sağa taşı
            for(int i = M-2; i!= child_index; i--){
                root->childs[i+1] = root->childs[i];
            }

            //child indexteki değerleri ve bir sağındakileri yeni değerler ile güncelle
            root->childs[child_index]->values[0] = over_fill[0];
            root->childs[child_index+1]->values[0] = over_fill[2];

            //kalan değerleri 0 yap
            root->childs[child_index]->values[1] = root->childs[child_index]->values[2] = 0;
            root->childs[child_index+1]->values[1] = root->childs[child_index+1]->values[2] = 0;
            
            //büyük bir hata çıkmaması için dua et
        }


    }
    return root;
}