#include <Arduino.h>
#include <zirconLib.h>
#include <math.h>

class BallFinding {
    public:
        BallFinding();
        double main_calc ();
        double orbit();
        double ballVector();
        double cos_sensors_sum;
        double sin_sensors_sum;
        double ballAngle;
        double multiplier;
        double distance;
        bool ball_in_robot;
    private:
        const int num_sensors = 8;
        double orbit_val;
};
