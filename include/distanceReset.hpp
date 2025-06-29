#pragma once

#include "lemlib/chassis/odom.hpp"
#include "pros/distance.hpp"
#include <vector>
#include <unordered_map>

namespace lemlib {
    class Chassis;
}

namespace hulib {

enum Quadrant {
    Q1,
    Q2,
    Q3,
    Q4
};
enum Direction {
    Left,
    Right,
    Front,
    Rear
};

class ResetSensor {
    public:
    /*
    measured in mm and degrees
    xOffset is the left/right offset from the tracking center of the robot
    left is negative, right is positive
    yOffset is the forward/backward offset from the tracking center of the robot
    backwards is negative, forwards is positive
    Pos/neg is based on their distance from the center and where they are pointing
    */
        ResetSensor( pros::Distance* dist, double xOffset, double yOffset, Direction dir);
        double getResetDist(double curHeading);
        double getRawDist();
        double getConfidence();
        pros::Distance* dist;
        double xOffset;
        double yOffset;
        Direction dir;
};

class DistanceResetSensors {
    public:
    
    DistanceResetSensors(   ResetSensor* leftReset1, ResetSensor* leftReset2,
                            ResetSensor* rightReset1, ResetSensor* rightReset2,
                            ResetSensor* frontReset1, ResetSensor* frontReset2,
                            ResetSensor* rearReset1, ResetSensor* rearReset2,
                            double usefulConfidence);

    void initialize();

    /**
     * @brief Reset position of the bot using distance sensors. Make sure only one side of the bot faces the wall in close proximity
     * 
     * @param quadrant the quadrant the robot is in (Q1 is B. Right, Q2 is R. Left, Q3 is R. Right, Q4 is B. Left)
     * @param resetX sensors facing the direction that will be used when resetting x position
     * @param resetY sensors facing the direction that will be used when resetting y position
     * @param resetHeading WIP
     * 
     */
    void reset_pos(hulib::Quadrant quadrant, hulib::Direction resetX, hulib::Direction resetY, bool resetHeading = false, lemlib::Chassis* robot = nullptr);
                            
    ResetSensor* leftReset1;
    ResetSensor* leftReset2;
    ResetSensor* rightReset1; 
    ResetSensor* rightReset2;
    ResetSensor* frontReset1; 
    ResetSensor* frontReset2;
    ResetSensor* rearReset1; 
    ResetSensor* rearReset2;
    std::unordered_map<hulib::Direction, std::vector<ResetSensor*>> sensors;
    double usefulConfidence;
};

}