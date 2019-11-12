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
    //buna gerek olmayabilir
    int src;
    AdjListNode* head;
}AdjList;

typedef struct Graph{
    int edge_amount;
    AdjList** list;
}Graph;

AdjListNode* new_adj_list_node(int dest);
Graph* create_graph(int edge_amount);
void add_edge(Graph* graph,int source,int dest);
Sensor* get_sensor(char* file_name);
float distance(float x1,float y1, float x2, float y2);
void print_sensors(Sensor* s);

//void get_distances(float*** ar,Sensor* s);
float** get_distances(Sensor* s);

#endif