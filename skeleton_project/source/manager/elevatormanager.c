#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

#include "../driver/elevio.h"
#include "doormanager.h"
#include "linemanager.h"

int stopbutton(){
    if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            printf("Stopbutton pressed");
            elevio_stopLamp(1);
            return 1;
            exit(0);
        }
    return 0;
}

int betweenFloors(){
    int floor = elevio_floorSensor();
    if(floor == -1){
        return TRUE;
    }else{
        return FALSE;
    }
}

void startupSequence(){
    
    printf("startup initiating");
    
    while(betweenFloors()){
        int current_floor = elevio_floorSensor();
        elevio_motorDirection(DIRN_DOWN);
        addToLineIfButton();
        
        if (current_floor != -1){
            elevio_floorIndicator(current_floor);
        }
        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            break;
        }
    }
}

void goToFloor(int next_floor){
    int floor = elevio_floorSensor();
    
    while (floor < next_floor){
        int current_floor = elevio_floorSensor();
        elevio_motorDirection(DIRN_UP);
        addToLineIfButton();
        
        if (current_floor != -1){
            elevio_floorIndicator(current_floor);
        }
        
        if (current_floor == next_floor){
            elevio_motorDirection(DIRN_STOP);
            return;
        }
        if (elevio_stopButton()){
            stopbutton();
        }
        
    }

    while(floor > next_floor){
        int current_floor = elevio_floorSensor();
        elevio_motorDirection(DIRN_DOWN);
        addToLineIfButton();

        if (current_floor != -1){
            elevio_floorIndicator(current_floor);
        }

        if (current_floor == next_floor){
            elevio_motorDirection(DIRN_STOP);
            return;
        }
        if (elevio_stopButton()){
            stopbutton();
        }
    }
}