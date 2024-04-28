#include <BallFinding.h>
#include <Arduino.h>
#include <zirconLib.h>
#include <math.h>
#include <algorithm>
#include<tuple>
#include<iostream>


BallFinding::BallFinding () {

}

double BallFinding::orbit() {
    double sin_sensors_sum = 0;
    double cos_sensors_sum = 0;
    double distance;
    // double average;    
    for (int i = 0; i < num_sensors; i++) {
        sin_sensors_sum += readBall(i+1) * sin(((i+1)*45)*(PI/180));
        cos_sensors_sum += readBall(i+1) * cos(((i+1)*45)*(PI/180));
    }


    ballAngle = atan2(cos_sensors_sum, sin_sensors_sum) * (180/PI);
    // Serial.println("cos" + String(cos_sensors_sum));
    // Serial.println("sin" + String(sin_sensors_sum));


    if (ballAngle < 0) {
        ballAngle += 360;
    }

    ballAngle -= 40;

    if (ballAngle < 0) {
        ballAngle += 360;
    }

    ballAngle = (360-ballAngle);

    Serial.println(ballAngle);

    // vector ball distance
    distance = sqrt((cos_sensors_sum*exp(2)) + (sin_sensors_sum*exp(2)));

    multi = 1/distance;

    multiplier = min(1,0.02*exp(5.5 * multi));

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
        orbit_val = -multiplier * min(110,1.4*exp(0.2*ballAngle));
        orbit_val += 360;
    }
    else {
        orbit_val = multiplier * min(110,1.4*exp(0.2*ballAngle));
    }

    return orbit_val;

}