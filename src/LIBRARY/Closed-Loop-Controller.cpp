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

    int ClosedLoop::sign(int x){
        if(x > 0){
            return 1; 
        } 
        else{
            return -1; 
        } 
    }

    void ClosedLoop::limit_acceleration(bool state, int max_accel){
        using_slew_rate = state; 
        accel_step = max_accel;
    }

    float ClosedLoop::get_calculated_power(int set_point, float sensor_value){
        int error = set_point - sensor_value; 
        p_power = kp * error; 
        pros::delay(UPDATE_RATE); 

        if(abs(error) < i_bound && abs(error) > INTERGAL_ERROR_TOLERANCE){
            integral += error; 
        }
        else{
            integral = 0; 
        }
        i_power = ki * integral; 

        int delta_error = (set_point - sensor_value) - error; 
        d_power = kd * delta_error; 

        if(abs(delta_error) < SETTLED_TOLERANCE){
            settled = true; 
        } 

        if(using_slew_rate && abs(delta_error) > accel_step){
            power += (sign(p_power) * ls); 
        }
        else{
            power = p_power + i_power + d_power; 
        }

        return power; 
    }

    void ClosedLoop::set_heading_state(bool heading_state){
        using_heading_correction = heading_state; 
    }

    void ClosedLoop::set_heading_multiplier(float heading_multi){
        heading_multiplier = heading_multi; 
    }

    void ClosedLoop::set_heading_value(float error){
        heading_error = error; 
    }

    bool ClosedLoop::get_heading_state() const{

        if(control_mode == 'L'){
            return true; 
        }
        return using_heading_correction; 
    }

    char ClosedLoop::get_mode() const{
        return control_mode; 
    }

    bool ClosedLoop::has_settled() const{
        return settled; 
    }

}
