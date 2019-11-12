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
    
    for(int i=0;i < 70; ++i)
        for(int j=0;j<70;++j){
            printf("(%i,%i)->%f\n",i,j,ar[i][j]);
    }
    return 0;
}