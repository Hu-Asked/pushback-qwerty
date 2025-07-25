#include "intake.hpp"

bool isSortingHopper = false;
bool isSortingSecondary = false;
auto prevIntakeState = hulib::IntakeState::Direct;

namespace hulib
{
    Intake::Intake(pros::Motor& firstStageIntakeMotor, pros::Motor& secondStageIntakeMotor, pros::Motor& hopperMotor, pros::Motor& scoringMotor, pros::Optical& hopperOptical, pros::Optical& secondaryOptical)
        : firstStageIntakeMotor(firstStageIntakeMotor), 
        secondStageIntakeMotor(secondStageIntakeMotor),
        hopperMotor(hopperMotor), 
        scoringMotor(scoringMotor), 
        hopperOptical(hopperOptical),
        secondaryOptical(secondaryOptical) {}

    void Intake::setIntakeSpeed(double speed)
    {
        intakeSpeed = speed;

        switch (intakeState)
        {
        case IntakeState::Direct:
            firstStageIntakeMotor.move(intakeSpeed * 0.65);
            secondStageIntakeMotor.move(intakeSpeed);
            if(!isSortingHopper) hopperMotor.move(intakeSpeed);
            break;
        case IntakeState::Feed:
            firstStageIntakeMotor.move(intakeSpeed * 0.12);
            secondStageIntakeMotor.move(intakeSpeed);
            hopperMotor.move(intakeSpeed);
            break;
        case IntakeState::Load:
            firstStageIntakeMotor.move(intakeSpeed);
            secondStageIntakeMotor.move(intakeSpeed);
            hopperMotor.move(-abs(intakeSpeed));
            break;
        }

        switch (scoringState)
        {
        case ScoringState::Long:
            if(!isSortingSecondary)
                scoringMotor.move(intakeSpeed);
            break;
        case ScoringState::Centre:
            if(!isSortingSecondary) {
                scoringMotor.move(-intakeSpeed*0.4);
                secondStageIntakeMotor.move(intakeSpeed*0.4);
            }
            break;
        case ScoringState::Hold:
            auto colour = getColour(secondaryOptical);
            if (colour != hulib::Colour::None && colour != colourToSort) {
                scoringMotor.move(0);
                secondStageIntakeMotor.move(0);
                hopperMotor.move(intakeSpeed*0.3);
            } else {
                scoringMotor.move(intakeSpeed*0.3);
                secondStageIntakeMotor.move(intakeSpeed*0.3);
            }
            break;
        }

        prevIntakeSpeed = intakeSpeed;
    }

    void Intake::setOpticalColourRanges(double RED_MIN, double RED_MAX, double BLUE_MIN, double BLUE_MAX)
    {
        this->RED_MIN = RED_MIN;
        this->RED_MAX = RED_MAX;
        this->BLUE_MIN = BLUE_MIN;
        this->BLUE_MAX = BLUE_MAX;
    }

    void Intake::chooseColourToSort(hulib::Colour colour)
{
        colourToSort = colour;
    }

    Colour Intake::getColourToSort() { return colourToSort; }

    hulib::Colour Intake::getColour(pros::Optical &chosenOptical)
    {
        double hue = chosenOptical.get_hue();
        double proximity = chosenOptical.get_proximity();

        if (proximity > 55 && (hue >= RED_MIN || hue <= RED_MAX))
        {
            return hulib::Colour::Red;
        }
        else if (proximity > 55 && hue >= BLUE_MIN && hue <= BLUE_MAX)
        {
            return hulib::Colour::Blue;
        }
        return hulib::Colour::None;
    }

    void Intake::setScoringState(ScoringState state) { this->scoringState = state; }

    void Intake::setIntakeState(IntakeState state) { 
        this->intakeState = state; 
        prevIntakeState = state;
    }

    ScoringState Intake::getScoringState() { return scoringState; }

    IntakeState Intake::getIntakeState() { return intakeState; }

    void Intake::colourSortHopper()
    {
        if (intakeState == IntakeState::Load) {
            firstStageIntakeMotor.move(127);
            hopperMotor.move(127);
            pros::delay(500);
        } else {
            firstStageIntakeMotor.move(127);
            hopperMotor.move(-127);
        }
        pros::delay(25);
        setIntakeSpeed(intakeSpeed);
    }

    void Intake::colourSortSecondary()
    {
        switch(scoringState) {
            case ScoringState::Long:
                secondStageIntakeMotor.move(50);
                scoringMotor.move(-127);
                pros::delay(200);
                break;
            case ScoringState::Centre:
                master.rumble(".");
                scoringMotor.move(127);
                pros::delay(500);
                break;
        }
        setIntakeSpeed(intakeSpeed);
    }

    void Intake::intakeTask()
    {
        hopperOptical.set_integration_time(20);
        secondaryOptical.set_integration_time(20);
        hopperOptical.set_led_pwm(80);
        secondaryOptical.set_led_pwm(80);
        while (true) {
            if(!pros::competition::is_autonomous()) {
                if (master.get_digital(DIGITAL_R1)) {
                    intakeState = prevIntakeState;
                    intake.setIntakeSpeed(127);
                } else if (master.get_digital(DIGITAL_L1)) {
                    intakeState = prevIntakeState;
                    intake.setIntakeSpeed(-127);
                } else if (master.get_digital(DIGITAL_R2)) {
                    intakeState = hulib::IntakeState::Feed;
                    intake.setIntakeSpeed(127);
                } else if (master.get_digital(DIGITAL_L2)) {
                    intakeState = hulib::IntakeState::Feed;
                    intake.setIntakeSpeed(-127);
                } else {
                    intake.setIntakeSpeed(0);
                }
            }
            if (isHopperSort && colourToSort != hulib::Colour::None && getColour(hopperOptical) == colourToSort)
            {
                if (intakeState != hulib::IntakeState::Feed) {
                    colourSortHopper();
                    isSortingHopper = true;
                }
            } else if (isSortingHopper) {
                isSortingHopper = false;
                setIntakeSpeed(prevIntakeSpeed);
            }
            if (isSecondarySort && scoringState != hulib::ScoringState::Hold && colourToSort != hulib::Colour::None && getColour(secondaryOptical) == colourToSort)
            {
                colourSortSecondary();
                isSortingSecondary = true;
            } else if (isSortingSecondary) {
                isSortingSecondary = false;
                setIntakeSpeed(prevIntakeSpeed);
            }
            if(scoringState == hulib::ScoringState::Hold) {
                auto colour = getColour(secondaryOptical);
                if (colour != hulib::Colour::None && colour != colourToSort) {
                    scoringMotor.move(0);
                    secondStageIntakeMotor.move(0);
                    hopperMotor.move(intakeSpeed*0.3);
                } else {
                    scoringMotor.move(intakeSpeed*0.3);
                    secondStageIntakeMotor.move(intakeSpeed*0.3);
                }
            }
            hugui::console_print(std::to_string((int) getColour(hopperOptical)) + " " + std::to_string((int) getColour(secondaryOptical)) + " " + std::to_string((int) colourToSort) + " " +
                                std::to_string(hopperOptical.get_proximity()) + " " + std::to_string(secondaryOptical.get_proximity()), 0);

            pros::delay(15);
        }
    }
}