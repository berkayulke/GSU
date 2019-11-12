#include <stdlib.h>
#include <stdio.h>
#include "tree.h"
extern int sensor_amount;

void print_s(Sensor s){
    printf("ID:%i   (%.2f,%.2f,%.2f)\n",s.id,s.x,s.y,s.z);
}

float dist(float x1,float y1){
    return 10.0/3.0; 
}

int main(){
    char file_name[] = "sensor_locations.csv";
    Sensor* sensors; 
    sensors = get_sensor(file_name);
    //print_sensors(sensors);
    float**ar=get_distances(sensors);

    return 0;
}