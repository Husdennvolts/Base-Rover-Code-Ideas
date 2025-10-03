#include "definitions.h"

void processDriveMsg(canMsg_t msg);
void controlDriveMotor(unsigned int speed, unsigned int direction);
void controlSteerMotor(unsigned int angle);
