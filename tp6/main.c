#include <stdlib.h>
#include <stdio.h>
#include "tree.h"
extern int sensor_amount;

int main(){
    char file_name[] = "sensor_locations.csv";
    Sensor* sensors; 
    
    sensors = read_sensors(file_name);
    float**distances = get_distances(sensors);
    Graph* graph = get_graph(sensors);
    
    //print_graph()
    return 0;
}