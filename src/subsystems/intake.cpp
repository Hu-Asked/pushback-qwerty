#include "intake.hpp"

int hopperColourSortTime = 150;

namespace hulib
{

    Intake::Intake(pros::Motor& primaryIntakeMotor, pros::Motor& hopperMotor, pros::Motor& scoringMotor, pros::Optical& hopperOptical)
        : primaryIntakeMotor(primaryIntakeMotor), hopperMotor(hopperMotor), scoringMotor(scoringMotor), hopperOptical(hopperOptical) {}

    void Intake::setIntakeSpeed(double speed)
    {
        intakeSpeed = speed;
        switch (scoringState)
        {
        case ScoringState::Long:
            primaryIntakeMotor.move(intakeSpeed);
            hopperMotor.move(intakeSpeed);
            scoringMotor.move(intakeSpeed);
            break;
        case ScoringState::Centre:
            primaryIntakeMotor.move(intakeSpeed);
            hopperMotor.move(intakeSpeed);
            scoringMotor.move(-intakeSpeed);
            break;
        case ScoringState::Load:
            primaryIntakeMotor.move(intakeSpeed);
            hopperMotor.move(-intakeSpeed);
            scoringMotor.move(0);
            break;
        }
        prevIntakeSpeed = intakeSpeed;
    }

    void Intake::setOpticalColourRanges(double BLUE_MIN, double BLUE_MAX, double RED_MIN, double RED_MAX)
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

    hulib::Colour Intake::getColour(pros::Optical& chosenOptical)
    {
        double hue = chosenOptical.get_hue();

        if (hue >= RED_MIN && hue <= RED_MAX)
        {
            return hulib::Colour::Red;
        }
        else if (hue >= BLUE_MIN && hue <= BLUE_MAX)
        {
            return hulib::Colour::Blue;
        }
        return hulib::Colour::None;
    }

    void Intake::setScoringState(ScoringState state) { this->scoringState = state; }

    void Intake::setFeedFromHopper(bool feedFromHopper) { this->feedFromHopper = feedFromHopper; }

    void Intake::colourSortHopper()
    {
        hopperMotor.move(-127);
        pros::delay(hopperColourSortTime);
        setIntakeSpeed(intakeSpeed);
    }

    void Intake::intakeTask()
    {

        if (colourToSort != hulib::Colour::None && getColour(hopperOptical) == colourToSort)
        {
            colourSortHopper();
        }

        pros::delay(20);
    }

}