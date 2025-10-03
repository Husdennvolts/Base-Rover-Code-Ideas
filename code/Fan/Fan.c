#include "Fan.h"
#include "Init/Init.h"

void processFanMsg(canMsg_t msg)
{
    if(getDevice() == FANBOARD)
    {
        //use mssage data to control the Fans
    }
}