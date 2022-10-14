#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <printf.h>

#define LEFT_EYE_PIN 5
#define RIGHT_EYE_PIN 6
#define CE_PIN   9
#define CSN_PIN 10

RF24 radio(CE_PIN, CSN_PIN);

char dataReceived[9];

const byte address[6] = "00002";

void setup() {
  pinMode(LEFT_EYE_PIN, OUTPUT);
  pinMode(RIGHT_EYE_PIN, OUTPUT);
  
  Serial.begin(9600);
  printf_begin();
  delay(1000);
  
  radio.begin();
  
  radio.openReadingPipe(0, address);   //Setting the address at which we will receive the data

  radio.setPayloadSize(sizeof(dataReceived)-1); //packet size, in bytes
  
  radio.setChannel(100); //select a channel (in which there is no noise!) 0 ... 125

  radio.setPALevel (RF24_PA_MAX); //transmitter power level. To choose RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  
  radio.setDataRate (RF24_250KBPS); //exchange rate. To choose RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
 
  radio.printDetails();
  radio.startListening();              //This sets the module as receiver
}
void loop()
{

    if (radio.available()) {

      radio.read(&dataReceived, sizeof(dataReceived)-1);    //Reading the data

      Serial.print("Received: ");
      Serial.print(dataReceived);
      Serial.println("|");

      if (strcmp(dataReceived,"FADE    ")==0) {
        FadingEyes(5, 0, 27510);
      }
    }
}

void FadingEyes(int fadeAmount, int brightness, int seconds) {
  Serial.print("FadingEyes");

  int counter = 0;
  while ((counter*30) < seconds) {
    analogWrite(LEFT_EYE_PIN, brightness);
    analogWrite(RIGHT_EYE_PIN, brightness);
    
    // change the brightness for next time through the loop:
    brightness = brightness + fadeAmount;

    // reverse the direction of the fading at the ends of the fade:
    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = -fadeAmount;
    }
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
    counter++;;
    //Serial.print(brightness);
    //Serial.print(":");
    //Serial.println((counter-1)*30);
  }

  analogWrite(LEFT_EYE_PIN, 0);
  analogWrite(RIGHT_EYE_PIN, 0);

}
