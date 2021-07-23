#ifndef CLOSED_LOOP_H_
#define CLOSED_LOOP_H_
#include "main.h"


class ClosedLoop{
    protected: 
        float kp, ki, kd, ls; 
        
        int integral, deriv, p_power, i_power, d_power, i_bound; 

        bool using_heading_correction, using_slew_rate; 


    public: 
        ClosedLoop(kp, ki, kd, ls, char state);
        
        void set_linear_constants(float kp, float kd, float ki); 
        
        void set_turn_constants(float kp, float kd, float ki); 

        float get_calculated_power(int set_point, float sensor_value);
        
        void set_heading_state(bool heading_state); 

        void set_heading_multiplier(float heading_multi); 

        void set_heading_value(float offset_value); 

        bool get_heading_state(); 

        bool has_settled(); 
};

#endif