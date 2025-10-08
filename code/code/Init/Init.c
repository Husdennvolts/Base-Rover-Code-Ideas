#include "Init/Init.h"

Device_t getDevice(void)
{
    //based on dip switch pins this will return what device it is
    //if pins are invalid maybe send a device invalid masseage on the bus if possible(might not be since since you'd need a source adress)
}

Device_t SAtodevice(int SA)
{
    //take in the given SA from a message and provide what device sent out that message
}

