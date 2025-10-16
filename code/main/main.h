#include "definitions.h"

void init(void);
void RxFifoQueue(void);
void processRxMessages(canMsg_t);
msgName_t whatMsgIsIt(canMsg_t);