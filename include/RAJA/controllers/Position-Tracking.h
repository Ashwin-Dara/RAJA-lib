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

            /*
            * Setting the IMU to use. 
            */
            void set_imu(const pros::IMU &imu, int port);

            /*
            * Setting the encoders (Rotation Sensors) to use. 
            */
            void set_encoders(const pros::Rotation &r, const pros::Rotation &l, int right_port, int left_port);

            /*
            * Setting the IMEs to use.
            */
            void set_motors(const pros::Motor &r, const pros::Motor &l);

            /*
            * This function will infinitely loop and is responsible for the position tracking mechanism.
            *
            * USAGE:
            * 1. Create an instance of the Position Tracking Class.
            * 2. Create a wrapper function that will contain the 'begin_tracking' method being called. 
            * 3. Create a task for that wrapper function. 
            * 
            */
            void begin_tracking(); 

            /*
            * Stops active position tracking by setting the flag to false. 
            */
            void stop_tracking(); 

            /*
            * Getter function retrives the x position. 
            */
            float get_x() const; // GETTER FUNCTIONS

            /*
            * Getter function retrieves the y position. 
            */
            float get_y() const; 
            
            /*
            * Getter function retrives theta. 
            */
            float get_theta() const; 

            /*
            * Converts ticks to inches based on the current of the drive. 
            */
            float ticks_to_inches(float ticks);

            /*
            * Converts deg to radians. 
            */
            float deg_to_radian(float degs); 
    };
}

#endif
