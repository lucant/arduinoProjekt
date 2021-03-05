#include "pixels.h"
#include "colorPallete.h"
#include "buttonSettings.h"
#include "sample.h"
#include "reactiveModes/blinkColor.h"
#include "reactiveModes/pulseLTOR.h"
#include "reactiveModes/pulseRTOL.h"
#include "reactiveModes/pulseMiddle.h"
#include "reactiveModes/pulseOutside.h"
#include "reactiveModes/alternate.h"
#include "reactiveModes/singlePixel.h"

// uint16_t grooveSignal = 0; // variable to save microphone signal

/**
  Code for initialisation
*/

void setup()
{
  Serial.begin(115200);              // Init Serial
  pixels.begin();                    // Init LED Strip
  pixels.show();                     // Start them with all LEDs off at the beginning
  pinMode(MICRO, INPUT);             // Microphone
  pinMode(BUTTONMODE, INPUT_PULLUP); // ButtonMODE Switch
  pinMode(BUTTONUP, INPUT_PULLUP);   // ButtonUP Switch
  pinMode(BUTTONDOWN, INPUT_PULLUP); // ButtonDown Switch
  pixels.setBrightness(brightness);  // Brightness of LEDs
}

/**
  Main code that is executed in a infinite loop
*/
uint8_t minSession = 255;
uint8_t maxSession = 0;
uint16_t lastActivePixelRatio = 0;
uint16_t activePixelRatio = 0;
void loop()
{
  checkButtonPress();
  float grooveSignal = 0.; // variable to save microphone signal
  lastActivePixelRatio = map(grooveSignal, minSession, maxSession, 1, NUMPIXELS);
  grooveSignal = sampling();

  if (grooveSignal < minSession)
    minSession = grooveSignal;

  if (grooveSignal > maxSession)
    maxSession = grooveSignal;

  fadeRGB(stepsize);
  soundTemperature(grooveSignal);
  activePixelRatio = map(grooveSignal, minSession, maxSession, 1, NUMPIXELS);

  switch (LEDModeValue)
  {
  case 0: // Blink in current color mode
    blinkColor(grooveSignal, colorPalletteRGB);
    break;
  case 1: // go from left to right
    pulseLTOR(activePixelRatio);
    break;
  case 2: // go from right to left
    pulseRTOL(activePixelRatio);
    break;
  case 3: // go from middle to right and left
    pulseMiddle(activePixelRatio, lastActivePixelRatio);
    break;
  case 4: // go from outside right and left to middle
    pulseOutside(activePixelRatio, lastActivePixelRatio);
    break;
  case 5: // switch beween even and odd pixels
    alterNate();
    break;
  case 6: // same as middle but only displaying one pixel
    singlePixel(activePixelRatio);
  default:
    break;
  }
}

/**
 * checkButtonPress() checks for incoming button presses and
 * handels them by calling their respective handlers
 */
void checkButtonPress()
{

  if (digitalRead(BUTTONMODE) == LOW)
  {
    delay(250); // Delay to prevent multiple calls
    handleButtonMode();
  }
  if (digitalRead(BUTTONUP) == LOW)
  {
    delay(250); // Delay to prevent multiple calls
    handleButton(UP);
  }
  if (digitalRead(BUTTONDOWN) == LOW)
  {
    delay(250); // Delay to prevent multiple calls
    handleButton(DOWN);
  }
}