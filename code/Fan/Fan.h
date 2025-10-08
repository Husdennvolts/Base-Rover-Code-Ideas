#include "definitions.h"

typedef struct
{
    float tempAvg1;
    float tempAvg2;
    int samples;
    const int maxSamples;// = 10;
}runningAvg_t;

void processFanMsg(canMsg_t);
float tempRunningAvg(float, float);