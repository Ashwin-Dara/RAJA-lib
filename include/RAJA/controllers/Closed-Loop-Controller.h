#ifndef CLOSED_LOOP_H_
#define CLOSED_LOOP_H_
#define INTERGAL_ERROR_TOLERANCE 3
#define SETTLED_TOLERANCE 1.5f
#define UPDATE_RATE 50

#include "main.h"

namespace RAJA{

    class ClosedLoop{

        protected: 
            /* 
            control_mode - 'L' indicates the controller will be used for linear movements. 
            */
            char control_mode; 


            /*
            * kP, kI, kD - constants used in the PID equation. 
            * power - total power calculated by PID controller
            * heading_error - difference between desired yaw and current yaw 
            * heading_multiplier - correctional power constant (works as a P controller)
            */
            float kp, ki, kd, ls, power, heading_error, heading_multiplier; 
            

            /*
            * These essentially are local variables for 'get_calculated_power' function. 
            * The reason these are included as variables here so they can be accessed in different methods in the class.
            */
            int integral, deriv, p_power, i_power, d_power, i_bound, accel_step; 


            /*
            * using_heading_correction - true indicates we wish to apply a heading correction power
            * using_slew_rate - true indicates we wish to 'slew' and cap the controller's acceleration
            * settled - true indicates the robot has settled (the movement is complete or steady state error is reached)
            */ 
            bool using_heading_correction, using_slew_rate, settled; 


            /*
            * Returns the sign of the input.
            *
            * @param {int} x - this is the number to obtain the sign of 
            * @return {int} - sign of the number inputted. 
            */
            static int sign(int x); 


        public: 

            /*
            * Constructor, initialize the PID constants and whether or not the PID is for linear movement. 
            *
            * @parameter {float} kp - kP constant in the PID equation
            * @parameter {float} ki - kI constant in the PID equation
            * @parameter {float} kd - kD constant in the PID equation
            * @parameter {float} ls - max acceleration step of the controller 
            * @parameter {char} state - 'L' indicates the PID is for linear movement. 'L' state enables heading correction.
            */
            ClosedLoop(float kp, float ki, float kd, float ls, char state='L'); 


            /*
            * Similar to constructor. Function will be used to reassign the constants.
            */
            void set_constants(float _kp, float _kd, float _ki, float _ls); 


            /*
            * Sets whether or not to enable slew control.  
            *
            * @param {bool} state - if true, slew control will be enabled 
            * @param {int} max_accel - this is the max slew step for the PID controller
            */
            void limit_acceleration(bool state, int max_accel); 


            /*
            * Calculates the PID power. 
            * 
            * @param {int} set_point - this is the desired target for the PID controller
            * @param {float} sensor_value - this is the current sensor value needed to be entered
            * @return {float} - returns the calculated power of the PID controller
            */
            float get_calculated_power(int set_point, float sensor_value);


            /* 
            * Sets whether or not heading correction is enabled. 
            */
            void set_heading_state(bool heading_state); 


            /* 
            * Sets the heading correction error multiplier (p constant).
            */
            void set_heading_multiplier(float heading_multi); 


            /*
            * Sets the error of the heading. E.g., set_heading_value(90 - imu.get_rotation()) would set an error of 90 minus the current yaw. 
            */
            void set_heading_value(float error); 


            /*
            * Gets whether or not the heading correction is true. 
            */
            bool get_heading_state() const; 


            /*
            * Gets the mode of the controller. 'L' indicates that the control is linear. 
            */
            char get_mode() const; 


            /*
            * Gets whether or not the controller has settled (either reached target or encounters steady state error).
            */
            bool has_settled() const; 
    };
    
}

#endif