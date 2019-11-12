#include <stdlib.h>
#include <stdio.h>
#include "tree.h"
extern int sensor_amount;

//bu değerli forda tanımlayınca hata veriyor ???
int i,j;
int main(){
    char file_name[] = "sensor_locations.csv";
    Sensor* sensors; 
    sensors = get_sensor(file_name);
    float**ar=get_distances(sensors);
    print_sensors(sensors);
    for(i=0;i < 70; ++i)
        for(j=0;j<70;++j){
            printf("(%i,%i)->%f\n",i,j,ar[i][j]);
    }
    return 0;
}