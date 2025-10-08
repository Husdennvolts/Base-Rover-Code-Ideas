#include "Light.h"
#include "Init/Init.h"

void processLightMsg(canMsg_t msg)
{
    if(getDevice() == LIGHTBOARD)
    {
        //convert mssage data PWM signals for each light and set the pinouts to the corresponding intensiy
    }
}