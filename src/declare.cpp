#include "declare.hpp"

const double gearRatio = 36.0 / 48.0;
const double trackWidth = 10.6;

const float DRIVESPEED = 120.0f;
const int TURNSPEED = 120.0f;

// PIDController pidH(0.023, 0.011, 0.144);
// PIDController pidD(0.21, 0, 0.03);

pros::Controller master(pros::E_CONTROLLER_MASTER);

//          PID
lemlib::ControllerSettings lateralController(5, // proportional gain (kP)
                                             0,   // integral gain (kI)
                                             1, // derivative gain (kD)
                                             0,   // anti windup
                                             1,   // small error range, in inches
                                             100, // small error range timeout, in milliseconds
                                             3,   // large error range, in inches
                                             500, // large error range timeout, in milliseconds
                                             127  // maximum acceleration (slew)
);

lemlib::ControllerSettings angularController(1.6, // proportional gain (kP) 
                                             0,    // integral gain (kI) 
                                             10,    // derivative gain (kD)
                                             2,    // anti windup
                                             1,    // small error range, in degrees
                                             100,  // small error range timeout, in milliseconds
                                             3,    // large error range, in degrees
                                             500,  // large error range timeout, in milliseconds
                                             127   // maximum acceleration (slew)
);

//          DRIVETRAIN

// pros::Motor m1(1, pros::MotorGearset::blue, pros::MotorUnits::degrees);
// pros::Motor m2(2, pros::MotorGearset::blue, pros::MotorUnits::degrees);
// pros::Motor m3(8, pros::MotorGearset::blue, pros::MotorUnits::degrees);

// pros::Motor m4(4, pros::MotorGearset::blue, pros::MotorUnits::degrees);
// pros::Motor m5(10, pros::MotorGearset::blue, pros::MotorUnits::degrees);
// pros::Motor m6(6, pros::MotorGearset::blue, pros::MotorUnits::degrees);

pros::MotorGroup LeftDrive({-1, -2, -3}, pros::MotorGearset::blue, pros::MotorUnits::degrees);
pros::MotorGroup RightDrive({8, 9, 10}, pros::MotorGearset::blue, pros::MotorUnits::degrees);

lemlib::Drivetrain driveTrain(&LeftDrive, &RightDrive, trackWidth, lemlib::Omniwheel::NEW_325, 450, 8);

pros::IMU imu(11);

//          ODOMETRY
// pros::Rotation horizontal_encoder(16);
pros::Rotation vertical_encoder(-4);

// lemlib::TrackingWheel horizontalTrackingWheel(&horizontal_encoder, lemlib::Omniwheel::NEW_2, 0.07874);
lemlib::TrackingWheel verticalTrackingWheel(&vertical_encoder, lemlib::Omniwheel::NEW_2, 0.5);

lemlib::OdomSensors sensors(&verticalTrackingWheel, // vertical tracking wheel
                            nullptr,
                            nullptr, // horizontal tracking wheel
                            nullptr,  
                            &imu,
                            360/358.15);

//          JOYSTICK CURVING

lemlib::ExpoDriveCurve throttle_curve(3,    // joystick deadband out of 127
                                      10,   // minimum output where drivetrain will move out of 127
                                      1.019 // expo curve gain
);

// input curve for steer input during driver control
lemlib::ExpoDriveCurve steer_curve(3,    // joystick deadband out of 127
                                   10,   // minimum output where drivetrain will move out of 127
                                   1.019 // expo curve gain
);

lemlib::Chassis chassis(driveTrain,
                        lateralController,
                        angularController,
                        sensors,
                        &throttle_curve,
                        &steer_curve);

//          Intake

pros::Motor firstStageIntakeMotor(-13, pros::MotorGearset::green, pros::MotorUnits::degrees);
pros::Motor secondStageIntakeMotor(12, pros::MotorGearset::green, pros::MotorUnits::degrees);
pros::Motor hopperMotor(-20, pros::MotorGearset::green, pros::MotorUnits::degrees);
pros::Motor scoringMotor(-7, pros::MotorGearset::green, pros::MotorUnits::degrees);
pros::Optical hopperOptical(14);
pros::Optical secondaryOptical(16);
hulib::Intake intake(firstStageIntakeMotor, secondStageIntakeMotor, hopperMotor, scoringMotor, hopperOptical, secondaryOptical);

//         Pneumatics
pros::adi::Pneumatics scraperPiston('a', false);