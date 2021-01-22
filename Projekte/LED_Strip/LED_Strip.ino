#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define PIN            5
#define NUMPIXELS      60
#define MAXBRIGHTNESS 10
#define RGB_RAUM 255
#define MICRO 3

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
uint32_t magenta = pixels.Color(255, 0, 255);
uint32_t red = pixels.Color(255, 0, 0);
uint32_t green = pixels.Color(0, 255, 0);
uint32_t blue = pixels.Color(0, 0 , 255);
uint32_t off = pixels.Color(0, 0, 0);
uint32_t greenishwhite = pixels.Color(255, 0, 255);
int middle = NUMPIXELS / 2;
int delayval = 2;
int soundSignal = LOW;




void setup() {
  Serial.begin(9600);
  pixels.begin();
  pixels.show();
  pinMode(MICRO, INPUT);
  pixels.setBrightness(MAXBRIGHTNESS);
}

/**
   pixels.fill(color,start,end);
   Füllt alle Pixel von Start bis ende
   pixels.clear();
   Löscht alle Pixel
*/

void loop() {
  //  for (int i = 0; i < NUMPIXELS; i++) {
  //    pixels.setPixelColor(i, blue);
  //    pixels.show(); // This sends the updated pixel color to the hardware.
  //    delay(delayval); // Delay for a period of time (in milliseconds).
  //  }
  //  for (int i = 0; i < NUMPIXELS; i++) {
  //    pixels.setPixelColor(NUMPIXELS - i, off); // Moderately bright green color.
  //    pixels.show(); // This sends the updated pixel color to the hardware.
  //    delay(delayval); // Delay for a period of time (in milliseconds).
  //  }

  uint8_t redNew = random(0, RGB_RAUM);
  uint8_t greenNew = random(0, RGB_RAUM);
  uint8_t blueNew = random(0, RGB_RAUM);

  soundSignal = digitalRead(MICRO); //read the value of the digital interface 3 assigned to val
  if (soundSignal == HIGH) {
//    for (int i = 0; i < NUMPIXELS / 2; i++) {
//      pixels.setPixelColor(middle + i, pixels.Color(redNew, greenNew, blueNew));
//      pixels.show();
//      pixels.setPixelColor(middle - i, pixels.Color(redNew, greenNew, blueNew));
//      pixels.show();
//      delay(delayval);
//    }
pixels.fill(pixels.Color(redNew, greenNew, blueNew),0,NUMPIXELS);
pixels.show();
    pixels.clear();
    pixels.show();
    //    for (int i = 0; i < NUMPIXELS / 2; i++) {
    //      pixels.setPixelColor(i, off);
    //      pixels.show();
    //      pixels.setPixelColor(NUMPIXELS - i, off);
    //      pixels.show();
    //      delay(delayval / 2);
    //    }
  }

}
