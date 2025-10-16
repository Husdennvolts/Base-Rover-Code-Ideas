#include "Init/Init.h"

void initIdPins(void)
{
    //do pin config for id pins **must be common between all boards**
}

Device_t initDeviceId(void)
{
    //based on dip switch pins this will return what device it is
    //if pins are invalid maybe send a device invalid masseage on the bus if possible(might not be since since you'd need a source adress)
    Device_t board_id = 0;
    board_id |= HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) << 0;
    board_id |= HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) << 1;
    board_id |= HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) << 2;
    board_id |= HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) << 3;
    board_id |= HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) << 4;
    return board_id;
}

void initRestOfPins(Device_t currDevice)
{
    switch(currDevice)
    {
        case DRIVEBOARD_1:
        case DRIVEBOARD_2:
        case DRIVEBOARD_3:
        case DRIVEBOARD_4:
        case DRIVEBOARD_5:
        case DRIVEBOARD_6:
            //configure drive board pins should be the same for all driveboards
            break;
        case ARMBOARD:
            //configure drive board pins should be the same for the arm board
            break;
        case LIGHTBOARD:
            //configure drive board pins should be the same for the light board
            break;
        case FANBOARD:
            //configure drive board pins should be the same for the fan board
            break;
        case TRANSLATOR:
            //configure drive board pins should be the same for the translator board
            break;
    } 
}

Device_t SAtodevice(int SA)
{
    //take in the given SA from a message and provide what device sent out that message
}

