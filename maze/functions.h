
#include "project.h"

void run_to_black(void) ;       //run forward towards black track

void run_to_white(void);        //run forward towards white area

//tankturn right
void tank_turn_r(uint8 tank_left, uint8 tank_right, uint32 delay);

//tankturn left
void tank_turn_l(uint8 tank_left, uint8 tank_right, uint32 delay);

void stay_inside_ring(void);    //robot stays inside the ring

void stay_at_centre(void);      //follow the black track

void turn_left(void);           //turn left at the intersection

void turn_right(void);          //turn right at the intersection