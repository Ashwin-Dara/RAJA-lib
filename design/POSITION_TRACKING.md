# Usage of the Position Tracking Class

## Steps to using the Position Tracking Class WITH AN IMU
1. Create an instance of the class
2. Configure the sensors you wish to use by using the functions "set_imu" "set_encoders" "set_motors"
3. Set the Drive Configurations. If you are using an IMU it actually doesn't matter what the first argument of 'set_drive_configurations' is.
4. Have a function that contains the PositionTracking::begin_tracking() method. The reason for this is that you will be putting the outer function into a task. 

<br>

Here is a full example of the usage:

```
pros::IMU main_imu(20); 
pros::Rotation right_encoder(1); 
pros::Rotation left_encoder(2); 


PositionTracking drive1; 
drive1.set_encoders(right_encoder, left_encoder); 
drive1.set_imu(main_imu); 
drive1.set_drive_configurations(15, 4);


void tracking_wrapper(void*){
    drive1.begin_tracking(); 
}

void autonomous(){
    pros::Task position_tracking_task(tracking_wrapper); 
    pros::delay(1000); 

    cout << "The Position of the Robot is: " << drive1.get_x() << "  " << drive1.get_y() << "  " << drive1.get_theta() <<  std::endl; 
}

```
<br>

## Using the Position Tracking Class without an IMU
1. The procedure is the exact same as the previous all we need to do is have an additional configuration for the track length of the drive
2. The track length is the distance from the right set of wheels and the left set of wheels (in inches). Moreover, we need to set the wheel size. 

Here is the full example of the usage for if you are not using an IMU:  
<br>
```
pros::Motor right_motor(1);
pros::Motor left_motor(2);

PositionTracking drive1; 
drive1.set_drive_configurations(15, 4);
drive1.set_motors(right_motor, left_motor);

void tracking_wrapper(void*){
    drive1.begin_tracking(); 
}

void autonomous(){
    pros::Task position_tracking_task(tracking_wrapper);
    pros::delay(1000);

    cout << "The Position of the Robot is: " << drive1.get_x() << "  " << drive1.get_y() << "  " << drive1.get_theta() <<  std::endl; 
}

```

