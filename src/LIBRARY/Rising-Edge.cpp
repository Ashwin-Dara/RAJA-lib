#include "main.h"
#include "../../include/RAJA/usercontrol/Rising-Edge.h"

bool rising_edge(pros::Controller &joystick, pros::controller_digital_e_t button){
    bool current_state = joystick.get_digital(button);
    pros::delay(20);
    return (bool) (!current_state && joystick.get_digital(button)); // Only return otrue if the button in the previous cycle was false and the button is being pressed. 
}

// TESTING ENSURING USAGE PRODUCES NO SYNTAX ERRORS 
/* 
pros::Controller joystick(pros::E_CONTROLLER_MASTER);
bool state = rising_edge(joystick, pros::E_CONTROLLER_DIGITAL_L2); 
*/