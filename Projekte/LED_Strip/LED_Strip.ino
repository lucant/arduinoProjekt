#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define LED_DATA 5       // Pin on which to control LED strip
#define NUMPIXELS 60     // Number of Pixels on the LED strip
#define MAXBRIGHTNESS 10 // Change this value to determine brightness of LED strip
#define RGB_SPACE 255    // Maximum value of RGB address space
#define MICRO 3          // Pin to get signal from microphone

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LED_DATA, NEO_GRB + NEO_KHZ800);

// Some predefined colors:
uint32_t magenta = pixels.Color(255, 0, 255);
uint32_t red = pixels.Color(255, 0, 0);
uint32_t green = pixels.Color(0, 255, 0);
uint32_t blue = pixels.Color(0, 0, 255);
uint32_t off = pixels.Color(0, 0, 0);
uint32_t greenishwhite = pixels.Color(255, 0, 255);

int soundSignal = LOW; // variable to save microphone signal

// Aux variables for displaying different modes
int middle = NUMPIXELS / 2;
int delayval = 2;

/**
  Code for initialisation
 */
void setup()
{
  Serial.begin(9600);                  // Random RGB values for every Signal from microphone
  pixels.begin();                      // Init LED Strip
  pixels.show();                       // Start them with all LEDs off at the beginning
  pinMode(MICRO, INPUT);               // Microphone
  pixels.setBrightness(MAXBRIGHTNESS); // Brightness of LEDs
}

/**
  Main code that is executed in a infinite loop
 */
void loop()
{
  // Random RGB values for every signal from microphone
  uint8_t redNew = random(0, RGB_SPACE);
  uint8_t greenNew = random(0, RGB_SPACE);
  uint8_t blueNew = random(0, RGB_SPACE);

  soundSignal = digitalRead(MICRO); //read the value of the digital interface 3 assigned to val
  if (soundSignal == HIGH)          // if microphone detects a sound execute LED control
  {
    pixels.fill(pixels.Color(redNew, greenNew, blueNew), 0, NUMPIXELS);
    pixels.show();
    pixels.clear();
    pixels.show();
  }
}

/**
   pixels.fill(color,start,end);  // Sets all pixels with @param color from @param start to @param end
   pixels.clear();                // Sets all pixels to RGB (0,0,0)
*/

/** Pulsierend von Mitte nach Links und Rechts
      for (int i = 0; i < NUMPIXELS / 2; i++) {
      pixels.setPixelColor(middle + i, pixels.Color(redNew, greenNew, blueNew));
      pixels.show();
      pixels.setPixelColor(middle - i, pixels.Color(redNew, greenNew, blueNew));
      pixels.show();
      delay(delayval);
      }
      for (int i = 0; i < NUMPIXELS / 2; i++) {
      pixels.setPixelColor(i, off);
      pixels.show();
      pixels.setPixelColor(NUMPIXELS - i, off);
      pixels.show();
      delay(delayval / 2);
      }
      */

/** Pulsierend von ersten bis zum letzten Pixel und zurück
      for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, blue);
      pixels.show(); // This sends the updated pixel color to the hardware.
      delay(delayval); // Delay for a period of time (in milliseconds).
      }
      for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(NUMPIXELS - i, off); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      delay(delayval); // Delay for a period of time (in milliseconds).
      }
      */