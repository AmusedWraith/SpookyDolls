#include "SerialTransfer.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include <printf.h>

#define CE_PIN   9
#define CSN_PIN 10

const byte numChars = 16;
char receivedChars[numChars];   // an array to store the received data
boolean newData = false;


RF24 radio(CE_PIN, CSN_PIN);       
byte address[6];     //Byte of array representing the address. This is the address where we will send the data. This should be same on the receiving side.
char transmitMsg[9];

/*
 * Serial Format for Commands
 * 
 * 00001;FADE    ;;
 * 
 * 1-5: Address
 * 6: semicolon
 * 7-14: Command
 * 15: semicolon
 * 16: semicolon
 * 
 */


char dollCommand[8];

char dollAddress[5];

void setup()
{
  Serial.begin(9600);

  printf_begin();
  delay(1000);
  radio.begin();                  //Starting the Wireless communication
  radio.setPayloadSize(8); //packet size, in bytes
  radio.setChannel(100); //select a channel (in which there is no noise!) 0 ... 125
  radio.setPALevel(RF24_PA_MAX);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.setDataRate (RF24_250KBPS); //exchange rate. To choose RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
  radio.printDetails();

  Serial.println("Transmitter is Ready");

}


void loop()
{
  recvWithStartEndMarkers();
  processNewData();
  
}

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;
 
    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

void processNewData() {
    if (newData == true) {
        Serial.print("This just in ... ");
        Serial.println(receivedChars);

        memcpy(&dollAddress, &receivedChars, 5);

        memcpy(&dollCommand, &receivedChars[6], 8);

        sendCommand(dollCommand, dollAddress);

        newData = false;
    }
}

void sendCommand(char myCommand[8], char myAddress[5]) {

  Serial.println("Sending ");

  strncpy((char *)address,myAddress, 5);
  address[5] = '\0';

  strncpy(transmitMsg, myCommand, 8);
  transmitMsg[9] = '\0';

  radio.stopListening();
  radio.openWritingPipe(address); //Setting the address where we will send the data
  radio.write(transmitMsg, sizeof(transmitMsg)); 

  
}
