# Design 
## Features 
The library will contain the following: 
- Methods for Autonomous 
- Methods for Driver Control 

### Autonomous
- Closed Loop Controller (slew limited closed-loop controller)
- Chassis "Model" 
    - Creating a "Chassis" class with methods for moving (view file Chassis-Object.cpp)
```
Motor rightMotor1(1); 
Motor rightMotor2(2); 
Motor leftMotor1(3); 
Motor leftMotor2(4); 

// FIRST PUT THE RIGHT MOTORS AND THEN THE LEFT MOTORS. Creates a chassis group.
ChassisObject drive1(rightMotor1, rightMotor2, leftMotor1, leftMotor2); 

drive1.move(100);  // valid 

```
- Odometry class. The ChassisObject Class will INHERIT the odometry/position tracking class. 
    - Description: will contain the following methods. one for updating the position (contains all of the equations). getter methods for x position, y position, and theta. Debug method that prints the position as a datastream into the terminal. 

- Motion Profile Class. This is how the usage should look like. 
```
void motion_profile_move(ChassisObject &drive, int set_point, int req_time_taken){
    // ... IMPLEMENTATION LEFT BLANK
}

// TO USE.  

void autonomous(){
Motor rightMotor1(1); 
Motor rightMotor2(2); 
Motor leftMotor1(3); 
Motor leftMotor2(4); 

// FIRST PUT THE RIGHT MOTORS AND THEN THE LEFT MOTORS. Essentially creates a chassis group
ChassisObject drive1(rightMotor1, rightMotor2, leftMotor1, leftMotor2); 

motion_profile_move(drive, 1000, 1500); // valid
}
```

### Driver Control 
    - Rising Edge Controller 
    - Tank Drive. This should be the function signature `void tank_control(const &pros::Controller joystick, ChassisObject &drive)`. 
    - Arcade Drive. Signature should be same as tank drive but the name should be `arcade_control`

