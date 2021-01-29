#include "pixels.h"
#include "colorPallete.h"
#include "buttonSettings.h"
#include "reactiveModes/blinkColor.h"
#include "reactiveModes/pulseLTOR.h"
#include "reactiveModes/pulseRTOL.h"
#include "reactiveModes/pulseMiddle.h"
#include "reactiveModes/pulseOutside.h"
#include "reactiveModes/alternate.h"

#define MICRO 3 // Pin to get signal from microphone

int soundSignal = LOW; // variable to save microphone signal

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

void loop()
{
  checkButtonPress();

  soundSignal = digitalRead(MICRO); //read the value of the digital interface 3 assigned to val
  if (soundSignal == HIGH)          // if microphone detects a sound execute LED control
  {
    switch (LEDModeValue)
    {
    case 0: // Blink in current color mode
      blinkColor(colorPalletteRGB);
      break;
    case 1: // go from left to right
      pulseLTOR();
      break;
    case 2: // go from right to left
      pulseRTOL();
      break;
    case 3: // go from middle to right and left
      pulseMiddle();
      break;
    case 4: // go from outside right and left to middle
      pulseOutside();
      break;
    case 5: // switch beween even and odd pixels
      alterNate();
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