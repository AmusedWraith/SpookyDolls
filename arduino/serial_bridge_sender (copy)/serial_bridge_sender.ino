#include "SerialTransfer.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include <printf.h>

#define CE_PIN   9
#define CSN_PIN 10

RF24 radio(CE_PIN, CSN_PIN);       
byte address[6];     //Byte of array representing the address. This is the address where we will send the data. This should be same on the receiving side.
char transmitMsg[9];

//SerialTransfer myTransfer;

char dollCommand[14];

char command[8];

char dollAddress[5];

void setup()
{
  Serial.begin(9600);
  //Serial.begin(115200);
  //myTransfer.begin(Serial);

  printf_begin();
  delay(1000);
  radio.begin();                  //Starting the Wireless communication
  //radio.openWritingPipe(address); //Setting the address where we will send the data
  radio.setPayloadSize(8); //packet size, in bytes
  radio.setChannel(100); //select a channel (in which there is no noise!) 0 ... 125
  radio.setPALevel(RF24_PA_MAX);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.setDataRate (RF24_250KBPS); //exchange rate. To choose RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
  radio.printDetails();
  radio.stopListening();          //This sets the module as transmitter
}


void loop()
{
  /*
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
    
  }*/

  delay(1000);

  //byte address1[6];
  strcpy((char *)address,"00001");
  strncpy(transmitMsg, "FADE    ", 8);

  radio.stopListening();
  radio.openWritingPipe(address); //Setting the address where we will send the data
  radio.write(transmitMsg, sizeof(transmitMsg)); 

  delay(100);

 // byte address2[6];
  strcpy((char *)address,"00002");
  strncpy(transmitMsg, "FADE    ", 8);


  radio.stopListening();
  radio.openWritingPipe(address); //Setting the address where we will send the data
  radio.write(transmitMsg, sizeof(transmitMsg)); 
  
/*
  dollAddress[0] = '0';
  dollAddress[1] = '0';
  dollAddress[2] = '0';
  dollAddress[3] = '0';
  dollAddress[4] = '2';

  command[0] = 'F';
  command[1] = 'A';
  command[2] = 'D';
  command[3] = 'E';
  command[4] = ' ';
  command[5] = ' ';
  command[6] = ' ';
  command[7] = ' ';

  sendCommand(command, dollAddress);

  delay(1000);

   dollAddress[0] = '0';
  dollAddress[1] = '0';
  dollAddress[2] = '0';
  dollAddress[3] = '0';
  dollAddress[4] = '1';

   // sendCommand(command, dollAddress);

  delay(500);
*/
  
}

void sendCommand(char myCommand[], char myAddress[]) {

  Serial.println("Sending");

  memcpy(address, myAddress,5);
  address[5] = '\0';

  memcpy(transmitMsg, myCommand, 8);
  transmitMsg[9] = '\0';

  radio.stopListening();
  radio.openWritingPipe(address); //Setting the address where we will send the data
  radio.write(transmitMsg, sizeof(transmitMsg)); 

  
}
