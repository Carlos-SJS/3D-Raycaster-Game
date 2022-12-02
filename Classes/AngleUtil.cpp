#include "AngleUtil.h"

float angle_util::get_angle(float dx, float dy) {
	float a;

	if (dx > 0) a = atan(dy / dx);
	else if (dx < 0) a = atan(dy / dx) + PI;
	else a = P2 * (dy!=0?dy<0?-1:1:0);

	return fix(a);
}

float angle_util::fix(float a) {
	if (a > dP) a -= dP;
	if (a < 0) a += dP;
	return a;
}

float angle_util::full_fix(float a) {
	return 0.0;
}