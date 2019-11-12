#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "graph.h"
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
        graph->list[i].node_amount = 0;
        graph->list[i].head = NULL;
    }
    return graph;
}

void add_edge(Graph* graph,int source,int dest){
    AdjListNode* node = new_adj_list_node(dest);
    AdjListNode* cursor = graph->list[source].head;
    
    if(!cursor) 
        graph->list[source].head = node;
    else{
        while(cursor->next)
            cursor = cursor->next;
        cursor->next = node;
    }

    graph->list[source].node_amount++;

    node = new_adj_list_node(source);
    cursor = graph->list[dest].head;
    
    if(!cursor)
        graph->list[source].head = node;
    
    else{
    while(cursor->next)
        cursor = cursor->next;
    cursor->next = node;
    }
    graph->list[dest].node_amount++;
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

Graph* matrix_to_graph(Sensor* sensors,float** distances){
    Graph* graph = create_graph(sensor_amount);
    for(int i=0;i < 70; ++i)
        for(int j=i+1;j<70;++j)
            if(distances[i][j] < 30)
                add_edge(graph,i,j);
}

void print_graph(Graph* graph,Sensor* sensors,float** distances){
    for(int i = 0; i < graph->node_amount; i++){
        AdjListNode* cursor = graph->list[i].head;
        Sensor cur_sens = sensors[i];
        
        int adj_counter = 0;
        while(cursor){
            adj_counter++;
            cursor = cursor->next;
        }
        cursor = graph->list[i].head;

        printf("SensorID: %i (%.2f,%.2f) ",i,cur_sens.x,cur_sens.y);
        printf("Merkez Dugume olan uzakligi %f ",distances[0][i]);
        printf("Komsu sayisi %i ",adj_counter);
        printf("Komusularinin IDleri = { ");
        if(!adj_counter)
            printf("Not:Bu sensorun hic komsusu yoktur. Izole dugum\n");
        while(cursor){
            printf("%i, ",cursor->dest);
            cursor = cursor->next;
        }
        printf("}\n");
    }
}

//ar[i][j] değeri i. sensörün j. sensörle arasındaki mesafeyi döndürür
float** get_distances(Sensor* s){
    float** a = malloc(sensor_amount*sizeof(float*));

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
Graph* get_graph(Sensor* sensors,int min_dis){
    float** distances = get_distances(sensors);
    Graph* graph = create_graph(sensor_amount);
    for(int i = 0; i < sensor_amount; ++i)
        for(int j = 0; j < sensor_amount; ++j)
            if(distances[i][j] < min_dis){
                add_edge(graph,i,j);
                //printf("i = %i   j = %i\n",i,j);
            }
    return graph;
}