#ifndef RISING_EDGE_H
#define RISING_EDGE_H
#include "main.h"

bool rising_edge(pros::Controller &joytick, pros::controller_digital_e_t button);
// USAGE 
/* 

    if(rising_edge(joystick, E_CONROLLER_DIGITAL_R1)){
        
    }

*/

#endif
