#include "main.h"
#include "../../include/RAJA/controllers/Position-Tracking.h"

namespace RAJA{
    
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

    void PositionTracking::set_imu(const pros::IMU &imu, int port){
        _odom_imu = std::make_shared<pros::IMU>(port);
    }

    void PositionTracking::set_encoders(const pros::Rotation &r, const pros::Rotation &l, int right_port, int left_port){
        r_odom = std::make_shared<pros::Rotation>(right_port); 
        l_odom = std::make_shared<pros::Rotation>(left_port);
    }

    void set_motors(const pros::Motor &r, const pros::Motor &l){
        r_m = std::make_shared<pros::Motor>(r.get_port(), r.get_gearing(), r.is_reversed(), pros::E_MOTOR_ENCODER_DEGREES);
        l_m = std::make_shared<pros::Motor>(l.get_port(), l.get_gearing(), l.is_reversed(), pros::E_MOTOR_ENCODER_DEGREES);
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

            float r_inches = ticks_to_inches(r_odom->get_position());
            float l_inches = ticks_to_inches(l_odom->get_position()); 
            float t_deg = deg_to_radian(_odom_imu->get_rotation());

            float r_enc_inches = ticks_to_inches(r_m->get_position());
            float l_enc_inches = ticks_to_inches(l_m->get_position());


            curr_theta = (using_the_imu) ? t_deg : 0; 
            curr_s_right = (using_rotation_sensor) ? r_inches : r_enc_inches; 
            curr_s_left = (using_rotation_sensor) ? l_inches : l_enc_inches; 

            pros::delay(25);

            float c_r_inches = ticks_to_inches(r_odom->get_position());
            float c_l_inches = ticks_to_inches(l_odom->get_position()); 
            float c_t_deg = deg_to_radian(_odom_imu->get_rotation());

            float c_r_enc_inches = ticks_to_inches(r_m->get_position());
            float c_l_enc_inches = ticks_to_inches(l_m->get_position());

            delta_s_right = (using_rotation_sensor) ? c_r_inches - curr_s_right : c_r_enc_inches - curr_s_right; 
            delta_s_left = (using_rotation_sensor) ? c_l_inches - curr_s_left : c_l_enc_inches - curr_s_left; 
            delta_theta = (using_the_imu) ? c_t_deg - curr_theta : theta + (((delta_s_right - delta_s_left) / (2 * track_length))/2); 

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

    float PositionTracking::ticks_to_inches(float ticks){
        return (deg_to_radian(ticks) * track_length/2);
    }

    float PositionTracking::deg_to_radian(float degs){
        return (ODOM_PI / 180) * degs;
    }
}