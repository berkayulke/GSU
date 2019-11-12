#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "tree.h"
int sensor_amount=0;
float distance(float x1,float y1, float x2, float y2){
    float first = x1 - x2;
    first*=first;

    float second = y1-y2;
    second*=second;

    float res = first + second;

    return (float) sqrt( (double) res );

}

AdjListNode* new_adj_list_node(int dest){
    AdjListNode* new_node = malloc(sizeof(AdjListNode));
    new_node->dest = dest;
    new_node->next = NULL;
    return new_node;
}

Graph* create_graph(int node_amount){
    Graph* graph = malloc(sizeof(Graph));
    graph->node_amount = node_amount;
    
    graph->list = malloc(node_amount*sizeof(AdjList));
    for(int i = 0; i < node_amount; ++i){
        graph->list[i].node_amount =0;
        graph->list[i].head = NULL;
    }
    return graph;
}

void add_edge(Graph* graph,int source,int dest){
    AdjListNode* node = new_adj_list_node(dest);
    AdjListNode* cursor = graph->list[source].head;
    
    while(cursor->next)
        cursor = cursor->next;
    cursor->next = node;

    node = new_adj_list_node(source);
    cursor = graph->list[dest].head;
    
    while(cursor->next)
        cursor = cursor->next;
    cursor->next = node;
}

void line_counter(char* file_name){
    FILE* file = fopen(file_name,"r");
    char* c = malloc(1024*sizeof(char));
    while(!feof(file)){
        char* temp = fgets(c,1024,file);
        
        sensor_amount++;
    }
    fclose(file);
}

Sensor* get_sensors(char* file_name){
    int error_check = 0;
    FILE* file = fopen(file_name,"r");
    line_counter(file_name);
    if(!file){
        printf("Couldn't open file!\n");
        return NULL;
    }
    
    if(error_check != 0){
        printf("Couldn't move cursor\n");
        return NULL;
    }
    printf("Total sensor amount = %i\n",sensor_amount);

    int id;
    float x,y,z;
        
    int counter = 0;
    Sensor* sensor_arr = NULL;
    while(!feof(file)){
        printf("counter = %i\n",counter);
        error_check = fscanf(file,"%i,%f,%f,%f\n",&id,&x,&y,&z);
        
        if(error_check != 4){
            printf("Couldn't read file during initializing array! line: %d\n", __LINE__);
            return NULL;
        }

        ++counter;
        Sensor* temp_alloc = realloc(sensor_arr,counter*sizeof(Sensor));
        if(temp_alloc)
            sensor_arr = temp_alloc;
        else{
            printf("Realloc error!\n");
            return NULL;
        }
        sensor_arr[counter-1].id = id;
        sensor_arr[counter-1].x = x;
        sensor_arr[counter-1].y = y;
        sensor_arr[counter-1].z = z; 
    }

    error_check = fclose(file);
    if(error_check != 0){
            printf("Couldn't close file!\n");
            return NULL;
    }

    return sensor_arr;
}

Sensor* read_sensors(char* file_name){
    FILE* file = fopen(file_name,"r");
    if(!file)
        printf("Couldn't open file\n");
    line_counter(file_name);

    Sensor* sensors = malloc(sensor_amount*sizeof(Sensor));

    int id,counter = 0;
    float x,y,z;
    char line[1024];
    if(!fgets(line,1024,file))
        printf("Couldn't read first line \n");
    for(int i = 0; i < sensor_amount; i++){
        fscanf(file,"%i,%f,%f,%f\n",&id,&x,&y,&z);
        sensors[counter].id = id;
        sensors[counter].x = x;
        sensors[counter].y = y;
        sensors[counter].z = z; 
        counter++;
    }

    fclose(file);
    return sensors;
}

void print_sensors(Sensor* s){
    for(int i = 1; i < sensor_amount;i++){
        printf("ID:%i   (%.2f,%.2f,%.2f)\n",
        s[i].id,
        s[i].x * s[i].y,
        s[i].y,
        s[i].z);
    }
}

//ar[i][j] değeri i. sensörün j. sensörle arasındaki mesafeyi döndürür
float** get_distances(Sensor* s){
    float** a = malloc(sensor_amount*sizeof(float*));

    //iki loop'u birleştirince hata veriyor ???
    for(int i = 0; i < sensor_amount;i++)
        a[i] = malloc(sensor_amount*sizeof(float));

    for(int i = 0; i < sensor_amount;i++){
        for(int j = 0; j < sensor_amount; j++){
            float dis = distance(s[i].x,s[i].y,s[j].x,s[j].y);
            a[i][j] = dis;
        }
    }
    return a;
}

//bütün bağları oluşturur
Graph* get_graph(Sensor* sensors){
    float** distances = get_distances(sensors);
    Graph* graph = create_graph(sensor_amount);
    for(int i = 0; i < sensor_amount; ++i){
        for(int j = i+1; j<sensor_amount; ++j){
            if(distances[i][j] < 30){
                add_edge(graph,i,j);
            }
        }
    }
    return graph;
}