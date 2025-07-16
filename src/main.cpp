#include "main.h"

void auto1() {

}

void auto2() {

}

void initialize() {
	hugui::initialize_auton_selector({
	});
	intake.setOpticalColourRanges(340, 30, 100, 290);
	intake.setIntakeState(hulib::IntakeState::Direct);
	intake.setScoringState(hulib::ScoringState::Long);

	// if (!pros::competition::is_connected()) 
    //     pros::Task update_info([&]() {  
    //         while (true) {
    //             // hugui::update_pos(chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta, 3);
    //             pros::delay(25);
    //         }
    //     }); 

	pros::Task intake_task([&]() { 
		intake.intakeTask(); 
	});
	intake.chooseColourToSort(hulib::Colour::Blue);
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
        chassis.arcade(Y, X);

		if(master.get_digital_new_press(DIGITAL_UP)) {
			intake.setScoringState(hulib::ScoringState::Long);
		} else if(master.get_digital_new_press(DIGITAL_DOWN)) {
			intake.setScoringState(hulib::ScoringState::Centre);
		} else if(master.get_digital_new_press(DIGITAL_B)) {
			intake.setScoringState(hulib::ScoringState::Hold);
		}

		if(master.get_digital_new_press(DIGITAL_LEFT)) {
			intake.chooseColourToSort(hulib::Colour::Blue);
		} else if(master.get_digital_new_press(DIGITAL_RIGHT)) {
			intake.chooseColourToSort(hulib::Colour::Red);
		}
		master.print(0, 0, "%d %d", intake.getColourToSort(), intake.getScoringState());
	
		if(!isNotified && pros::millis() - startTime >= notifyTime) {
			master.rumble("--------");
			isNotified = true;
		}
		lv_task_handler();
		pros::delay(10);
	}
}