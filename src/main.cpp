#include "main.h"

void auto1() {

}

void auto2() {

}

void initialize() {
	hugui::initialize_auton_selector({
	});
	chassis.calibrate();
	master.rumble(".");
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {
	double startTime = pros::millis();
	double notifyTime = 70000;
	bool isNotified	= false;

	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);

	while (true) {
		if (!pros::competition::is_connected()) {
            if (master.get_digital_new_press(DIGITAL_RIGHT))
                autonomous();
        }

        int Y = master.get_analog(ANALOG_LEFT_Y);
        int X = master.get_analog(ANALOG_RIGHT_X);
        chassis.arcade(Y, X);
	
		if(!isNotified && pros::millis() - startTime >= notifyTime) {
			master.rumble("--------");
			isNotified = true;
		}
		lv_task_handler();
		pros::delay(10);
	}
}