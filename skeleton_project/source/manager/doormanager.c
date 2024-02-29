#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

#include "../driver/elevio.h"
#include "elevatormanager.h"
#include "linemanager.h"


void doorOpenSequence(){
    int between_floors = betweenFloors();
    if (between_floors){
        printf("Doors cannot open you are between floors");
        stopbutton();
    }else{
        elevio_doorOpenLamp(1);
        removeCurrentFloorFromLine();

        while(elevio_obstruction()){
            usleep(1000);
            addToLineIfButton();
            if(elevio_stopButton()){
                stopbutton();
            }
        }

        for(int i = 0; i < 300; i++){
            usleep(3000);
            addToLineIfButton();
            if(elevio_stopButton()){
                stopbutton();
            }
        }
        elevio_doorOpenLamp(0);
        }
}