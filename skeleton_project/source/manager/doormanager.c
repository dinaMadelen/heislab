#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

#include "../driver/elevio.h"

void doorOpenSequence(){
    int between_floors = betweenFloors();
    if (between_floors){
        printf("Doors cannot open you are between floors");
    }else{
        elevio_doorOpenLamp(1);
        usleep(3000000);
        while(elevio_obstruction()){
            usleep(1000000);
        }
        usleep(3000000);
        elevio_doorOpenLamp(0);
        }
}