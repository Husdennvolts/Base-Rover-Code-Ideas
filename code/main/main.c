#include "main.h"
#include "definitions.h"
#include "Dirve/Drive.h"
#include "Arm/Arm.h"
#include "Fan/Fan.h"
#include "Init/Init.h"

void init(void)
{
    //runs once on boot up 
    Device_t currDevice;
    //initialize dip switch pins
    initIdPins();
    //read dip switch pins to get device id
    currDevice = initDeviceId();
    //initialize the rest of the pins based on what device it is
    initRestOfPins(currDevice);

    //runs every tick and controle the peripherals
    while (1) {
        //maybe do a function pointer for this
        switch (currDevice) {
            case DRIVEBOARD_1:
            case DRIVEBOARD_2:
            case DRIVEBOARD_3:
            case DRIVEBOARD_4:
            case DRIVEBOARD_5:
            case DRIVEBOARD_6:
                controlDriveMotor();
                controlSteerMotor();
                controlbrakeMotor();
                break;
            case ARMBOARD:
                break;
            case LIGHTBOARD:
                break;
            case FANBOARD:
                break;
            case TRANSLATOR:
                break;
        }
    }
}

//STM generated file when FDCAN is configured
void RxFifoQueue(void)
{
    canMsg_t msg;
    //if message is received and is valid 
    processRxMessages(msg);
}

//runs when a message enters the queue and updates variables for the control loop to use next tick
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