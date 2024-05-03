#include <BallFinding.h>
#include <Arduino.h>
#include <zirconLib.h>
#include <math.h>
#include <algorithm>
#include<tuple>
#include<iostream>
// #include <cmath>


BallFinding::BallFinding () {

}

double BallFinding::orbit() {
    double sin_sensors_sum = 0;
    double cos_sensors_sum = 0;
    double distance = 0;
    double move_angle = 0;

    // Serial.println("ball 1:   " + String(readBall(1)));
    // Serial.println("ball 2:   " + String(readBall(2)));
    // Serial.println("ball 3:   " + String(readBall(3)));
    // Serial.println("ball 4:   " + String(readBall(4)));
    // Serial.println("ball 5:   " + String(readBall(5)));
    // Serial.println("ball 6:   " + String(readBall(6)));
    // Serial.println("ball 7:   " + String(readBall(7)));
    // Serial.println("ball 8:   " + String(readBall(8)));
    // double average;    
    for (int i = 0; i < num_sensors; i++) {
        sin_sensors_sum += readBall(i+1) * sin(((i+1)*45)*(PI/180));
        cos_sensors_sum += readBall(i+1) * cos(((i+1)*45)*(PI/180));
    }


    ballAngle = atan2(cos_sensors_sum, sin_sensors_sum) * (180/PI);
    // Serial.println(0);
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

    // Serial.println(ballAngle);

    // return pow(cos_sensors_sum,2);
    // return pow(sin_sensors_sum, 2);
    // vector ball distance

    distance = sqrt((pow(cos_sensors_sum, 2)) + pow(sin_sensors_sum, 2));
    // distance = 850;
    multiplier = min(1.0, pow(0.9, (1.0/60.0) * (distance - 800)));

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
        orbit_val = min(110,1.4*exp(0.2*ballAngle));
        orbit_val += 360;
    }
    else {
        orbit_val = min(110,1.4*exp(0.2*ballAngle));
    }

// DAMPEN FUNCTION
    // ballAngle = 45;
    if (ballAngle > 0 && ballAngle < 90) {
        move_angle = ballAngle + (orbit_val * multiplier);
    } 

    else if (ballAngle < 0 && ballAngle > -90) {
        orbit_val = ballAngle - (orbit_val * multiplier);
    }



    return orbit_val + (ballAngle * multiplier);

}