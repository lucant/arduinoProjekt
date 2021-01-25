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
uint32_t white = pixels.Color(255, 255, 255);
uint32_t red = pixels.Color(255, 0, 0);
uint32_t green = pixels.Color(0, 255, 0);
uint32_t blue = pixels.Color(0, 0, 255);
uint32_t off = pixels.Color(0, 0, 0);
uint32_t greenishwhite = pixels.Color(255, 0, 255);

int soundSignal = LOW; // variable to save microphone signal

// Aux variables for displaying different modes
int middle = NUMPIXELS / 2; // Identify middle pixel
int delayval = 1;           // Determines how long a delay between a switch should be
int MODE = 5;               // Switches between different modes

// Fade variables
uint32_t fadeRGBColor = pixels.Color(0, 0, 0); // initiliaze fader color
uint8_t redNew = 255;                          // start from red
uint8_t greenNew = 0;                          // initialize 0 to fade into
uint8_t blueNew = 0;                           // initialize 0 to fade into
int fadeStatus = 0;                            // switches the RGB fade
int stepsize = 2;                              // defines velocity of fade

/**
  Code for initialisation
*/
void setup()
{
  Serial.begin(9600);                  // Init Serial
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

  soundSignal = digitalRead(MICRO); //read the value of the digital interface 3 assigned to val
  if (soundSignal == HIGH)          // if microphone detects a sound execute LED control
  {

    fadeRGB(stepsize);                                      // calculate new fading colours
    fadeRGBColor = pixels.Color(redNew, greenNew, blueNew); // insert values
    switch (MODE)
    {
    case 0: // Blink only in redlue
      blinkColor(red);
      break;
    case 1: // Blink only in green
      blinkColor(green);
      break;
    case 2: // Blink only in blue
      blinkColor(blue);
      break;
    case 4: // Blink only in white
      blinkColor(white);
      break;
    case 5: // Blink with a fade from RGB
      blinkColor(fadeRGBColor);
      break;
    case 6: // go from left to right
      pulseLTOR(fadeRGBColor);
      break;
    case 7: // go from right to left
      pulseRTOL(fadeRGBColor);
      break;
    case 8: // go from right to left
      pulseMiddle(fadeRGBColor);
      break;
    default:
      break;
    }
  }
}
/**
 * Blinks on signal in @param color
 */
void blinkColor(uint32_t color)
{
  pixels.fill(color, 0, NUMPIXELS);
  pixels.show();
  pixels.clear();
  pixels.show();
}

/**
 * Blinks on signal @param color from first (pixel 0) to last (pixel NUMPIXELS)
 */

void pulseLTOR(uint32_t color)
{

  for (int i = 0; i < NUMPIXELS; i++)
  {
    pixels.setPixelColor(i, color);
    pixels.show();
  }

  for (int i = 0; i < NUMPIXELS; i++)
  {
    pixels.setPixelColor(NUMPIXELS - i, off);
    pixels.show();
  }
}

/**
 * Blinks on signal @param color from last (pixel NUMPIXELS) to first (pixel 0) 
 */

void pulseRTOL(uint32_t color)
{
  for (int i = 0; i < NUMPIXELS; i++)
  {
    pixels.setPixelColor(NUMPIXELS - i, color);
    pixels.show();
  }

  for (int i = 0; i < NUMPIXELS; i++)
  {
    pixels.setPixelColor(i, off);
    pixels.show();
  }
}

/**
 * Blinks on signal in @param color from middle (pixel NUMPIXELS/2) to first (pixel 0) and last pixel (pixel NUMPIXELS)
 */

void pulseMiddle(uint32_t color)
{
  for (int i = 0; i < NUMPIXELS / 2 + 1; i++)
  {
    pixels.setPixelColor(middle + i, color);
    pixels.show();
    pixels.setPixelColor(middle - i, color);
    pixels.show();
  }
  for (int i = 0; i < NUMPIXELS / 2 + 1; i++)
  {
    pixels.setPixelColor(i, off);
    pixels.show();
    pixels.setPixelColor(NUMPIXELS - i, off);
    pixels.show();
  }
}
/**
 * Fades on each iteration from Red->Green->Blue with @param stepsize
 * @param stepsize must be 
 */
void fadeRGB(int stepsize)
{

  if (fadeStatus == 0)
  {
    greenNew += stepsize;
    redNew -= stepsize;
    if (redNew < 0)
    {
      fadeStatus = 1;
    }
  }
  else if (fadeStatus == 1)
  {
    blueNew += stepsize;
    greenNew -= stepsize;
    if (greenNew < 0)
    {
      fadeStatus = 2;
    }
  }
  else
  {
    redNew += stepsize;
    blueNew -= stepsize;

    if (blueNew < 0)
    {
      fadeStatus = 0;
    }
  }
}
