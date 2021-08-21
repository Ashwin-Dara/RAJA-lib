#include "main.h"
#include <iostream>
#include "../../include/RAJA/usercontrol/Drive-Opcontrol.h"

namespace RAJA{

    void tank_drive(pros::Controller &joystick, RAJA::ChassisObject &drive){
        // Getting the values of the right and left channels
        int right_channel = joystick.get_analog(ANALOG_RIGHT_Y); 
        int left_channel = joystick.get_analog(ANALOG_LEFT_Y); 

        // Ensuring that the channels are pushed past the 'dead zone' 
        int right_power = (abs(right_channel) > STANDARD_DEADBAND_ERROR) ? right_channel : 0; 
        int left_power = (abs(right_channel) > STANDARD_DEADBAND_ERROR) ? right_channel : 0; 

        // Moving the chassis at the calculated powers. 
        drive.move_right_side(right_power); 
        drive.move_left_side(left_power); 
    }


    void arcade_drive(pros::Controller &joystick, RAJA::ChassisObject &drive){
        // Getting values of the channels appropriate for arcade control. 
        int right_channel = joystick.get_analog(ANALOG_RIGHT_Y);
        int left_x_channel = joystick.get_analog(ANALOG_LEFT_X); 

        // Ensuring the channels are past the `dead zone.`
        int linear_power = (abs(right_channel) > STANDARD_DEADBAND_ERROR) ? right_channel : 0; 
        int turn_power = (abs(left_x_channel) > STANDARD_DEADBAND_ERROR) ? left_x_channel : 0; 

        // Powers are assigned for arcade control a differently. 
        drive.move_left_side(linear_power + turn_power);
        drive.move_right_side(linear_power - turn_power);
    }
}
