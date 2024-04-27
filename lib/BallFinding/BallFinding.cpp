#include <BallFinding.h>
#include <Arduino.h>
#include <zirconLib.h>
#include <math.h>
#include <algorithm>
#include<tuple>
#include<iostream>


BallFinding::BallFinding () {

}

double BallFinding::ballVector() {
    double sin_sensors[num_sensors];
    double cos_sensors[num_sensors];
    double sin_sensors_sum, cos_sensors_sum;
    double ballValVect[2];
    double distance;
    // double average;    
    for (int i = 0; i < num_sensors; i++) {
        sin_sensors[i] = readBall(i+1) * sin(((i+1)*45)*(PI/180));
        cos_sensors[i] = readBall(i+1) * cos(((i+1)*45)*(PI/180));

        // if (i == 6) {
        //     sin_sensors[i] == (readBall(8) * sin(((i+1)*45)*(PI/180)) + readBall(6) * sin(((i+1)*45)*(PI/180)))/2;
        //     cos_sensors[i] == (readBall(8) * cos(((i+1)*45)*(PI/180)) + readBall(6) * cos(((i+1)*45)*(PI/180)))/2;
        // }
    // sensors[i] = readBall(i+1);
    // max_sensors = max(sensors);
        sin_sensors_sum += sin_sensors[i];
        cos_sensors_sum += cos_sensors[i];
    }

    distance = sqrt((cos_sensors_sum*exp(2)) + (sin_sensors_sum*exp(2)));

    return sin_sensors_sum;
    return cos_sensors_sum;
}

double BallFinding::main_calc () {
    ballAngle = atan2(cos_sensors_sum, sin_sensors_sum) * (180/PI);

    if (ballAngle < 0) {
        ballAngle += 360;
    }

    ballAngle -= 40;

    if (ballAngle < 0) {
        ballAngle += 360;
    }

    ballAngle = (360-ballAngle);

    return ballAngle;
}

double BallFinding::orbit() {
    multiplier = 1/distance;

    // create a function that returns value from 0-1 based off of multiplier

    if (ballAngle>80 && ballAngle<280) {
        orbit_val = 180;
        if (ballAngle>170 && ballAngle<190) {
            orbit_val = 90;
        }
    }

    else if (355 < orbit_val && orbit_val < 5) {
        orbit_val = 0;
        ball_in_robot = true;
    }
    else if (ballAngle > 270) {
        ballAngle = 360-ballAngle;
        orbit_val = -min(110,1.4*exp(0.2*ballAngle));
        orbit_val += 360;
    }
    else {
        orbit_val = min(110,1.4*exp(0.2*ballAngle));
    }

    return orbit_val;
}