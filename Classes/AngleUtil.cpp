#include "AngleUtil.h"

namespace angle_util {
	float get_angle(float dx, float dy) {
		float a;

		if (dx > 0) a = atan(dy / dx);
		else if (dx < 0) a = atan(dy / dx) + PI;
		else a = P2 * (dy / abs(dy));

		return fix(a);
	}

	float fix(float a) {
		if (a > dP) a -= dP;
		if (a < 0) a += dP;
		return a;
	}

	float full_fix(float a) {
		return 0.0;
	}
};