#include <Arduino.h>
#include <zirconLib.h>
#include <math.h>

class LineAvoidance {
    public:
        LineAvoidance();
        double finding_line();
        
    private:
        const int white_line = 700;

};
