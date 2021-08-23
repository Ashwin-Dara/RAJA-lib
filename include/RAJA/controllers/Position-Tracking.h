#ifndef POSITION_TRACKING_H_
#define POSITION_TRACKING_H_
#define ODOM_PI 3.1415f
#include "main.h"
#include <memory>
#include <cmath>

namespace RAJA{
    /*
    * These sensors will be used internally by the PositionTracking class. They will be configured by passing the original electronics. 
    */
    extern std::shared_ptr<pros::IMU> _odom_imu; // IMU sensor

    extern std::shared_ptr<pros::Motor> r_m, l_m; // Integrated Motor Encoders

    extern std::shared_ptr<pros::Rotation> r_odom, l_odom; // Dedicated Rotation Sensors

    class PositionTracking{
        private: 

            /*
            * These variables will be used within the position tracking equations. 
            *
            * In particular, this was the lecture that was used to construct the 'begin_tracking' function.
            * Source: https://www.hmc.edu/lair/ARW/ARW-Lecture01-Odometry.pdf
            *
            * Summary: 
            * The x position is given by (displacement) * ( cos(theta + ( change in theta / 2) ) )
            * The y position is given by the same equation except that cosine is a sine. 
            * Theta will be calculated likely through the IMU. 
            *
            * EVERYTHING WILL BE TRACKED IN INCHES
            */
            float track_length, wheel_size, x_coord, y_coord, theta; 


            /* 
            * These flags determine what sensors the user is using.
            */
            bool using_the_imu, using_rotation_sensor, using_integrated_enc; 
            

            /* 
            * This controls the 'begin_tracking' function's while loop. 
            */
            bool tracking_flag; 

        public: 

            /*
            * Constructor initializes all the private variables, and sets them equal to 0. 
            */
            PositionTracking(); 

            /*
            * Setting the track length of the drive alongside the wheel size. 
            */
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
}

#endif
