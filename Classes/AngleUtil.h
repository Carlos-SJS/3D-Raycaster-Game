#pragma once
#include <cmath>

#define PI 3.14159265    //Aprox. value of PI     (180°)
#define P2 1.570796325   //Aprox. value of PI/2   ( 90°)
#define P3 4.712388975   //Aprox. value of PI/3   (270°)
#define dP 6.2831853

namespace angle_util {
	float get_angle(float, float);
	float fix(float);
	float full_fix(float);
};