#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
extern int sensor_amount;

int main(){
    int min_dis = 10;

    char file_name[] = "sensor_locations.csv";
    Sensor* sensors; 
    
    sensors = read_sensors(file_name);
    float**distances = get_distances(sensors);
    Graph* graph = get_graph(sensors,min_dis);
    printf("%i iletisim mesafes icin:\n",min_dis);
    print_graph(graph,sensors,distances);
    return 0;
}