#include "definitions.h"

void processTempMsg(canMsg_t);
void updateBoardTemps(canMsg_t, int);
float tempRunningAvg(float, float);
int tempToPWM(float, float);