#ifndef CLOSED_LOOP_H_
#define CLOSED_LOOP_H_
#include "main.h"
#define INTERGAL_ERROR_TOLERANCE 3
#define SETTLED_TOLERANCE 1.5f


class ClosedLoop{
    protected: 

        char control_mode; 

        float kp, ki, kd, ls, power, heading_error, heading_multiplier; 
        
        int integral, deriv, p_power, i_power, d_power, i_bound, accel_step; 

        bool using_heading_correction, using_slew_rate, settled; 


    public: 
        static int sign(int x); 

        ClosedLoop(float kp, float ki, float kd, float ls, char state='L'); 
        
        void set_constants(float _kp, float _kd, float _ki, float _ls); 

        void limit_acceleration(bool state, int max_accel); 
        
        float get_calculated_power(int set_point, float sensor_value);
        
        void set_heading_state(bool heading_state); 

        void set_heading_multiplier(float heading_multi); 

        void set_heading_value(float error); 

        bool get_heading_state() const; 

        char get_mode() const; 

        bool has_settled() const; 
};

#endif