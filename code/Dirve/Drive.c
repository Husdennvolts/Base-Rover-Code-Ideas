#include "Drive.h"
#include "Init/Init.h"

unsigned int step = 0;
unsigned int direction;
unsigned int rawAngle = 0;
unsigned int rawSpeed = 0;
unsigned int reqAngle = 0;
unsigned int reqSpeed = 0;
unsigned int currAngle = 0;
unsigned int currSpeed = 0;
/*---------------------------------------------------------CAN communication stuff------------------------------------------------------------*/
void processDriveMsg(canMsg_t msg)
{
    switch (getDevice())
    {
    case DRIVEBOARD_1:
        //use bytes 0-3 to control front left drive and steer motors

        //could probably optimize using fucntion with a for loop and some math
        rawAngle = (((msg.data[0] << 8) | msg.data[1]) & 0xFF);
        direction = ((msg.data[2] >> 4 ) & 0x1);
        //possibly add a nuetral bit and if its set then that motor goes limp
        rawSpeed = (((msg.data[2] << 8) | msg.data[3]) & 0xFF);

        //could optimize using by making scaling functions
        reqAngle = rawAngle * 0.0439453125;// 12bit: (-90 - 90)degrees
        reqSpeed = rawSpeed * 0.0244140625;// 12bit: (0 - 100)%
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
/*---------------------------------------------------------BLDC motor stuff------------------------------------------------------------*/
void controlDriveMotor()
{
    //could add a buffer for speed so it does waste resources always setting changing the speed of the motor (if speed is is withing + or - 5% dont change)
    //only change direction when the direction bit changes
    //justin would like a brake motor as well so if nuetral bit isnt set and speed is 0 the brake motor will hold the wheel in position
    //read encoder and swap phases at a rate determined by the requested speed (my head hurts thinking about doing this)


    int driveEncoderPosition;
    const unsigned int commutation_table[6][6] = {
    {1, 0, 0, 0, 1, 0}, // Step 1
    {1, 0, 0, 1, 0, 0}, // Step 2
    {0, 0, 1, 1, 0, 0}, // Step 3
    {0, 1, 1, 0, 0, 0}, // Step 4
    {0, 1, 0, 0, 0, 1}, // Step 5
    {0, 0, 0, 0, 1, 1}  // Step 6
    };

//Determine what PWM channels to power based on encoder position 
    //use the hal function to get the encoder value
    driveEncoderPosition = getEncoderAngle();
    /*  
    (0xFFFF / 6) breaks the total range of the ecoder into six segments 
    (encoderPosition / (0xFFFF / 6)) find which of the six segments the its currently in
    (encoderPosition / (0xFFFF / 6)) % 6 gives a value from 0-5 even if an overflow occurs
    */
    step = (driveEncoderPosition / (0xFFFF / 6)) % 6;
    SetPWM();
}

void SetPWM()
{
    /*
    1. use the step calculated to know what pwm channels to turn on
    2. use a PID or equivalent method to adjust the current speed up to the requested speed
    3. use the output of the PID to set the high pwm duty cycle
    */
}
/*---------------------------------------------------------Steer motor stuff------------------------------------------------------------*/
void controlSteerMotor()
{
    //read absolute encoder and adjust angle till current and requested angle match

    int steerEncoderPosition;

    //use the hal function to get the encoder value
    steerEncoderPosition = getEncoderAngle();
    // use a PID or equivalent method to adjust the current angle to the requested angle
}
/*---------------------------------------------------------brake motor stuff------------------------------------------------------------*/
void controlBrakeMotor()
{
    //read absolute encoder and adjust angle till current and requested angle match
}