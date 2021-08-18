#include "main.h"
#include "../../include/RAJA/controllers/Position-Tracking.h"

std::shared_ptr<pros::IMU> _odom_imu;
std::shared_ptr<pros::Motor> r_m, l_m; 
std::shared_ptr<pros::Rotation> r_odom, l_odom; 

PositionTracking::PositionTracking(){
    x_coord = y_coord = theta = 0; 
    tracking_flag = using_the_imu = using_rotation_sensor = using_integrated_enc = false; 
}


// THIS FUNCTION WILL COMPUTE THE COORDINATES BASED OON THE ODOEMTRY EQUATIONS 
// https://www.hmc.edu/lair/ARW/ARW-Lecture01-Odometry.pdf
void PositionTracking::begin_tracking(){

    if(!tracking_flag) {
        tracking_flag = true; 
    }

    while(tracking_flag){
        float delta_s, delta_theta, delta_r, delta_l; 
        float curr_s, curr_theta, curr_r, curr_l; 
        
        curr_theta = (using_the_imu) ? _odom_imu->get_rotation() : 0; 
        

        if(using_the_imu) {

            curr_theta

        }
        else{

        }

        if(using_rotation_sensor){

        } 
        else{

        }



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