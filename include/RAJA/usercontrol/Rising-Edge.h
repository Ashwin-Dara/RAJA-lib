#ifndef RISING_EDGE_H
#define RISING_EDGE_H

#include "main.h"

namespace RAJA{
    
    /*
    * Rising Edge Controller. I.e., if a button is held down, the rising_edge function will return true only for one cycle. 
    *
    * @param {pros::Controller} joystick - controller that you wish to use
    * @param {pros::controller_digital_e_t} button - this is the button enum that you wish to retrieve the rising edge state for
    */
    bool rising_edge(pros::Controller &joystick, pros::controller_digital_e_t button);

    /*
    * Example usage. 
    *
    * 1| pros::Controller controller1(E_MASTER_CONTROLLER);
    * 2| if(rising_edge(controller1, DIGITAL_L1); 
    * 3| // If the button is held down, it will still only return true once. Very useful for counts. 
    */
}

#endif
