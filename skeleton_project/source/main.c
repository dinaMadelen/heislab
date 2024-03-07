#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

#include "driver/elevio.h"
#include "manager/linemanager.h"
#include "manager/elevatormanager.h"
#include "manager/doormanager.h"



int main(){
    elevio_init();

    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");
    int is_between_floors = betweenFloors();
    printf("Is between floors: %d \n",is_between_floors);

    while(1){
        printf("Inside the main while loop\n");

        startupSequence();

    
        printf("Startup complete\n");
        while (1){
            addToLineIfButton();
            int next_floor = getNextFloor();
            while (next_floor == -1) {
                addToLineIfButton();
                printf("next floor %d", next_floor);
                next_floor = getNextFloor();
                if(elevio_stopButton()){
                    stopbutton();
                }
            }
            /*printf(" %d ", floorPriority[0]," %d ", floorPriority[1], " %d ", floorPriority[2]," %d ", floorPriority[3]);
            */
            goToFloor(next_floor);
            doorOpenSequence();
            
        }
        break;
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
}
