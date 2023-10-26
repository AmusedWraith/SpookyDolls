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

char dataTime[3];

long commandTime;

const byte address[6] = "00007";

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

      if (  
        (dataReceived[0] == 'F') &&
        (dataReceived[1] == 'A') &&
        (dataReceived[2] == 'D') &&
        (dataReceived[3] == 'E') ) {

          dataTime[0] = dataReceived[5];
          dataTime[1] = dataReceived[6];
          dataTime[2] = dataReceived[7];

          commandTime = atol(dataTime)*1000;
 
          FadingEyes(5, 0, commandTime);
      }

      if (  
        (dataReceived[0] == 'T') &&
        (dataReceived[1] == 'E') &&
        (dataReceived[2] == 'S') &&
        (dataReceived[3] == 'T') ) {

          dataTime[0] = dataReceived[5];
          dataTime[1] = dataReceived[6];
          dataTime[2] = dataReceived[7];

          commandTime = atol(dataTime)*1000;

          FullEyes(commandTime);
 
      }

      if (  
        (dataReceived[0] == 'F') &&
        (dataReceived[1] == 'L') &&
        (dataReceived[2] == 'A') &&
        (dataReceived[3] == 'S') &&
        (dataReceived[4] == 'H')) {

          dataTime[0] = dataReceived[5];
          dataTime[1] = dataReceived[6];
          dataTime[2] = dataReceived[7];

         commandTime= atol(dataTime)*1000;

          FlashEyes(commandTime);
 
      }

    }

    delay(1000);
}

void FullEyes(long seconds) {
  Serial.print("Starting FullEyes seconds:");
  Serial.println(seconds);

  digitalWrite(LEFT_EYE_PIN,HIGH);
  digitalWrite(RIGHT_EYE_PIN,HIGH);
  

  delay(seconds);

  digitalWrite(LEFT_EYE_PIN,LOW);
  digitalWrite(RIGHT_EYE_PIN,LOW);
  Serial.println("Ending FullEyes");

}

void FlashEyes(long seconds) {
  Serial.print("Starting FlashEyes seconds:");
  Serial.println(seconds);

  int elapsed = 0;
  while ( elapsed < seconds) {

    int count = elapsed/100;

    if( (count%2) == 0) {
        digitalWrite(LEFT_EYE_PIN,HIGH);
        digitalWrite(RIGHT_EYE_PIN,HIGH);
    } else {
        digitalWrite(LEFT_EYE_PIN,LOW);
        digitalWrite(RIGHT_EYE_PIN,LOW);
    }

    elapsed += 100;
    delay(100);
  }

  digitalWrite(LEFT_EYE_PIN,LOW);
  digitalWrite(RIGHT_EYE_PIN,LOW);

  Serial.println("Ending FlashEyes");

}

void FadingEyes(int fadeAmount, int brightness, long seconds) {

  Serial.print("Starting FadingEyes fadeAmount:");
  Serial.print(fadeAmount);
  Serial.print(" brightness:");
  Serial.print(brightness);
  Serial.print(" seconds:");
  Serial.println(seconds);

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

  }

  analogWrite(LEFT_EYE_PIN, 0);
  analogWrite(RIGHT_EYE_PIN, 0);
  Serial.println("Ending FadingEyes");

}
