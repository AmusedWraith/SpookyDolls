#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include <printf.h>

#define CE_PIN   9
#define CSN_PIN 10

RF24 radio(CE_PIN, CSN_PIN);       
const byte address[6] = "00002";     //Byte of array representing the address. This is the address where we will send the data. This should be same on the receiving side.


void setup() {

Serial.begin(9600);
printf_begin();
delay(1000);
radio.begin();                  //Starting the Wireless communication
radio.openWritingPipe(address); //Setting the address where we will send the data
  radio.setPayloadSize(8); //packet size, in bytes
  
  radio.setChannel(100); //select a channel (in which there is no noise!) 0 ... 125
radio.setPALevel(RF24_PA_MAX);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
radio.setDataRate (RF24_250KBPS); //exchange rate. To choose RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
radio.printDetails();
radio.stopListening();          //This sets the module as transmitter
}
void loop()
{

  Serial.println("Sent");
const char text[] = "FADE    ";
radio.write(&text, sizeof(text));                  //Sending the message to receiver

delay(30000);
}
