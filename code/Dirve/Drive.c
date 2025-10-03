#include "Drive.h"
#include "Init/Init.h"

unsigned int rawAngle;
unsigned int direction;
unsigned int rawSpeed;
unsigned int angle;
unsigned int speed;

void processDriveMsg(canMsg_t msg)
{
    switch (getDevice())
    {
    case DRIVEBOARD_1:
        //use bytes 0-3 to control front left drive and steer motors

        //could probably optimize using fucntion with a for loop and some math
        rawAngle = (((msg.data[0] << 8) | msg.data[1]) & 0xFFF);
        direction = ((msg.data[2] >> 4 ) & 0x1);
        //possibly add a nuetral bit and if its set then that motor goes limp
        rawSpeed = (((msg.data[2] << 8) | msg.data[3]) & 0xFFF);

        //could optimize using by making scaling functions
        angle = rawAngle * 0.0439453125;// 12bit - 180degrees
        speed = rawSpeed * 0.0244140625;// 12bit - 100%

        controlDriveMotor(speed, direction);
        controlSteerMotor(angle);
        break;
    case DRIVEBOARD_2:
        //use bytes 4-7 to control front left drive and steer motors
        break;
    case DRIVEBOARD_3:
        //use bytes 8-11 to control front left drive and steer motors
        break;
    case DRIVEBOARD_4:
        //use bytes 12-15 to control front left drive and steer motors
        break;
    case DRIVEBOARD_5:
        //use bytes 16-19 to control front left drive and steer motors
        break;
    case DRIVEBOARD_6:
        //use bytes 20-23 to control front left drive and steer motors
        break;
    default:
        break;
    }
}

//the heaviest part of this will be swapping between reading encoder values and changing phases to drive the motor 
//it will be tricky to swap contexts between reaing and adjusting till you reach you desired angle
//may need some sort of rtos to handle something like this not to sure
void controlDriveMotor(unsigned int speed, unsigned int direction)
{
    //could add a buffer for speed so it does waste resources always setting changing the speed of the motor (if speed is is withing + or - 5% dont change)
    //maybe only change direction when the direction bit changes
    //justin would like a brake motor as well so if nuetral bit isnt set and speed is 0 the brake motor will hold the wheel in position
    //read encoder and swap phases at a rate determined by the requested speed 
}
void controlSteerMotor(unsigned int angle)
{
    //read absolute encoder and adjust angle till current and requested angle match
}