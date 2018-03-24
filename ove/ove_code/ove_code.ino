/*
  @Author Geert Roumen
  @Project Sound design for industrial design
  @Team
  Iris Ritsma (Interaction Design)
  Ivan Kunjasic (Interaction Design)
  Ricardo Verheul (Advanced Product Design)
  @Page http://geertroumen.nl/portfolio/index.php?page=ove
  @Hardware
  Reed sensor
  Neopixel ring   https://www.adafruit.com/product/1586
  Force sensor    https://www.adafruit.com/product/166
  Sound board x2  https://www.adafruit.com/product/2342
*/

#define NUMPIXELS      26
#define NEOPIXEL_PIN 2

#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);


#define WEIGHT_ELEMENT_PIN A0

#define REED_SWITCH_PIN 4
#define HEATING_BUTTON_PIN 3

//UNCOMMENT TO HAVE SOUND
//#define MUTED

#ifdef MUTED
byte weighingSoundPins[] = { -1, -1, -1, -1, -1, -1, -1, -1};
byte doneSoundPin = -1;
byte startSoundPin = -1;
byte heatingSoundPin = -1;
byte heatingStartSoundPin = -1;
#else
byte weighingSoundPins[] = {12, A7, 11, A6, 10, A5, 9, A4};
byte doneSoundPin = 8;
byte startSoundPin = A3;
byte heatingSoundPin = A1;
byte heatingStartSoundPin = A2;
#endif

#define OFF 0
#define ON_BOTTLE_MEASURING 1
#define ON_POWDER_MEASURING 2
#define ON_BOTTLE_DONE 3
#define ON_POWDER_DONE 4
#define ON_HEATING 5
#define ON_HEARING_DONE 6

//define global variables
byte state = 0;
long modeTimer = 0;
byte modeTimerMode = OFF;
long resetTimer = 0;
byte powderSpoons = 0;

#define IS_BOTTLE 280 //TRESHHOLD FOR START SOUND
#define MIN_BOTTLE 580 //WEIGHT WITH EMPTY BOTTLE


boolean wasPowderBottle = false;

#define MIN_POWDER_BOX 522
#define MAX_POWDER_BOX 410
#define MAX_BOTTLE 700

//The moving average value for measurement.
float mov = 0;
//The moving average light value, to ensure smooth transitions.
float light = 0;

void setup() {
  initSoundPins();
  // initialize the serial communication:
  Serial.begin(9600);
  // This initializes the NeoPixel library.
  pixels.begin();
  //
  pinMode(REED_SWITCH_PIN, INPUT_PULLUP);
  pinMode(HEATING_BUTTON_PIN, INPUT_PULLUP);
}


void loop() {
  /*
    This is the stuff that always should happen
  */

  Serial.print(mov);
  Serial.print(",");
  Serial.print(analogRead(WEIGHT_ELEMENT_PIN));
  Serial.print(",");
  Serial.println(mov);
  measureScale();
  doResetTimer();
  //check if heating button is pressed and deal with it.
  heatingBehaviour();
  int maxValue;
  int minValue;
  if (isPowderBottle()) {
    //A powder bottle is detected
    Serial.println("POWDER BOTTLE SENSED");
    if (wasPowderBottle == false) {
      delay(800);
      //wait for the force sensor to stabilize, 
      //and set the moving average to the current value.
      mov = analogRead(WEIGHT_ELEMENT_PIN);
    }
    wasPowderBottle = true;
    /* maxValue = MAX_POWDER_BOX;
      minValue = MIN_POWDER_BOX;*/
    //Serial.println(abs(analogRead(WEIGHT_ELEMENT_PIN)-mov));
    if (abs(analogRead(WEIGHT_ELEMENT_PIN) - mov) > 10) {
      powderSpoons++;
      light += 64;
      setLightWeighing(light);
      if (powderSpoons > 3) {
        // light = map(mov, minValue, maxValue, 0, 255);
        //Serial.println(255);
        setLightDone(light);
        playDone();
        doneLightBehaviour();
      }
      playIncrease(powderSpoons + 4);
      delay(150);
      initSoundPins();
      delay(650);
      mov = analogRead(WEIGHT_ELEMENT_PIN);
    }
  } else {
    wasPowderBottle = false;
    maxValue = MAX_BOTTLE;
    minValue = MIN_BOTTLE;
    if (mov < maxValue) {
      int val = map(mov, minValue, maxValue, 0, 255);
      setLightWeighing(val);
      //Serial.println(val);
      playIncrease(floor(val / 32));
    } else {
      light = map(mov, minValue, maxValue, 0, 255);
      //Serial.println(255);
      setLightDone(light);
      playDone();
      doneLightBehaviour();
    }
  }
  delay(2);
}
