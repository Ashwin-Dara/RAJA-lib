#ifndef CHASSIS_OBJ_H_
#define CHASSIS_OBJ_H_
#define UPDATE_RATE_CHASSIS_OBJ 25

#include "main.h"
#include <memory>
#include "../controllers/Closed-Loop-Controller.h"

namespace RAJA{

    /*
    * Internal electronics that will be declared particularily to be used by RAJA lib. 
    * The intention of this was to avoid modifying the current electronics / motors. 
    * I.e., we are making a "copy" of the electronics configuration of the user. 
    */
    extern std::shared_ptr<pros::Motor> rDrive1, rDrive2, lDrive1, lDrive2; 

    class ChassisObject{

        public: 

            /*
            * Constructor. Will require the user to input in their current drive motors so that RAJA can make a model "copy."
            *
            * @param {pros::Motor} m1, m2 - right motors that the user will pass in. rDrive1 and rDrive2 will be "copies" of "m1" and "m2" respectively.
            * @param {pros::Motor} m3, m4 - left motors that the user will pass in. lDrive1 and lDrive2 will be "copies" of "m3" and "m4" respectively.
            */
            ChassisObject(const pros::Motor &m1, const pros::Motor &m2, 
                          const pros::Motor &m3, const pros::Motor &m4);


            /*
            * Moves the right motors (which are m1 and m2) with the power of voltage. The absolute max input is 127. 
            */
            void move_right_side(int voltage); 


            /*
            * Moves the left motors (which are m3 and m4) with the power of voltage. The absolute max input is 127. 
            */
            void move_left_side(int voltage); 

            /*
            * Moves the entire chassis. The absolute max input is 127.
            */
            void move(int voltage); 
    }; 

    /*
    * Will move in the inputted chassis object to a particular position. This is an absolute movement.
    *
    * @parameter {ChassisObject} drive - this is the chassis object that the user will enter for this function.
    * @parameter {ClosedLoop} controller - this is the controller instance that the user will enter. 
    * @parameter {float} sensor_value - this is the sensor that the user wishes to use within the PID controller.
    * @parameter {int} set_point - this is the desired position of the chassis object
    * @parameter {int} timeout=0 - this is the manual timeout in MS for the chassis to settle. 
    */
    void absolute_move_to(ChassisObject &drive, ClosedLoop &controller, float sensor_value, int set_point, int timeout=0);

    /*
    * Moves the inputted chassis object t4o a particular position, but is a relative movement. 
    * Implementation will use the absolute movement function.
    */
    void relative_move_to(ChassisObject &drive, ClosedLoop &controller, float sensor_value, int set_point, int timeout=0);
}

#endif