#include "Drive.h"
#include "Init/Init.h"

unsigned int reqAngle = 0;
unsigned int reqSpeed = 0;
unsigned int currAngle = 0;
unsigned int currSpeed = 0;
unsigned int dutyCycle = 0;
/*---------------------------------------------------------CAN communication stuff------------------------------------------------------------*/
void processDriveMsg(canMsg_t msg)
{
    unsigned int rawAngle = 0;
    unsigned int rawSpeed = 0;
    unsigned int direction;
    unsigned int nuetral;

    switch (getDevice())
    {
    case DRIVEBOARD_1:
        //use bytes 0-3 to control front left drive and steer motors

        // [0000 0000] [0000 0000]   [0000 0000] [0000 0000]
        // |___| |_______________|     |_| |_______________|
        //   |           |              |         |
        //   |    all for steering  direction   speed
        //unused                     nuetral

        //could probably optimize using fucntion with a for loop and some math
        rawAngle = (((msg.data[0] << 8) | msg.data[1]) & 0xFF);
        direction = ((msg.data[2] >> 4 ) & 0x1);
        nuetral = ((msg.data[2] >> 5 ) & 0x1);
        //possibly add a nuetral bit and if its set then that motor goes limp
        rawSpeed = ((((msg.data[2] << 8) & 0xF) | msg.data[3]) & 0xFF);

        //could optimize using by making scaling functions
        reqAngle = rawAngle * 0.0439453125;// 12bit: (-90 - 90)degrees
        speedPID(rawSpeed, direction);
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
void encoderISRCallback()
{
    int driveEncoderPosition;
    int currentStep = 0;
    int lastStep = 0;

//Determine what PWM channels to power based on encoder position 
    //use the hal function to get the encoder value
    driveEncoderPosition = getEncoderAngle();
    /*  
    (0xFFFF / 6) breaks the total range of the ecoder into six segments 
    (encoderPosition / (0xFFFF / 6)) find which of the six segments the its currently in
    (encoderPosition / (0xFFFF / 6)) % 6 gives a value from 0-5 even if an overflow occurs
    */
    //this is for 1 pole pair and will need to be adjusted if the BLDC has more pole pairs
    currentStep = (driveEncoderPosition / (0xFFFF / 6)) % 6;

    if (currentStep != lastStep)
    {
        lastStep = currentStep;
        SetPWM(currentStep);     
    }
}

void speedPID(int rawSpeed, int direction)
{
    reqSpeed = (rawSpeed * 0.0244140625);// 12bit: (0 - 100)%

    //implement PID to increase speed by adjusting the PWM duty cycle
}

void SetPWM(int step)
{
    //reset all the phases to 0

    switch (step) {
        case 0:
            // Set PWM for step 0
                // Phase A High
                // Phase B Low
            break;
        case 1:
            // Set PWM for step 1
                // Phase A High
                // Phase C Low
            break;
        case 2:
            // Set PWM for step 2
                // Phase B High
                // Phase C Low
            break;
        case 3:
            // Set PWM for step 3
                // Phase B High
                // Phase A Low
            break;
        case 4:
            // Set PWM for step 4
                // Phase C High
                // Phase A Low
            break;
        case 5:
            // Set PWM for step 5
                // Phase C High
                // Phase B Low
            break;
    }
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