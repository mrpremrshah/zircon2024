#ifndef LINE_AVOIDANCE_H
#define LINE_AVOIDANCE_H
#include <Arduino.h>
#include <zirconLib.h>
#include <math.h>

class LineAvoidance {
public:
    LineAvoidance();
    bool detectLine();
    void avoidLine(double& moveAngle);

private:
    const int LINE_SENSOR_THRESHOLD = 50; // Adjust this value based on your sensor readings
    const int LINE_SENSOR_1 = A0; // change pin numbers for our line sensors(Idk what they are)
    const int LINE_SENSOR_2 = A1;
    const int LINE_SENSOR_3 = A2;
};