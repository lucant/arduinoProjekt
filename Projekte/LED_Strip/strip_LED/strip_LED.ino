#include <Arduino.h>
#include "pixels.h"
#include "fadeRGB.h"
#include "button.h"
#include "reactiveModes/blinkColor.h"
#include "reactiveModes/pulseLTOR.h"
#include "reactiveModes/pulseRTOL.h"
#include "reactiveModes/pulseMiddle.h"
#include "reactiveModes/pulseOutside.h"
#include "reactiveModes/alternate.h"

#define MICRO 3 // Pin to get signal from microphone

int soundSignal = LOW; // variable to save microphone signal
/**  TODO:
 *    - LEDModeValue ist static right now
 *    - Determine way to switch modes (e.g. Button, Remote Control)
 */

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

  // Make stepsize and odd number if it es even
  if (stepsize % 2 == 0)
    stepsize += 1;
}

/**
  Main code that is executed in a infinite loop
*/

void loop()
{
  checkButtonPress();

  soundSignal = digitalRead(MICRO); //read the value of the digital interface 3 assigned to val
  if (soundSignal == HIGH)          // if microphone detects a sound execute LED control
  {
    fadeRGBColor = fadeRGB(); // calculate new fading colours
    switch (LEDModeValue)
    {
    case 0: // Blink only in red
      blinkColor(red);
      break;
    case 1: // Blink only in green
      blinkColor(green);
      break;
    case 2: // Blink only in blue
      blinkColor(blue);
      break;
    case 3: // Blink only in white
      blinkColor(white);
      break;
    case 4: // Blink with a fade in RGB
      blinkColor(fadeRGBColor);
      break;
    case 5: // go from left to right
      pulseLTOR(fadeRGBColor);
      break;
    case 6: // go from right to left
      pulseRTOL(fadeRGBColor);
      break;
    case 7: // go from middle to right and left
      pulseMiddle(fadeRGBColor);
      break;
    case 8: // go from outside right and left to middle
      pulseOutside(fadeRGBColor);
      break;
    case 9: // switch beween even and odd pixels
      alterNate(fadeRGBColor);
      break;
    default:
      break;
    }
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