#include "distanceReset.hpp"
#include <math.h>


hulib::ResetSensor::ResetSensor(pros::Distance* dist, double x, double y, hulib::Direction dir) 
    : dist(dist),
      xOffset(x),
      yOffset(y),
      dir(dir) {}
    
double hulib::ResetSensor::getResetDist(double heading) {
    heading = fmod(heading, 360);
    double rad = heading * (M_PI / 180);
    int a = tan(rad) * xOffset;
    double trueDist = dist->get_distance() + a + yOffset; // hypotenuse
    double resetDist = cos(rad) * trueDist;
    return resetDist / 25.4;
}

double hulib::ResetSensor::getRawDist() {
    return dist->get_distance() / 25.4;
}

double hulib::ResetSensor::getConfidence() {
    return dist->get_confidence();
}

hulib::DistanceResetSensors::DistanceResetSensors(
                            ResetSensor* leftReset1, ResetSensor* leftReset2,
                            ResetSensor* rightReset1, ResetSensor* rightReset2,
                            ResetSensor* frontReset1, ResetSensor* frontReset2,
                            ResetSensor* rearReset1, ResetSensor* rearReset2,
                            double usefulConfidence)
    : leftReset1(leftReset1),
      leftReset2(leftReset2),
      rightReset1(rightReset1),
      rightReset2(rightReset2),
      frontReset1(frontReset1),
      frontReset2(frontReset2),
      rearReset1(rearReset1),
      rearReset2(rearReset2),
      usefulConfidence(usefulConfidence) {}

void hulib::DistanceResetSensors::initialize() {
    if(leftReset1 != nullptr) sensors[Direction::Left].push_back(leftReset1);
    if(leftReset2 != nullptr) sensors[Direction::Left].push_back(leftReset2);
    if(rightReset1 != nullptr) sensors[Direction::Right].push_back(rightReset1);
    if(rightReset2 != nullptr) sensors[Direction::Right].push_back(rightReset2);
    if(frontReset1 != nullptr) sensors[Direction::Front].push_back(frontReset1);
    if(frontReset2 != nullptr) sensors[Direction::Front].push_back(frontReset2);
    if(rearReset1 != nullptr) sensors[Direction::Rear].push_back(rearReset1);
    if(rearReset2 != nullptr) sensors[Direction::Rear].push_back(rearReset2);
}

//TODO implement imu reset through distanceSensors requires multiple on one side, possibly obselete
void hulib::DistanceResetSensors::reset_pos(hulib::Quadrant quadrant, hulib::Direction resetX, hulib::Direction resetY, bool resetHeading, lemlib::Chassis* robot) {
    double poseX, poseY;
    if (robot == nullptr) return;

    switch (quadrant) {
        case hulib::Quadrant::Q1:
            poseX = 70;
            poseY = 70;
            break;
        case hulib::Quadrant::Q2:
            poseX = -70;
            poseY = 70;
            break;
        case hulib::Quadrant::Q3:
            poseX = -70;
            poseY = -70;
            break;
        case hulib::Quadrant::Q4:
            poseX = 70;
            poseY = -70;
            break;
    }

    poseX -= sensors[resetX][0]->getResetDist(robot->getPose().theta);
    poseY -= sensors[resetY][0]->getResetDist(robot->getPose().theta);
    robot->setPose(poseX, poseY, robot->getPose().theta);
}