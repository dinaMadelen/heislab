#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

#include "driver/elevio.h"
#include "manager/linemanager.h"
#include "manager/elevatormanager.h"
#include "manager/doormanager.h"





int line[4];




/*Står stille betyr definert

*/
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
        doorOpenSequence();

        printf("completed floor jump\n");
        

        goToFloor(1);
        doorOpenSequence();

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
