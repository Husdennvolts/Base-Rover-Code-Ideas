#include "main.h"
#include "definitions.h"
#include "Dirve/Drive.h"
#include "Arm/Arm.h"

//STM generated file when FDCAN is configured
void RxFifoQueue(void)
{
    //if message is received and is valid 
    //processRxMessages(stdMsg);
}

void processRxMessages(canMsg_t stdMsg)
{
    switch(whatMsgIsIt(stdMsg))
    {
        case DRIVE_MESSAGE:
            processDriveMsg(stdMsg);
            break;
        case LIGHT_MESSAGE:
            processLightMsg(stdMsg);
            break;
        case FAN_MESSAGE:
            processFanMsg(stdMsg);
            break;
        case ARM_MESSAGE:
            processArmMsg(stdMsg);
            break;
        default:
            break;
    }
}

msgName_t whatMsgIsIt(canMsg_t msg)
{
    msg.id = ((msg.id >> 4) && 0xFFFFu);

    if(msg.id < MAX_MESSAGE)
    {
        return (msg.id);   
    }
}