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

Sensor* get_sensor(char* file_name){
    FILE* file = fopen(file_name,"r");
    // Ilk satırı geç
    char* c;
    fscanf(file,"%[^\n]",c);

    int id = 0;
    float x,y,z;

    Sensor* sensor_arr = malloc(sizeof(Sensor));
    fscanf(file,"%i,%f,%f,%f",&id,&x,&y,&z);
    sensor_arr[0].id = id;
    sensor_arr[0].x = x;
    sensor_arr[0].y = y;
    sensor_arr[0].z = z;
    
    int counter = 1;

    while(!feof(file)){
        fscanf(file,"%i,%f,%f,%f\n",&id,&x,&y,&z);
        ++counter;
        sensor_arr = realloc(sensor_arr,counter*sizeof(Sensor));
        sensor_arr[counter-1].id = id;
        sensor_arr[counter-1].x = x;
        sensor_arr[counter-1].y = y;
        sensor_arr[counter-1].z = z; 
    }
    sensor_amount = counter;
    fclose(file);
    return sensor_arr;
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

Graph* get_graph(Sensor* sensors){
    float** distances = get_distances(sensors);
    Graph* graph = create_graph(sensor_amount);
    for(int i = 0; i < sensor_amount; ++i){
        for(int j = 0; j<sensor_amount; ++j){
            if(distances[i][j] < 30){
                add_edge(graph,i,j);
            }
        }
    }
    return graph;
}