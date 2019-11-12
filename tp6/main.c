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
int i,j;
int main(){
    char file_name[] = "sensor_locations.csv";
    Sensor* sensors; 
    sensors = get_sensor(file_name);
    float**ar=get_distances(sensors);
    print_sensors(sensors);
    for(i=0;i < 70; ++i)
        for(j=0;j<70;++j)
            printf("(%i,%i)->%f\n",i,j,ar[i][j]);
    return 0;
}