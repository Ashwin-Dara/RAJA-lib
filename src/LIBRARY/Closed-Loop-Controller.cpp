#include "main.h"
#include "../../include/RAJA/controllers/Closed-Loop-Controller.h"
#include <iostream>

namespace RAJA{

    // Initializing all of the PID constants in the constructor 
    ClosedLoop::ClosedLoop(float kp, float ki, float kd, float ls, char state):
                        kp(kp), ki(ki), kd(kd), ls(ls), control_mode(state){}


    // Another setter function for the main PID constants
    void ClosedLoop::set_constants(float _kp, float _kd, float _ki, float _ls){
        kp = _kp; 
        ki = _ki; 
        kd = _kd; 
        ls = _ls; 
    }


    // Returns the sign of the input. 
    int ClosedLoop::sign(int x){
        if(x > 0){
            return 1; 
        } 
        else{
            return -1; 
        } 
    }


    // Sets whether or not slew is used and sets the acceleration limit. 
    void ClosedLoop::limit_acceleration(bool state, int max_accel){
        using_slew_rate = state; 
        accel_step = max_accel;
    }


    // Calculates the PID power. What needs to be inputted is the set_point (desired position) and sensor value (current position)
    float ClosedLoop::get_calculated_power(int set_point, float sensor_value){

        // Error: desired location - current location
        int error = set_point - sensor_value; 
        p_power = kp * error; 

        pros::delay(UPDATE_RATE); // sleeping to have a change in time for delta

        // The integral only acculumates within a certain range. 
        if(abs(error) < i_bound && abs(error) > INTERGAL_ERROR_TOLERANCE){
            integral += error; 
        }
        else{
            integral = 0; 
        }
        i_power = ki * integral; 

        // The change in error is the current error (the pahrenthetical expression) minus the previous error
        int delta_error = (set_point - sensor_value) - error; 
        d_power = kd * delta_error; 

        // If the error does not change, this indicates the robot settled. Therefore, we set 'settled' to true. 
        if(abs(delta_error) < SETTLED_TOLERANCE){
            settled = true; 
        } 
        // If the change in power is above what we want it to be, then we will cap the power.
        if(using_slew_rate && abs(delta_error) > accel_step){
            power += (sign(p_power) * ls); 
        }
        else{ // If not, regular power.
            power = p_power + i_power + d_power; 
        }
        return power; 
    }


    // Sets whether or not heading state is to be used. 
    void ClosedLoop::set_heading_state(bool heading_state){
        using_heading_correction = heading_state; 
    }


    // Sets the heading correctionality constant. Higher will lead to a sharper correction. 
    void ClosedLoop::set_heading_multiplier(float heading_multi){
        heading_multiplier = heading_multi; 
    }


    // Need to input the heading error. I.e., the user will input the desired position minus the current position. 
    void ClosedLoop::set_heading_value(float error){
        heading_error = error; 
    }


    // Retrieves if heading correction is being used. 
    bool ClosedLoop::get_heading_state() const{
        if(control_mode == 'L'){
            return true; 
        }
        return using_heading_correction; 
    }


    // Gets whether or not the controller will be used for linear movement. If 'L' is returned that indicates linear movement. 
    char ClosedLoop::get_mode() const{
        return control_mode; 
    }


    // Gets whether or not the drive has settled.
    bool ClosedLoop::has_settled() const{
        return settled; 
    }
}
