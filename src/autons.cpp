#include "autons.hpp"

void moveVolts(int volts) {
    LeftDrive.move(volts);
    RightDrive.move(volts);
}
void jiggle(int time) {
    int start = pros::millis();
    while(pros::millis() - start < time) {
        moveVolts(60);
        pros::delay(60);
        moveVolts(0);
        pros::delay(60);
    }
} 


void redHigh() {
    chassis.setPose({0, 0, 0});
    intake.setScoringState(hulib::ScoringState::Hold);
    intake.setIntakeState(hulib::IntakeState::Load);
    intake.chooseColourToSort(hulib::Colour::Blue);
    intake.setIntakeSpeed(127);
    chassis.moveToPoint(0.2, 56, 2000, {.minSpeed = 30, .earlyExitRange = 28});
    chassis.moveToPoint(-0.3, 56, 1100, {.maxSpeed = 40});
    chassis.waitUntilDone();
    chassis.moveToPoint(7, 48, 1000, {.forwards = false, .minSpeed = 15, .earlyExitRange = 1});
    chassis.turnToPoint(15, 28, 1500, {.maxSpeed = 80, .minSpeed = 10, .earlyExitRange = 1});
    chassis.moveToPoint(15, 28, 3500, {.maxSpeed = 30, .minSpeed = 5, .earlyExitRange = 1});
    chassis.turnToPoint(-24, 20, 1500, {.minSpeed = 20, .earlyExitRange = 2});
    chassis.waitUntilDone();
    scraperPiston.toggle(); 
    chassis.moveToPose(-23, 19, 210, 2000, {.lead = 0.45, .minSpeed = 10, .earlyExitRange = 2});
    chassis.waitUntilDone();
    chassis.moveToPoint(-27.5, 12, 1200, {.minSpeed = 10, .earlyExitRange = 0.5});
    intake.setIntakeState(hulib::IntakeState::Direct);
    intake.setIntakeSpeed(127);
    chassis.waitUntilDone();
    jiggle(750);
    chassis.moveToPose(-13.9, 36.9, 210, 1500, {.forwards = false});
    chassis.waitUntilDone();
    moveVolts(-40);
    intake.setScoringState(hulib::ScoringState::Long);
    pros::delay(500);
    intake.setIntakeState(hulib::IntakeState::Feed);
    intake.setIntakeSpeed(127);
}

void redSAWP() {
    chassis.setPose({0, 0, 0});
    intake.setScoringState(hulib::ScoringState::Hold);
    intake.setIntakeState(hulib::IntakeState::Direct);
    intake.chooseColourToSort(hulib::Colour::Blue);
    intake.setIntakeSpeed(127);
    chassis.moveToPose(0, 42, 270, 2000, {.minSpeed = 20, .earlyExitRange = 1});
    scraperPiston.toggle();
    chassis.moveToPoint(-11, 43.8, 1500, {.minSpeed = 10, .earlyExitRange = 0.5});
    chassis.waitUntilDone();
    moveVolts(90  );
    pros::delay(250);
    jiggle(800);
    chassis.moveToPose(24, 44.15, 270, 2000, {.forwards = false, .minSpeed = 10});
    chassis.waitUntilDone();
    intake.setScoringState(hulib::ScoringState::Long);
    intake.setIntakeSpeed(127);
    pros::delay(1500);
    intake.setScoringState(hulib::ScoringState::Hold);
    intake.setIntakeSpeed(127);
    chassis.moveToPose(-2, 15, 180, 2000, {.minSpeed = 10, .earlyExitRange = 0.5});
    scraperPiston.toggle();
    chassis.turnToPoint(25, 16.4, 1500, {.minSpeed = 10, .earlyExitRange = 1});
    chassis.moveToPoint(25, 16.4, 5000, {.maxSpeed = 30, .minSpeed = 10, .earlyExitRange = 1});
    chassis.turnToPoint(35, 7, 1500, {.forwards = false, .minSpeed = 10, .earlyExitRange = 1});
    chassis.moveToPose(36, 6, -405, 1000, {.forwards = false, .minSpeed = 10, .earlyExitRange = 1});
    chassis.moveToPoint(36, 6, 1000, {.forwards = false, .minSpeed = 10, .earlyExitRange = 1});
    chassis.waitUntilDone();
    intake.setScoringState(hulib::ScoringState::Centre);
    intake.setIntakeSpeed(127);
}

