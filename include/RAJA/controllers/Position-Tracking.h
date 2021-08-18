#ifndef POSITION_TRACKING_H_
#define POSITION_TRACKING_H_
#define ODOM_PI 3.1415f
#include "main.h"
#include <memory>
#include <cmath>

extern std::shared_ptr<pros::IMU> _odom_imu;
extern std::shared_ptr<pros::Motor> r_m, l_m; 
extern std::shared_ptr<pros::Rotation> r_odom, l_odom; 
/* 
    We want to have a insert chassis model function into a function in the PositionTracking class
    Then, based on whatever is the model, we will create new sensors in particular for the odometry functions. 

*/
// Within the functions that set up the sensors to be used for odometry, we want to be able to 

class PositionTracking{
    private: 
        float track_length, wheel_size; 

        float x_coord, y_coord, theta; 

        bool using_the_imu, using_rotation_sensor, using_integrated_enc; 
        
        bool tracking_flag; // flag will control position tracking while loop in the "begin_tracking" function
         
    public: 
        PositionTracking(); 

        // all of the measurements will be converted and consistent with inches
        void set_drive_configuration(float track_length, float wheel_size = 4.0); 

        void set_imu(const pros::IMU &imu, int port);

        void set_encoders(const pros::Rotation &r, const pros::Rotation &l, int right_port, int left_port);

        void set_motors(const pros::Motor &r, const pros::Motor &l);

        void begin_tracking(); 

        void stop_tracking(); 

        float get_x() const; // GETTER FUNCTIONS

        float get_y() const; 
        
        float get_theta() const; 

        // Need to figure out the math for this later
        float ticks_to_inches(float ticks);

        float deg_to_radian(float degs); 

};

#endif
