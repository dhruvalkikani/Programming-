
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
#include "functions.h"
#include "constants.h"

#if 1
    
void zmain(void)
{
    int i = 0;
    int runTime;
    TickType_t start ,end, obstacle;
  
     
    
    Ultra_Start();              //enable ultrasonic sensor
    
    motor_start();              // enable motor controller
    motor_forward(0,0);  
    

    reflectance_start();        //enable reflectance sensor
    reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000); 
    
    IR_Start();                 //enable IR sensor
    
    while(SW1_Read()==1){      // read the user button's input
        vTaskDelay(100);
    }  
      
    run_to_black();
    
    motor_forward(0,0);
    print_mqtt(READY, "maze");
    
    IR_wait();                            //wait for the IR signal
   
    run_to_white();
    
    start = xTaskGetTickCount();                //take the start time
    print_mqtt(START_TIME, "%d", start);
    
 
                        
    while (SW1_Read()==1){  
 
        int d = Ultra_GetDistance();
    
        //turns left for the first 2 obstacles 
        if(d<5 && i <= 1){                                      
          
            BACKWARD;
            TANK_TURN_LEFT;
            i += 1;
            
            obstacle = xTaskGetTickCount();
            print_mqtt(OBSTACLE_TIME, "%d", obstacle);
            
            stay_at_centre();
            motor_forward(30, 700);     //running a bit forward for a proper tankturn
            turn_right();
            stay_at_centre();           //run on the straight line
            
  
        } 
        
        //turns right for the 3rd obstacle
        else if (d < 5) {
            BACKWARD;
            TANK_TURN_RIGHT;

            obstacle = xTaskGetTickCount();
            print_mqtt(OBSTACLE_TIME, "%d", obstacle);
            
            stay_at_centre();
  
            run_to_white();
            run_to_black();
           
            
            motor_forward(30, 700);     //running a bit forward for a proper tankturn
            turn_left();
       
            stay_at_centre();           //run on the straight line            
           
        }
                 
            stay_at_centre();           //run on the straight line            
            FORWARD;     
        
    } 
    
    motor_forward(0,0);                 // stop motors
    
    end = xTaskGetTickCount();
    print_mqtt(STOP_TIME, "%d", end);
    
    runTime = end - start;
    print_mqtt(RUN_TIME, "%d", runTime);       //print the run time
    
    motor_stop();                       // disable motor controller
    
    while(true){
        vTaskDelay(100);
    }
} 
    
#endif  