void blueHigh() {
    chassis.setPose({0, 0, 0});
    intake.setScoringState(hulib::ScoringState::Hold);
    intake.setIntakeState(hulib::IntakeState::Load);
    intake.chooseColourToSort(hulib::Colour::Red);
    intake.setIntakeSpeed(127);
    chassis.moveToPoint(-0.5, 57, 2000, {.minSpeed = 30, .earlyExitRange = 28});
    chassis.moveToPoint(-0.5, 57, 1000, {.maxSpeed = 40});
    chassis.waitUntilDone();
    pros::delay(200);
    chassis.moveToPoint(0, 46, 1000, {.forwards = false, .minSpeed = 10, .earlyExitRange = 1});
    chassis.turnToPoint(12, 33.7, 1500);
    chassis.moveToPoint(12, 33.7, 3500, {.maxSpeed = 35, .minSpeed = 20, .earlyExitRange = 1});

    chassis.turnToPoint(-27, 28, 1500, {.minSpeed = 20, .earlyExitRange = 1});
    chassis.moveToPoint(-27, 28, 2000);
    scraperPiston.toggle();
    intake.setIntakeState(hulib::IntakeState::Direct);
    chassis.turnToPoint(-33.5, 16, 1500, {.minSpeed = 20, .earlyExitRange = 1});
    chassis.moveToPoint(-33.5, 16, 2000, {.maxSpeed = 75, .minSpeed = 10, .earlyExitRange = 1});
    chassis.waitUntilDone();
    LeftDrive.move(40);
    RightDrive.move(40);
    pros::delay(200);
    LeftDrive.move(0);
    RightDrive.move(0);
    pros::delay(1500);
    intake.setIntakeSpeed(0);
    chassis.moveToPoint(-18.5, 40, 2000, {.forwards = false});
    chassis.waitUntilDone();
    intake.setIntakeState(hulib::IntakeState::Feed);
    intake.setScoringState(hulib::ScoringState::Long);
    intake.setIntakeSpeed(127);
    LeftDrive.move(-70);
    RightDrive.move(-70);
    pros::delay(2000);
    LeftDrive.move(0);
    RightDrive.move(0);
}

double target = 0;
void drive_example() {
    chassis.setPose({0, 0, 0});
    pros::Task print_task([]() {
        double start = pros::millis();
        while(true) {
            std::cout << std::to_string(chassis.getPose().y) << " " << std::to_string(target) << " " << std::to_string(pros::millis() - start) << "\n";
            pros::delay(10);
        }
    });
    target = 36;
    chassis.moveToPoint(0, 36, 5000, {.maxSpeed = DRIVESPEED});
    chassis.waitUntilDone();
    target = 0;
    chassis.moveToPoint(0, 0, 5000, {.forwards = false, .maxSpeed = DRIVESPEED});
    chassis.waitUntilDone();
    target = 24;
    pros::delay(400);
    chassis.setPose({0, 0, 0});
    chassis.moveToPoint(0, 24, 5000, {.maxSpeed = DRIVESPEED});
    chassis.waitUntilDone();
    target = 0;
    chassis.moveToPoint(0, 0, 5000, {.forwards = false, .maxSpeed = DRIVESPEED});
    chassis.waitUntilDone();
}
void turn_example() {
    chassis.setPose({0, 0, 0});
    pros::Task print_task([]() {
        double start = pros::millis();
        while(true) {
            std::cout << std::to_string(chassis.getPose().theta) << " " << std::to_string(target) << " " << std::to_string(pros::millis() - start) << "\n";
            pros::delay(10);
        }
    });
    target = 45;
    chassis.turnToHeading(45, 2000, {.maxSpeed = TURNSPEED});
    chassis.waitUntilDone();
    target = 135;
    chassis.turnToHeading(135, 2000, {.maxSpeed = TURNSPEED});
    chassis.waitUntilDone();
    target = 315;
    chassis.turnToHeading(315, 2000, {.maxSpeed = TURNSPEED});
}

void driveOffLine() {
    chassis.setPose({0, 0, 0});
    chassis.moveToPoint(0, 10, 1200, {.maxSpeed = 60});
}