#include "main.h"
#include <iostream>
#include "../../include/RAJA/usercontrol/Drive-Opcontrol.h"

namespace RAJA{
    
    void tank_drive(pros::Controller &joystick, RAJA::ChassisObject &drive){
        int right_channel = joystick.get_analog(ANALOG_RIGHT_Y); 
        int left_channel = joystick.get_analog(ANALOG_LEFT_Y); 

        if(abs(right_channel) > STANDARD_DEADBAND_ERROR){
            drive.move_right_side(right_channel); 
        } 
        else drive.move_right_side(0); 

        if(abs(left_channel) > STANDARD_DEADBAND_ERROR){
            drive.move_left_side(left_channel); 
        } 
        else drive.move_left_side(0); 
    }

    void arcade_drive(pros::Controller &joystick, RAJA::ChassisObject &drive){
        int right_channel = joystick.get_analog(ANALOG_RIGHT_Y);
        int left_x_channel = joystick.get_analog(ANALOG_LEFT_X); 

        int linear_power = (abs(right_channel) > STANDARD_DEADBAND_ERROR) ? right_channel : 0; 
        int turn_power = (abs(left_x_channel) > STANDARD_DEADBAND_ERROR) ? left_x_channel : 0; 

        drive.move_left_side(linear_power + turn_power);
        drive.move_right_side(linear_power - turn_power);

    }

}
