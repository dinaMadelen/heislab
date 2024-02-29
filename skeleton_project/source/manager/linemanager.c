#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

#include "../driver/elevio.h"


void addToLineIfButton(int line[]){
    if (elevio_callButton(0, BUTTON_CAB) || elevio_callButton(0, BUTTON_HALL_UP)){
        line[0] = TRUE;

    }
    if (elevio_callButton(1, BUTTON_CAB) || elevio_callButton(1, BUTTON_HALL_UP) || elevio_callButton(1, BUTTON_HALL_DOWN)){
        line[1] = TRUE;
    }
    if (elevio_callButton(2, BUTTON_CAB) || elevio_callButton(2, BUTTON_HALL_UP) || elevio_callButton(2, BUTTON_HALL_DOWN)) {
        line[2] = TRUE;
    }
    if (elevio_callButton(3, BUTTON_CAB) || elevio_callButton(3, BUTTON_HALL_DOWN)) {
        line[3] = TRUE;
    }

}

void removeFromLine(int line[]){

}