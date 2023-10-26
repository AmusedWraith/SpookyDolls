#include "FastLED.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <printf.h>

#define DATA_PIN 3
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS 300
#define BRIGHTNESS 64

#define CE_PIN   9
#define CSN_PIN 10

CRGB leds[NUM_LEDS];

RF24 radio(CE_PIN, CSN_PIN);

char dataReceived[9];

char dataTime[3];

long commandTime;

const byte address[6] = "00006";

void setup() {

  Serial.begin(9600);
  printf_begin();

  delay(3000); // initial delay of a few seconds is recommended

  radio.begin();
  
  radio.openReadingPipe(0, address);   //Setting the address at which we will receive the data

  radio.setPayloadSize(sizeof(dataReceived)-1); //packet size, in bytes
  
  radio.setChannel(100); //select a channel (in which there is no noise!) 0 ... 125

  radio.setPALevel (RF24_PA_MAX); //transmitter power level. To choose RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  
  radio.setDataRate (RF24_250KBPS); //exchange rate. To choose RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
 
  radio.printDetails();
  radio.startListening();              //This sets the module as receiver
  

  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip); // initializes LED strip

  FastLED.setBrightness(BRIGHTNESS);// global brightness

  showProgramCleanUp(10);

}
// switches off all LEDs
void showProgramCleanUp(long delayTime) {
  for (int i = 0; i < NUM_LEDS; ++i) {
    leds[i] = CRGB::Black;
  }
  FastLED.setBrightness(0);
  FastLED.show();
  delay(delayTime);
}

// switches on all LEDs. Each LED is shown in random color.
// numIterations: indicates how often LEDs are switched on in random colors
// delayTime: indicates for how long LEDs are switched on.
void showProgramRandom(int numIterations, long delayTime) {
  for (int iteration = 0; iteration < numIterations; ++iteration) {
    for (int i = 0; i < NUM_LEDS; ++i) {
      leds[i] = CHSV(random8(),255,255); // hue, saturation, value
    }
    FastLED.show();
    delay(delayTime);
  }
}

// Shifts a single pixel from the start of strip to the end.
// crgb: color of shifted pixel
// delayTime: indicates how long the pixel is shown on each LED
void showProgramShiftSinglePixel(CRGB crgb, long delayTime) {
  for (int i = 0; i < NUM_LEDS; ++i) {
    leds[i] = crgb;
    FastLED.show();
    delay(delayTime);
    leds[i] = CRGB::Black;
  }
}

// Shifts multiple pixel from the start of strip to the end. The color of each pixel is randomized.
// delayTime: indicates how long the pixels are shown on each LED
void showProgramShiftMultiPixel(long delayTime) {
  for (int i = 0; i < NUM_LEDS; ++i) { 
    for (int j = i; j > 0; --j) {
      leds[j] = leds[j-1];
    }
    CRGB newPixel = CHSV(random8(), 255, 255);
    leds[0] = newPixel;
    FastLED.show();
    delay(delayTime);
  }
}

void setAllRGB(CRGB crgb) {
  for (int i = 0; i < NUM_LEDS; ++i) {
    leds[i] = crgb;
  }
  FastLED.show();
}

void fadeDown(int timeStep) {
  int currentBrightness = FastLED.getBrightness();
  for(int i = currentBrightness; i >= 0; --i) {
    Serial.print("Brightness set to:");
    Serial.println(i);
    FastLED.setBrightness(i);
    FastLED.show();
    delay(timeStep);
  }
}

void fadeUp(int timeStep) {
  int currentBrightness = FastLED.getBrightness();
  for(int i = currentBrightness; i<= BRIGHTNESS; ++i) {
    Serial.print("Brightness set to:");
    Serial.println(i);
    FastLED.setBrightness(i);
    FastLED.show();
    delay(timeStep);
  }
}


// main program
void loop() {

  if (radio.available()) {

    radio.read(&dataReceived, sizeof(dataReceived)-1);    //Reading the data

      CRGB colorToUse;

      Serial.print("Received: ");
      Serial.print(dataReceived);
      Serial.println("|");

      if (  
        (dataReceived[0] == 'R') &&
        (dataReceived[1] == 'D') ) {

          colorToUse = CRGB::Red;

      }

      if (  
        (dataReceived[0] == 'G') &&
        (dataReceived[1] == 'N') ) {

          colorToUse = CRGB::Green;

      }

      if (  
        (dataReceived[0] == 'B') &&
        (dataReceived[1] == 'L') ) {

          colorToUse = CRGB::Blue;

      }

      if (  
        (dataReceived[0] == 'A') &&
        (dataReceived[1] == 'Q') ) {

          colorToUse = CRGB::Aqua;

      }

      

      if (  
        (dataReceived[2] == 'G') &&
        (dataReceived[3] == 'L') &&
        (dataReceived[4] == 'W') ) {

          dataTime[0] = dataReceived[5];
          dataTime[1] = dataReceived[6];
          dataTime[2] = dataReceived[7];

          commandTime = atol(dataTime)*1000;

          Fading(commandTime, colorToUse);

      }

      if (  
        (dataReceived[2] == 'F') &&
        (dataReceived[3] == 'L') &&
        (dataReceived[4] == 'H') ) {

          dataTime[0] = dataReceived[5];
          dataTime[1] = dataReceived[6];
          dataTime[2] = dataReceived[7];

          commandTime = atol(dataTime)*1000;

          Flashing(commandTime, colorToUse);

      }

    }

    delay(1000);

  //showProgramCleanUp(2500); // clean up
  //showProgramRandom(100, 100); // show "random" program
  
  //showProgramCleanUp(2500); // clean up
  //showProgramRandom(10, 1000); // show "random" program
  
  //showProgramCleanUp(2500); // clean up
  //showProgramShiftSinglePixel(CRGB::Blue, 250); // show "shift single pixel program" with blue pixel
  
  //showProgramCleanUp(2500); // clean up
  //showProgramShiftSinglePixel(CRGB::Maroon, 100); // show "shift single pixel program" with maroon pixel
  
  //showProgramCleanUp(2500); // clean up
  //showProgramShiftMultiPixel(500); // show "shift multi pixel" program
  
  //showProgramCleanUp(2500); // clean up
  //showProgramShiftMultiPixel(50); // show "shift multi pixel" program
}

void Fading(long seconds, CRGB crgb) {

  showProgramCleanUp(10);
  setAllRGB(crgb);
  int elapsed = 0;
  while ( elapsed < seconds) {
    fadeUp(10);
    fadeDown(10);
    elapsed += 1780;
    delay(500);
  }
  showProgramCleanUp(10);

}

void Flashing(long seconds, CRGB crgb) {

  showProgramCleanUp(10);
  setAllRGB(crgb);
  int elapsed = 0;
  while ( elapsed < seconds) {
    FastLED.setBrightness(0);
    FastLED.show();
    elapsed += 50;
    delay(50);
    FastLED.setBrightness(BRIGHTNESS);
    FastLED.show();
    elapsed += 50;
    delay(50);
  }
  showProgramCleanUp(10);

}
