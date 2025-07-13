#include "main.h"

void auto1() {

}

void auto2() {

}

void initialize() {
	hugui::initialize_auton_selector({
	});
	intake.setOpticalColourRanges(330, 45, 80, 290);
	intake.setIntakeState(hulib::IntakeState::Direct);
	intake.setScoringState(hulib::ScoringState::Long);
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
            if (master.get_digital_new_press(DIGITAL_X))
                autonomous();
        }

        int Y = master.get_analog(ANALOG_LEFT_Y);
        int X = master.get_analog(ANALOG_RIGHT_X);
        chassis.curvature(Y, X);

		if (master.get_digital(DIGITAL_R1)) {
			intake.setIntakeSpeed(127);
		} else if (master.get_digital(DIGITAL_L1)) {
			intake.setIntakeSpeed(-127);
		} else {
			intake.setIntakeSpeed(0);
		}

		if(master.get_digital_new_press(DIGITAL_UP)) {
			intake.setScoringState(hulib::ScoringState::Long);
		} else if(master.get_digital_new_press(DIGITAL_DOWN)) {
			intake.setScoringState(hulib::ScoringState::Centre);
		}

		if(master.get_digital_new_press(DIGITAL_LEFT)) {
			intake.setIntakeState(hulib::IntakeState::Load);
		} else if(master.get_digital_new_press(DIGITAL_RIGHT)) {
			intake.setIntakeState(hulib::IntakeState::Direct);
		}
		master.print(0, 0, "%d %d", intake.getIntakeState(), intake.getScoringState());
	
		if(!isNotified && pros::millis() - startTime >= notifyTime) {
			master.rumble("--------");
			isNotified = true;
		}
		lv_task_handler();
		pros::delay(10);
	}
}