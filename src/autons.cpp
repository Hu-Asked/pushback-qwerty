#include "autons.hpp"

void redHigh() {
    chassis.setPose({0, 0, 0});
    intake.setScoringState(hulib::ScoringState::Hold);
    intake.setIntakeState(hulib::IntakeState::Load);
    intake.chooseColourToSort(hulib::Colour::Blue);
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