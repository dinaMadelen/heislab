#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"

#define TRUE 1
#define FALSE 0

int betweenFloors(){
    int floor = elevio_floorSensor();
    if(floor == -1){
        return TRUE;
    }else{
        return FALSE;
    }
}

/*
    Floor må alltid være definert fra før av
*/
void goToFloor(int next_floor){
    int floor = elevio_floorSensor();
    
    while (floor < next_floor){
        int current_floor = elevio_floorSensor();
        elevio_motorDirection(DIRN_UP);

        if (current_floor == next_floor){
            elevio_motorDirection(DIRN_STOP);
            return;
        }
        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            break;
        }
    }

    while(floor > next_floor){
        int current_floor = elevio_floorSensor();
        elevio_motorDirection(DIRN_DOWN);

        if (current_floor == next_floor){
            elevio_motorDirection(DIRN_STOP);
            return;
        }
        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            break;
        }
    }
}

void startupSequence(){
    
    printf("startup initiating");
    int current_floor = elevio_floorSensor();

    while(betweenFloors()){
        elevio_motorDirection(DIRN_DOWN);
        if((current_floor == 0) || (current_floor == 1) || (current_floor == 2) || (current_floor == 3)){
            elevio_motorDirection(DIRN_STOP);

            return;
        }
        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            break;
        }
    }
}
    


/**
 * Denne koden fungerer slik at hvis heisen ikke er i tredje etage vil den gå nedover 
*/

int main(){
    elevio_init();
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");
    int is_between_floors = betweenFloors();
    printf("Is between floors: %d \n",is_between_floors);

    while(1){
        printf("Inside the main while loop\n");

        startupSequence();
        int floor = elevio_floorSensor();
    
        printf("Startup complete\n");
        

        goToFloor(3);

        printf("completed floor jump\n");
        

        goToFloor(1);

        printf("completed floor jump\n");
        

        goToFloor(3);

        break;



        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                elevio_buttonLamp(f, b, btnPressed);
            }
        }

        if(elevio_obstruction()){
            elevio_stopLamp(1);
        } else {
            elevio_stopLamp(0);
        }
        
        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            break;
        }
        
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
}
