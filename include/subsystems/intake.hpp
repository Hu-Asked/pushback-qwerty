#pragma once

#include "main.h";

namespace hulib
{
    enum class Colour
    {
        Red,
        Blue,
        None
    };
    enum class ScoringState
    {
        Long,
        Centre,
        Load
    };

    class Intake
    {
    public:
        /**
         * @brief constructs an Intake object used for controlling the intake system
         *
         * @param primaryIntakeMotor the main motor used for the control of the intake throughout the robot
         * @param hopperMotor the motor responsible for moving the blocks from the intake to the hopper
         * @param scoringMotor the motor responsible for scoring the blocks in the high or low goals
         * @param hopperOptical the optical sensor used to detect the colour of the blocks before the hopper
         *
         */
        Intake(pros::Motor& primaryIntakeMotor, pros::Motor& hopperMotor, pros::Motor& scoringMotor, pros::Optical& hopperOptical);

        /**
         * @brief sets the speed of the overall intake system
         *
         * @param speed the speed to set the intake system to, from -127 to 127
         *
         */
        void setIntakeSpeed(double speed);

        /**
         * @brief sets the colour ranges for the optical sensor
         *
         * @param RED_MIN the minimum hue value for red blocks
         * @param RED_MAX the maximum hue value for red blocks
         * @param BLUE_MIN the minimum hue value for blue blocks
         * @param BLUE_MAX the maximum hue value for blue blocks
         */
        void setOpticalColourRanges(double RED_MIN, double RED_MAX, double BLUE_MIN, double BLUE_MAX);

        /**
         * @brief sets the colour for the colour sorter to sort
         *
         * @param color the colour to set the sorter to, none if the colour sensor is to be disabled
         */
        void chooseColourToSort(hulib::Colour colour);

        /**
         * @brief returns the colour detected by the optical sensor
         *
         * @param chosenOptical the optical sensor to get the colour from
         */
        hulib::Colour getColour(pros::Optical &chosenOptical);

        /**
         * @brief sets the scoring state of the intake system
         *
         * @param state the state to set the scoring system to, long, centre or load (straight into the hopper)
         */
        void setScoringState(ScoringState state);

        /**
         * @brief sets the hopper feed state
         *
         * @param feedFromHopper true if the hopper will feed into the intake system, false if it will not
         */
        void setFeedFromHopper(bool feedFromHopper);

        /**
         * @brief runs the intake task
         */
        void intakeTask();

    private:
        void colourSortHopper();

        pros::Motor primaryIntakeMotor;
        pros::Motor hopperMotor;
        pros::Motor scoringMotor;
        pros::Optical hopperOptical;
        double intakeSpeed = 0;
        double prevIntakeSpeed = 0;

        bool feedFromHopper = false;
        ScoringState scoringState;

        int RED_MIN = 0;
        int RED_MAX = 0;
        int BLUE_MIN = 0;
        int BLUE_MAX = 0;

        hulib::Colour colourToSort;
    };
}
