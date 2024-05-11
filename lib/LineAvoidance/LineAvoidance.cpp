#include <LineAvoidance.h>
#include <Arduino.h>
#include <zirconLib.h>
#include <math.h>
#include <algorithm>
#include<tuple>
#include<iostream>


LineAvoidance::LineAvoidance() {
    // Initialize line sensors if needed
}

bool LineAvoidance::detectLine() {
    int sensor1Value = analogRead(LINE_SENSOR_1);
    int sensor2Value = analogRead(LINE_SENSOR_2);
    int sensor3Value = analogRead(LINE_SENSOR_3);

    // Check if any of the line sensors detect a line
    return (sensor1Value > LINE_SENSOR_THRESHOLD ||
            sensor2Value > LINE_SENSOR_THRESHOLD ||
            sensor3Value > LINE_SENSOR_THRESHOLD);
}

void LineAvoidance::avoidLine(double& moveAngle) {
    int sensor1Value = analogRead(LINE_SENSOR_1);
    int sensor2Value = analogRead(LINE_SENSOR_2);
    int sensor3Value = analogRead(LINE_SENSOR_3);

    // Determine the direction to avoid the line
    if (sensor1Value > LINE_SENSOR_THRESHOLD) {
        moveAngle += 90; // Turn right
    } else if (sensor3Value > LINE_SENSOR_THRESHOLD) {
        moveAngle -= 90; // Turn left
    }

    // Adjust the moveAngle to keep it within the valid range (0-360 degrees)
    moveAngle = fmod(moveAngle, 360);
    if (moveAngle < 0) {
        moveAngle += 360;
    }
}