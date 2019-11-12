#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifndef __GRAPH_H_
#define __GRAPH_H_

typedef struct Sensor {
    int id;
    float x,y,z;
}Sensor;

//AdjListin her elemanı, LinkedList 
typedef struct AdjListNode{
    int dest;
    struct AdjListNode* next;
}AdjListNode;

typedef struct AdjList{
    //kaç eleman var
    int node_amount;
    //linkedlist
    AdjListNode* head;
}AdjList;

typedef struct Graph{
    int node_amount;
    //bu bildiğin array, array'in indeksi
    AdjList* list;
}Graph;

AdjListNode* new_adj_list_node(int dest);
Graph* create_graph(int node_amount);
void add_edge(Graph* graph,int source,int dest);
Sensor* get_sensors(char* file_name);
float distance(float x1,float y1, float x2, float y2);
void print_sensors(Sensor* s);
Sensor* read_sensors(char* file_name);

float** get_distances(Sensor* s);
Graph* get_graph(Sensor* sensors,int min_dis);

void print_graph(Graph* graph,Sensor* sensors,float** distances);
#endif