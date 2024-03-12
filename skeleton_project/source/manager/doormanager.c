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
        
    }else{
        elevio_doorOpenLamp(1);
        removeCurrentFloorFromLine();

        int i = 0;

        while(i < 5000){
            i = i+1;
            usleep(300);
            addToLineIfButton();
            if(elevio_stopButton()){
                stopbutton();
                i = 0;
            }
            while(elevio_obstruction()){
                i = 0;
                addToLineIfButton();
                if(elevio_stopButton()){
                    stopbutton();
                    i = 0;
                }
            }
        }
        elevio_doorOpenLamp(0);
        }
}