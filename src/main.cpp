#include "main.h"

void auto1() {

}

void auto2() {

}

void initialize() {
	hugui::initialize_auton_selector({
		hugui::Auton(redHigh, "Red High", hugui::AutonType::RED),
		hugui::Auton(blueHigh, "Blue High", hugui::AutonType::BLUE),
		hugui::Auton(drive_example, "Drive Example", hugui::AutonType::OTHER),
		hugui::Auton(turn_example, "Turn Example", hugui::AutonType::OTHER),
		hugui::Auton(driveOffLine, "Drive Off Line", hugui::AutonType::OTHER)
	});
	hugui::add_config_toggle(&intake.isHopperSort, "Hopper Sort");
	hugui::add_config_toggle(&intake.isSecondarySort, "Secondary Sort");
	intake.setOpticalColourRanges(340, 16, 100, 290);
	intake.setIntakeState(hulib::IntakeState::Direct);
	intake.setScoringState(hulib::ScoringState::Long);

	if (!pros::competition::is_connected()) 
        pros::Task update_info([&]() {  
            while (true) {
                hugui::update_pos(chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta, 3);
                pros::delay(25);
            }
        }); 

	pros::Task intake_task([&]() { 
		intake.intakeTask(); 
	});
	intake.chooseColourToSort(hulib::Colour::Blue);
	chassis.calibrate();
	chassis.setPose({0, 0, 0});
	master.rumble(".");
}

void disabled() {}

void competition_initialize() {}

void autonomous() { hugui::run_selected_auton(); }

std::string updateIntakeData() {
	std::string intakeData = "";
	switch(intake.getScoringState()) {
		case hulib::ScoringState::Long:
			intakeData = "Long";
			break;
		case hulib::ScoringState::Centre:
			intakeData = "Mid";
			break;
		case hulib::ScoringState::Hold:
			intakeData = "Hold";
			break;
	}

	switch(intake.getIntakeState()) {
		case hulib::IntakeState::Direct:
			intakeData += " Direct";
			break;
		case hulib::IntakeState::Feed:
			intakeData += " Feed";
			break;
		case hulib::IntakeState::Load:
			intakeData += " Load";
			break;
	}
	
	switch (intake.getColourToSort()) {
		case hulib::Colour::Red:
			intakeData += " (R)";
			break;
		case hulib::Colour::Blue:
			intakeData += " (B)";
			break;
	}
	return intakeData;
}

void opcontrol() {
	double startTime = pros::millis();
	double notifyTime = 70000;
	bool isNotified	= false;

	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
	intake.setIntakeState(hulib::IntakeState::Direct);
	std::string intakeData = "";
	while (true) {
		if (!pros::competition::is_connected()) {
            if (master.get_digital_new_press(DIGITAL_X))
                autonomous();
        }

        int Y = master.get_analog(ANALOG_LEFT_Y);
        int X = master.get_analog(ANALOG_RIGHT_X);
        chassis.arcade(Y, X);

		if (master.get_digital_new_press(DIGITAL_A)) {
			scraperPiston.toggle();
		}

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

		if(master.get_digital_new_press(DIGITAL_Y)) {
			if(intake.getIntakeState() == hulib::IntakeState::Direct) {
				intake.setIntakeState(hulib::IntakeState::Load);
				intake.prevIntakeState = hulib::IntakeState::Load;
			} else if(intake.getIntakeState() == hulib::IntakeState::Load) {
				intake.setIntakeState(hulib::IntakeState::Direct);
				intake.prevIntakeState = hulib::IntakeState::Direct;
			}
		}

		intakeData = updateIntakeData();
		master.print(0, 0, "%s", intakeData);
	
		if(!isNotified && pros::millis() - startTime >= notifyTime) {
			master.rumble("--------");
			isNotified = true;
		}
		lv_task_handler();
		pros::delay(10);
	}
}