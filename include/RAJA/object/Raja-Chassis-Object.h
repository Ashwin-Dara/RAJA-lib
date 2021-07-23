#ifndef CHASSIS_OBJ_H_
#define CHASSIS_OBJ_H_

#include "main.h"

class ChassisObject{
    public: 
        ChassisObject(const )
        void move_right_side(int voltage); 
        void move_left_side(int volatge); 
}; 

void absolute_move_to(const ChassisObject &drive, const ClosedLoop &controller, float sensor_value, int set_point, int timeout=0){
    int manual_timeout = 0; 
    while(!controller.has_settled() || (manual_timeout < timeout && manual_timeout > 0)){

        drive.move_left_side(controller.get_calculated_power(set_point, timeout));
        drive.move_right_side(controller.get_calculated_power(set_point, timeout));

        pros::delay(25);
        manual_timeout += 25; 
    }
}

void relative_move_to(const ChassisObject &drive, const ClosedLoop &controller, float sensor_value, int set_point, int timeout=0){
    absolute_move_to(drive, controller, sensor_value, set_point - sensor_value, timeout);
}

#endif