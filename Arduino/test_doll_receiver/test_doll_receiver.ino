#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include <printf.h>

#define CE_PIN   9
#define CSN_PIN 10

RF24 radio(CE_PIN, CSN_PIN);

char dataReceived[6];


const byte address[6] = "00001";
boolean button_state = 0;
int led_pin = 3;
void setup() {
pinMode(led_pin, OUTPUT);
Serial.begin(9600);
printf_begin();
delay(1000);
radio.begin();
radio.openReadingPipe(0, address);   //Setting the address at which we will receive the data
radio.setPALevel(RF24_PA_MIN);       //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
radio.setPayloadSize(5); //packet size, in bytes


  radio.setChannel(100); //select a channel (in which there is no noise!) 0 ... 125

  radio.setPALevel (RF24_PA_MIN); //transmitter power level. To choose RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  radio.setDataRate (RF24_250KBPS); //exchange rate. To choose RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
 
radio.printDetails();
radio.startListening();              //This sets the module as receiver
}
void loop()
{

  
if (radio.available())              //Looking for the data.
{

radio.read(&dataReceived, sizeof(dataReceived)-1);    //Reading the data

if (strcmp(dataReceived,"Hello")==0) {
digitalWrite(led_pin, HIGH);
}

if (strcmp(dataReceived,"BYEEE")==0) {
digitalWrite(led_pin, LOW); 
}



Serial.println(dataReceived);


/*radio.read(&button_state, sizeof(button_state));    //Reading the data
#if(button_state == HIGH)
#{
#digitalWrite(led_pin, HIGH);
#Serial.println(text);
#}
#else
#{
#digitalWrite(led_pin, LOW);
#Serial.println(text);}
#}*/
delay(50);
}
}
