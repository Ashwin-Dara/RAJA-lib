#include "main.h"
#include "../../include/RAJA/controllers/Position-Tracking.h"

std::shared_ptr<pros::IMU> _odom_imu;
std::shared_ptr<pros::Motor> r_m, l_m; 
std::shared_ptr<pros::Rotation> r_odom, l_odom; 

PositionTracking::PositionTracking(){
    x_coord = y_coord = theta = track_length = wheel_size = 0; 
    tracking_flag = using_the_imu = using_rotation_sensor = using_integrated_enc = false; 
}

void PositionTracking::set_drive_configuration(float _track_length, float _wheel_size){
    track_length = _track_length; 
    wheel_size = _wheel_size; 
}


// THIS FUNCTION WILL COMPUTE THE COORDINATES BASED OON THE ODOEMTRY EQUATIONS 
// https://www.hmc.edu/lair/ARW/ARW-Lecture01-Odometry.pdf
void PositionTracking::begin_tracking(){

    if(!tracking_flag) {
        tracking_flag = true; 
    }

    while(tracking_flag){
        float curr_s_right, curr_s_left, curr_theta; 
        float delta_s_right, delta_s_left, delta_theta; 

        curr_theta = (using_the_imu) ? _odom_imu->get_rotation() : 0; 
        curr_s_right = (using_rotation_sensor) ? r_odom->get_position() : r_m->get_position(); 
        curr_s_left = (using_rotation_sensor) ? l_odom->get_position() : l_m->get_position(); 

        pros::delay(25);

        delta_s_right = (using_rotation_sensor) ? curr_s_right - r_odom->get_position() : curr_s_right - r_m->get_position(); 
        delta_s_left = (using_rotation_sensor) ? curr_s_left - l_odom->get_position() : curr_s_left - l_m->get_position(); 
        delta_theta = (using_the_imu) ? _odom_imu->get_rotation() - curr_theta : curr_theta + ((delta_s_right - delta_s_left) / (2 * track_length)); 

        float delta_s = (delta_s_left + delta_s_right) / 2; 
        x_coord += delta_s * std::cos(theta + (delta_theta/2));
        y_coord += delta_s * std::sin(theta + (delta_theta/2));
        theta += delta_theta; 
    }
}

void PositionTracking::stop_tracking(){
    tracking_flag = false; 
}

float PositionTracking::get_x() const{
    return x_coord; 
}


float PositionTracking::get_y() const{
    return y_coord; 
}

float PositionTracking::get_theta() const{
    return theta; 
}

float PositionTracking::deg_to_radian(float degs){
    return (ODOM_PI / 180) * degs;
}