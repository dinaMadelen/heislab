#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

#include "../driver/elevio.h"
#include "doormanager.h"
#include "linemanager.h"
int betweenFloors(){
    int floor = elevio_floorSensor();
    if(floor == -1){
        return TRUE;
    }else{
        return FALSE;
    }
}

int stopbutton(){
        
        elevio_stopLamp(1);
        elevio_motorDirection(DIRN_STOP);
        while (elevio_stopButton()){
            usleep(100);
        }
        elevio_stopLamp(0);
        
        printf("Stopbutton pressed");
        removeFloorFromLine(0);
        removeFloorFromLine(1);
        removeFloorFromLine(2);
        removeFloorFromLine(3);
        int is_between_floors = betweenFloors();

        if(is_between_floors == 0){
            doorOpenSequence();
        }

        

        
        while(1){
            usleep(1000);
            addToLineIfButton();
            if ((line[0] == 1) || (line[1] == 1) || (line[2] == 1) || (line[3] == 1)){

                break;
            }
        }

        

    return 0;
}



void startupSequence(){
    
    printf("startup initiating");
    elevio_doorOpenLamp(0);
    elevio_stopLamp(0);

    removeFloorFromLine(0);
    removeFloorFromLine(1);
    removeFloorFromLine(2);
    removeFloorFromLine(3);

    while(betweenFloors()){
        int current_floor = elevio_floorSensor();
        elevio_motorDirection(DIRN_DOWN);
        addToLineIfButton();
        
        if (current_floor != -1){
            elevio_floorIndicator(current_floor);
        }
        /* 
        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            stopbutton();
            
        }*/
        
    }
    elevio_motorDirection(DIRN_STOP);
    }

void goToFloor(int true_next_floor){
    int floor = elevio_floorSensor();
    int next_floor = true_next_floor;

    while(1){
        int current_floor = elevio_floorSensor();

        if (current_floor == next_floor){
                elevio_motorDirection(DIRN_STOP);
                motordirection = 0;
                return;
            }
        
        while (floor < next_floor){
            current_floor = elevio_floorSensor();
            
            elevio_motorDirection(DIRN_UP);
            addToLineIfButton();
            
            if (current_floor != -1){
                elevio_floorIndicator(current_floor);
                true_last_floor = current_floor;
            }
            
            if (current_floor == next_floor){
                elevio_motorDirection(DIRN_STOP);
                motordirection = 0;
                return;
            }
            if ((hallUpLine[1] == 1) && (current_floor == 1)){
                hallUpLine[1] = 0;
                elevio_motorDirection(DIRN_STOP);
                doorOpenSequence();
            }
            if ((hallUpLine[2] == 1) && (current_floor == 2)){
                hallUpLine[2] = 0;
                elevio_motorDirection(DIRN_STOP);
                doorOpenSequence();
            }

            if (elevio_stopButton()){
                /*Må legge til stoppsekvens*/
                motordirection = 1;
                stopbutton();
                next_floor = getNextFloor();
                if(next_floor == true_last_floor){
                    floor = true_last_floor + 10;
                }
                break;
            }
            
            
        }

        while(floor > next_floor){
            current_floor = elevio_floorSensor();
            elevio_motorDirection(DIRN_DOWN);
            addToLineIfButton();

            if (current_floor != -1){
                elevio_floorIndicator(current_floor);
                true_last_floor = current_floor;
            }

            if (current_floor == next_floor){
                elevio_motorDirection(DIRN_STOP);
                motordirection = 0;
                return;
            }

            if ((hallDownLine[1] == 1) && (current_floor == 1)){
                hallDownLine[1] = 0;
                elevio_motorDirection(DIRN_STOP);
                doorOpenSequence();
            }

            if ((hallDownLine[2] == 1) && (current_floor == 2)){
                hallDownLine[2] = 0;
                elevio_motorDirection(DIRN_STOP);
                doorOpenSequence();
            }

            if (elevio_stopButton()){
                motordirection = -1;
                stopbutton();
                next_floor = getNextFloor();
                if(next_floor == true_last_floor){
                    floor = true_last_floor - 10;
                }
                break;
            }
        }
    }
}