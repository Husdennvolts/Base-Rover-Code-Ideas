#include "main.h"
#include "definitions.h"
#include "Dirve/Drive.h"
#include "Arm/Arm.h"
#include "Fan/Fan.h"

//STM generated file when FDCAN is configured
void RxFifoQueue(void)
{
    //if message is received and is valid 
    //processRxMessages(stdMsg);
}

void processRxMessages(canMsg_t msg)
{
    switch(whatMsgIsIt(msg))
    {
        case DRIVE_MESSAGE:
            processDriveMsg(msg);
            break;
        case LIGHT_MESSAGE:
            processLightMsg(msg);
            break;
        case FAN_MESSAGE:
            processTempMsg(msg);
            break;
        case ARM_MESSAGE:
            processArmMsg(msg);
            break;
        default:
            break;
    }
}

msgName_t whatMsgIsIt(canMsg_t msg)
{
    msg.id = ((msg.id >> 8) && 0xFFFFu);

    if(msg.id < MAX_MESSAGE)
    {
        return (msg.id);   
    }
}