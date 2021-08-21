#ifndef DRIVE_OPCONTROL_H_
#define DRIVE_OPCONTROL_H_
#define STANDARD_DEADBAND_ERROR 2

#include "main.h"
#include "../object/Chassis-Object.h"

namespace RAJA{

    /*
    * Function that provides tank drive control to the inputted ChassisObject.
    * 
    * @param {pros::Controller} joystick - this is the joystick that the function will retrieve button states and channel inputs from.
    * @param {RAJA::ChassisObject} drive - this is the ChassisObject that the function will control.
    */
    void tank_drive(pros::Controller &joystick, RAJA::ChassisObject &drive);


    /*
    * Function that provides 'arcade' control to the inputted ChassisObject.
    * 
    * @param {pros::Controller} joystick - this is the joystick that the function will retrieve button states and channel inputs from.
    * @param {RAJA::ChassisObject} drive - this is the ChassisObject that the function will control.
    */
    void arcade_drive(pros::Controller &joystick, RAJA::ChassisObject &drive); 
}

#endif