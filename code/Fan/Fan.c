#include "Fan.h"
#include "Init/Init.h"

//may want to change this file to be a temp control.c and it can handle the drive board temp if neccesarry

/*----------------------------functions processed when message is received-----------------------------------------*/
//this would be used if this file controlled handled the driveboard temp stuff
void processTempMsg(canMsg_t msg)
{
    int SA;
    int device;

    if(getDevice() == FANBOARD)
    {
        SA = (msg.id & 0xFF);
        device = SAToDevice(SA);

        updateBoardTemps(msg, device);
    }
}

void updateBoardTemps(canMsg_t msg, int device)
{
    // take in the temp messages each board sends
    // compare it to a threshold
    // decide if that board is ok to continue its function
    // build a status massage to send to the main board
    // the main board will report it to base station and use the info to manage functionality
}

/*------------------------------------functions processed every tick-----------------------------------------------*/
float tempRunningAvg(float battCaseTemp, float mainCaseTemp)
{
    float battCaseAvg;
    float mainCaseAvg;
    //pass the temp sensor readings in and create a running average to 
    //maybe have a wrapping array the only remove the oldest sample and replace it with the new one
    //keep the average relevant
    tempToPWM(battCaseAvg, mainCaseAvg);
}

int tempToPWM(float battCaseAvg, float mainCaseAvg)
{
    //some sort of interpolation to go from the tempurature readings to a PWM signal 
}