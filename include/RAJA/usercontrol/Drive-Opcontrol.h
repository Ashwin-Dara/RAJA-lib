#ifndef DRIVE_OPCONTROL_H_
#define DRIVE_OPCONTROL_H_
#define STANDARD_DEADBAND_ERROR 2

#include "main.h"
#include "../object/Chassis-Object.h"

void tank_drive(pros::Controller &joystick, ChassisObject &drive);

void arcade_drive(pros::Controller &joystick, ChassisObject &drive); 

#endif