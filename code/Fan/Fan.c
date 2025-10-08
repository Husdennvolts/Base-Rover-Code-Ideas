#include "Fan.h"
#include "Init/Init.h"

/*----------------------------functions processed when message is received-----------------------------------------*/
void processFanMsg(canMsg_t msg)
{
    if(getDevice() == FANBOARD)
    {
        //use mssage data to control the Fans
    }
}

/*------------------------------------functions processed every tick-----------------------------------------------*/
float tempRunningAvg(float tempSense1, float tempSense2)
{
    //pass the temp sensor readings in and create a running average to 
}