#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

#include "../driver/elevio.h"
#include "elevatormanager.h"
#include "doormanager.h"


void addToLineIfButton(){
    if (elevio_callButton(0, BUTTON_CAB) || elevio_callButton(0, BUTTON_HALL_UP)){
        line[0] = 1;
        floorPriority[0] = floorPriority[0] + 1;
        
        if(elevio_callButton(0, BUTTON_CAB)){
            elevio_buttonLamp(0, BUTTON_CAB, 1);
        }

        if(elevio_callButton(0, BUTTON_HALL_UP)){
            elevio_buttonLamp(0, BUTTON_HALL_UP, 1);
        }
    }


    if (elevio_callButton(1, BUTTON_CAB) || elevio_callButton(1, BUTTON_HALL_UP) || elevio_callButton(1, BUTTON_HALL_DOWN)){
        line[1] = 1;
        floorPriority[1] = floorPriority[1] + 1;

        if(elevio_callButton(1, BUTTON_CAB)){
            elevio_buttonLamp(1, BUTTON_CAB, 1);
        }
        if(elevio_callButton(1, BUTTON_HALL_UP)){
            elevio_buttonLamp(1, BUTTON_HALL_UP, 1);
        }
        if(elevio_callButton(1, BUTTON_HALL_DOWN)){
            elevio_buttonLamp(1, BUTTON_HALL_DOWN, 1);
        }
    }

    if (elevio_callButton(2, BUTTON_CAB) || elevio_callButton(2, BUTTON_HALL_UP) || elevio_callButton(2, BUTTON_HALL_DOWN)) {
        line[2] = 1;
        floorPriority[2] = floorPriority[2] + 1;
        if(elevio_callButton(2, BUTTON_CAB)){
            elevio_buttonLamp(2, BUTTON_CAB, 1);
        }
        if(elevio_callButton(2, BUTTON_HALL_UP)){
            elevio_buttonLamp(2, BUTTON_HALL_UP, 1);
        }
        if(elevio_callButton(2, BUTTON_HALL_DOWN)){
            elevio_buttonLamp(2, BUTTON_HALL_DOWN, 1);
        }
    }

    if (elevio_callButton(3, BUTTON_CAB) || elevio_callButton(3, BUTTON_HALL_DOWN)) {
        line[3] = 1;
        floorPriority[3] = floorPriority[3] + 1;
        if(elevio_callButton(3, BUTTON_CAB)){
            elevio_buttonLamp(3, BUTTON_CAB, 1);
        }
        if(elevio_callButton(3, BUTTON_HALL_DOWN)){
            elevio_buttonLamp(3, BUTTON_HALL_DOWN, 1);
        }
    }
}

/** funksjon skal bare kjøres når dør er åpen*/
void removeCurrentFloorFromLine(){
    int floor = elevio_floorSensor();
    line[floor] = 0;
    floorPriority[floor] = 0;
    elevio_buttonLamp(floor, BUTTON_CAB, 0);
    if(floor == 1 || floor == 2){
        elevio_buttonLamp(floor, BUTTON_HALL_DOWN, 0);
        elevio_buttonLamp(floor, BUTTON_HALL_UP, 0);
    }
    if (floor == 0){
        elevio_buttonLamp(floor, BUTTON_HALL_UP, 0);
    }

    if (floor == 3){
        elevio_buttonLamp(floor, BUTTON_HALL_DOWN, 0);
    }
    

}

int getNextFloor(){

    while((floorPriority[0] == 0) && (floorPriority[1] == 0) && (floorPriority[2] == 0) && (floorPriority[3] == 0)){
        printf("In zero loop");
        addToLineIfButton();
        usleep(300);
    }

    if ((floorPriority[0] > floorPriority[1]) && (floorPriority[0] > floorPriority[2]) && (floorPriority[0] > floorPriority[3])){
        floorPriority[0] = 0;
        printf("going to 0");
        return 0;
    }
    else if ((floorPriority[1] > floorPriority[0]) && (floorPriority[1] > floorPriority[2]) && (floorPriority[1] > floorPriority[3])){
        floorPriority[1] = 0;
        printf("going to 1");
        return 1;
    }
    else if ((floorPriority[2] > floorPriority[0]) && (floorPriority[2] > floorPriority[1]) && (floorPriority[2] > floorPriority[3])){
        floorPriority[2] = 0;
        printf("going to 2");
        return 2;
    }
    else if ((floorPriority[3] > floorPriority[0]) && (floorPriority[3] > floorPriority[1]) && (floorPriority[3] > floorPriority[2])){
        floorPriority[3] = 0;
        printf("going to 3");
        return 3;
    }
    else if(floorPriority[0] > 0){
        floorPriority[0] = 0;
        printf("going to 0");
        return 0;
    }
    else if(floorPriority[1] > 0){
        floorPriority[1] = 0;
        printf("going to 1");
        return 1;
    }
    else if(floorPriority[2] > 0){
        floorPriority[2] = 0;
        printf("going to 2");
        return 2;
    }
    else if(floorPriority[3] > 0){
        floorPriority[3] = 0;
        printf("going to 3");
        return 3;
    }

}