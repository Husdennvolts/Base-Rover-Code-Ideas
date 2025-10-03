typedef struct
{
    unsigned int id;
    //not sure how this will work with messages of different lengths may be able to do a generic or dynamic array
    //may also just be set up already based on what RxElement that is pass(same thing i was unsure at our one meeting)
    unsigned char data[8];
} canMsg_t;

//message nakme definitions
typedef enum
{
    DRIVE_MESSAGE = 1,
    LIGHT_MESSAGE,
    FAN_MESSAGE,
    ARM_MESSAGE,
    MAX_MESSAGE
} msgName_t;

typedef enum
{
    DRIVEBOARD_1,
    DRIVEBOARD_2,
    DRIVEBOARD_3,
    DRIVEBOARD_4,
    DRIVEBOARD_5,
    DRIVEBOARD_6,
    ARMBOARD,
    LIGHTBOARD,
    FANBOARD,
    INVALID
} Device_t;


