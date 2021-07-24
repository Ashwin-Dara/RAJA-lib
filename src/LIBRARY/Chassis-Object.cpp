#include "main.h"
#include "../../include/RAJA/object/Chassis-Object.h"

std::shared_ptr<pros::Motor> rDrive1, rDrive2, lDrive1, lDrive2; 

ChassisObject::ChassisObject(const pros::Motor &m1, const pros::Motor &m2, 
                             const pros::Motor &m3, const pros::Motor &m4) {

// Creating motor parameters: port, gearset, reverse, encoder_units

rDrive1 = std::make_shared<pros::Motor>(m1.get_port(), m1.get_gearing(), m1.is_reversed(), m1.get_encoder_units());
rDrive2 = std::make_shared<pros::Motor>(m2.get_port(), m2.get_gearing(), m2.is_reversed(), m2.get_encoder_units());

lDrive1 = std::make_shared<pros::Motor>(m3.get_port(), m3.get_gearing(), m3.is_reversed(), m3.get_encoder_units());
lDrive2 = std::make_shared<pros::Motor>(m4.get_port(), m4.get_gearing(), m4.is_reversed(), m4.get_encoder_units());

}


void ChassisObject::move_right_side (int voltage){
    rDrive1->move(voltage); 
    rDrive2->move(voltage);
}

 void ChassisObject::move_left_side (int voltage){
    lDrive1->move(voltage); 
    lDrive2->move(voltage);
}

// NEED TO PASS IN THE CHASSIS OBJECT THROUGH REFERENCE 

/* SAMPLE USAGE 

ChassisObject drive1(rightMotor, rightMotor2, leftMotor, leftMotor2); 
ClosedLoop pid1(0.18, 0.01, 0.05, 2, 'C');

move_to_point(drive1, pid1, imu.get_position(), 90);


*/