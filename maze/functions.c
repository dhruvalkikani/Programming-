
#include <project.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "Motor.h"
#include "Ultra.h"
#include "Nunchuk.h"
#include "Reflectance.h"
#include "Gyro.h"
#include "Accel_magnet.h"
#include "LSM303D.h"
#include "IR.h"
#include "Beep.h"
#include "mqtt_sender.h"
#include <time.h>
#include <sys/time.h>
#include "serial1.h"
#include <unistd.h>
#include <stdlib.h>
#include "constants.h"

//run forward until L3 and R3 detects black
void run_to_black(void) 
{
    struct sensors_ dig;

    do {
        motor_forward(30,10);
        reflectance_digital(&dig);
    } while(!(dig.L3 == BLACK && dig.R3 == BLACK) );
}    


//run forward until L3 and R3 detects white
void run_to_white(void)
{
    struct sensors_ dig;

    do {
        motor_forward(30,10);
        reflectance_digital(&dig);
    } while(!(dig.L3 == WHITE && dig.R3 == WHITE) );
}


//tank turn right
void tank_turn_r(uint8 tank_left, uint8 tank_right, uint32 delay)
{   
    

    SetMotors(0,1, tank_left, tank_right, delay);               //right motor runs backward and the robot takes a quick turn towards right
}


//tank turn left
void tank_turn_l(uint8 tank_left, uint8 tank_right, uint32 delay)
{   
    

    SetMotors(1,0, tank_left, tank_right, delay);               //left motor runs backward and the robot takes a quick turn towards left
}


//use reflectance sensor to stay inside the sumo ring
void stay_inside_ring(void)
{
    struct sensors_ dig;
    
    reflectance_digital(&dig);
    
    int left_right;
    
    left_right = rand()%2+1;                            //save a rondom number to the variable left_right
    
    //stay inside the ring 
    if (dig.L3 == 1 || dig.R3 == 1) {
        
        REVERSE;
        
        if (left_right == 1){                          
            tank_turn_l(100, 100, 265);                 //turn left if the random number is 1
        }else{     
            tank_turn_r(100, 100, 265);                 //turn right if the random number is not 1  
        }
        
    }
    
}

//follow the black line
void stay_at_centre (void) {
    
    struct sensors_ dig; 
    
    
    reflectance_digital(&dig);
    while(!(dig.R3 == BLACK && dig.L3 == BLACK))
    {   
        
        int d = Ultra_GetDistance();
        
        reflectance_digital(&dig);
        if(d < 5) {                                     //if distance is less than 5cm from the obstacle don't execute the 'if' statements                                 
            break;
        }
        else if(dig.R1 == BLACK && dig.L1 == BLACK) {
            FORWARD;
        }
        else if(dig.R1 == BLACK && dig.L1 == WHITE) {
            SLIGHT_RIGHT;
        }
        else if(dig.R1 == WHITE && dig.L1 == BLACK) {
            SLIGHT_LEFT;
        }
        else if(dig.R1 == WHITE && dig.R2 == BLACK) {
            SLIGHT_RIGHT;
        }
        else if(dig.L1 == WHITE && dig.L2 == BLACK) {
            SLIGHT_LEFT;
        }

    }
    
 
}

//function for turning left at the intersection
void turn_left(void)
{
    struct sensors_ dig;
    do {
        tank_turn_l(30,30, 10);
        reflectance_digital(&dig);
    } while(!(dig.L1 == WHITE && dig.R1 == WHITE));
    
    do {
        tank_turn_l(30, 30, 10);
        reflectance_digital(&dig);
    } while(!(dig.L1 == BLACK && dig.R1 == BLACK));
}    

//function for turning right at the intersection
void turn_right(void)
{
    struct sensors_ dig;
    do {
        tank_turn_r(30,30, 10);
        reflectance_digital(&dig);
    } while(!(dig.L1 == WHITE && dig.R1 == WHITE));
    
    do {
        tank_turn_r(30, 30, 10);
        reflectance_digital(&dig);
    } while(!(dig.L1 == BLACK && dig.R1 == BLACK));
    
} 
