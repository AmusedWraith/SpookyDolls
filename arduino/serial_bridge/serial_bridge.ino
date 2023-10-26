#include "SerialTransfer.h"


SerialTransfer myTransfer;

char dollCommand[14];

char command[8];

char dollAddress[5];

void setup()
{
  Serial.begin(115200);
  myTransfer.begin(Serial);
}


void loop()
{
  if(myTransfer.available())
  {
    myTransfer.rxObj(dollCommand);

    memcpy(&command, &dollCommand[0], 8);
    memcpy(&dollAddress, &dollCommand[9], 5);

    uint16_t sendSize = 0;

    ///////////////////////////////////////// Stuff buffer with struct
    sendSize = myTransfer.txObj(dollAddress, sendSize, sizeof(dollAddress));

    ///////////////////////////////////////// Stuff buffer with array
    sendSize = myTransfer.txObj(command, sendSize, sizeof(command));

    ///////////////////////////////////////// Send buffer
    myTransfer.sendData(sendSize);
    delay(500);
    
  }
}
