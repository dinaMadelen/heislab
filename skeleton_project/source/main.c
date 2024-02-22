#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"


void goToFloor(int floor, int next_floor){
    int current_floor = elevio_floorSensor();

    if (current_floor == next_floor){
        elevio_motorDirection(DIRN_STOP);
        return 0;
    }
    if (floor < next_floor){
        elevio_motorDirection(DIRN_UP);

    }
    if (floor > next_floor){
        elevio_motorDirection(DIRN_DOWN);

    }
}

void startupSequence(){
    int current_floor = elevio_floorSensor();
    if((current_floor =! 1) && (current_floor =! 2) && (current_floor =! 3) && (current_floor != 4)){
        elevio_motorDirection(DIRN_DOWN);
    }

    if((current_floor == 1) && (current_floor == 2) && (current_floor == 3) && (current_floor == 4)){
        elevio_motorDirection(DIRN_STOP);
        /** 
         * Funksjonen får ikke exite koden hvis vi ikke er i en definert tilstand
        */
        return 0;
    }
}

/**
 * Denne koden fungerer slik at hvis heisen ikke er i tredje etage vil den gå nedover 
*/
int main(){
    elevio_init();
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    elevio_motorDirection(DIRN_UP);

    while(1){
        int floor = elevio_floorSensor();

        

        startupSequence();
        goToFloor(floor, 3);

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
