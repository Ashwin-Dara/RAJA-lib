#include "main.h"
#include "../../include/RAJA/object/Chassis-Object.h"

namespace RAJA{

    /*
    * Electronics that will be used internally by the ChassisObject class. 
    */
    std::shared_ptr<pros::Motor> rDrive1, rDrive2, lDrive1, lDrive2; 

    ChassisObject::ChassisObject(const pros::Motor &m1, const pros::Motor &m2, 
                                 const pros::Motor &m3, const pros::Motor &m4) {

    // Constructing the motors that will be use internally by the Chassis Object Class.

    rDrive1 = std::make_shared<pros::Motor>(m1.get_port(), m1.get_gearing(), 
                                            m1.is_reversed(), m1.get_encoder_units());

    rDrive2 = std::make_shared<pros::Motor>(m2.get_port(), m2.get_gearing(), 
                                            m2.is_reversed(), m2.get_encoder_units());

    lDrive1 = std::make_shared<pros::Motor>(m3.get_port(), m3.get_gearing(), 
                                            m3.is_reversed(), m3.get_encoder_units());

    lDrive2 = std::make_shared<pros::Motor>(m4.get_port(), m4.get_gearing(), 
                                            m4.is_reversed(), m4.get_encoder_units());
    }


    void ChassisObject::move_right_side (int voltage){
        // Moving the right motors at the specified voltage.
        rDrive1->move(voltage); 
        rDrive2->move(voltage);
    }


    void ChassisObject::move_left_side (int voltage){
        // Moving the left motors at the specified voltage.
        lDrive1->move(voltage); 
        lDrive2->move(voltage);
    }


    void ChassisObject::move(int voltage){
        // Moving the drive at the inputted voltage. 
        move_right_side(voltage); 
        move_left_side(voltage);
    }


    void absolute_move_to(ChassisObject &drive, ClosedLoop &controller, float sensor_value, int set_point, int timeout){
        // Passing in the chassis so that we can move it. Passing in the ClosedLoop so we know what controller to apply. 
        int manual_timeout = 0; // Time override in the case that the drive does not "settle"

        while(!controller.has_settled() || (manual_timeout < timeout && manual_timeout > 0)){

            drive.move_left_side(controller.get_calculated_power(set_point, timeout));
            drive.move_right_side(controller.get_calculated_power(set_point, timeout));

            pros::delay(25);
            manual_timeout += 25; 
        }
    }


    void relative_move_to(ChassisObject &drive, ClosedLoop &controller, float sensor_value, int set_point, int timeout){
            // Using the absolute_move_to function but with modified sensor logic
        absolute_move_to(drive, controller, sensor_value, set_point - sensor_value, timeout);
    }

        /* SAMPLE USAGE 

        ChassisObject drive1(rightMotor, rightMotor2, leftMotor, leftMotor2); 
        ClosedLoop pid1(0.18, 0.01, 0.05, 2, 'T');

        move_to_point(drive1, pid1, imu.get_position(), 90);

        */
}
