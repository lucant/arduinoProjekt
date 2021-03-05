#ifndef _PIXELS_H
#define _PIXELS_H
#include <Adafruit_NeoPixel.h>

#define LED_DATA 5              // Pin on which to control LED strip
#define NUMPIXELS 144      // Number of Pixels on the LED strip
#define MAXBRIGHTNESS 255 // Change this value to determine brightness of LED strip
#define STEPBRIGHTNESS 51 // Change this value to increase speed of dimming NOTE: (must be a divisor of MAXBRIGHTNESS)
#define MODE_NO 7         // Defines maximum number of modes
#define SETTINGS_NO 3     // Defines maximum number of settings

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LED_DATA, NEO_GRB + NEO_KHZ800); // Init LED strip

const int MIDDLE = NUMPIXELS / 2; // Identify middle pixel
const int DELAY = 1;              // Determines how long a delay between a switch should be

// Some p redefined colors:
uint32_t colorPalletteRGB = pixels.Color(0,0,0); // Stores the current color pallette for all the modes
uint32_t white = pixels.Color(255, 255, 255);
uint32_t grey = pixels.Color(127, 127, 127);
uint32_t red = pixels.Color(255, 0, 0);
uint32_t green = pixels.Color(0, 255, 0);
uint32_t blue = pixels.Color(0, 0, 255);
uint32_t yellow = pixels.Color(255, 255, 0);
uint32_t magenta = pixels.Color(255, 0, 255);
uint32_t cyan = pixels.Color(0, 255, 255);
uint32_t off = pixels.Color(0, 0, 0);

uint8_t LEDModeValue = 0;     // Switches between different LED modes
uint8_t settingModeValue = 0; // Switches between different settings (Mode,Brightness,Speed)
uint8_t set = 0;              // Counter to switch between sets of pixels
uint8_t brightness = ((MAXBRIGHTNESS / STEPBRIGHTNESS) / 2) * STEPBRIGHTNESS;

#endif