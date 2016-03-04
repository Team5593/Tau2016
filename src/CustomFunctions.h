#ifndef CUSTOMFUNCTIONS_H
#define CUSTOMFUNCTIONS_H

// Map
float Map(float rawAxis, float in_min, float in_max, float out_min, float out_max) {
	return rawAxis * (out_max - out_min) / (in_max - in_min) + out_min;
}

// Sign
int Sign(float input) {
	if (input < 0) {
		return -1;
	}
	else if (input > 0) {
		return 1;
	}
	else {
		return 0;
	}
}

// Axis Deadband 
float AxisDeadband(float rawAxis, float deadzone) {
	if (abs(rawAxis) < deadzone) {
		return 0;
	}
	else {
		return rawAxis;
	}
}


#endif
