#include <stdlib.h>
#include <stdio.h>
#include "tree.h"
extern int sensor_amount;

//bu değerli forda tanımlayınca hata veriyor ???
int main(){
    char file_name[] = "sensor_locations.csv";
    Sensor* sensors; 
    sensors = read_sensors(file_name);
    float**ar=get_distances(sensors);
    

    return 0;
}