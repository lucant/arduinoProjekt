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
#include <microsmooth.h>

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

void loop()
{
  checkButtonPress();

  float grooveSignal = 0.; // variable to save microphone signal
  //Get sample of 32 loops and afterwards scale it (>>= 5) to 1024 bits
  // for (int i = 0; i < 64; i++)
  // {
  //   grooveSignal += analogRead(A0);
  // }
  // grooveSignal >>= 5;
  //grooveSignal = sampling(); //read the value of the digital interface 3 assigned to val
  grooveSignal = sampling();

  int activePixelRatio = ((double)grooveSignal / 1024.0) * NUMPIXELS;

  Serial.print("Groovesignal: ");
  Serial.println(grooveSignal);
  Serial.print("PixelRatio: ");
  Serial.println(activePixelRatio);

  //pulseLTOR(grooveSignal, activePixelRatio);
  pulseMiddle(grooveSignal, activePixelRatio);
  // switch (LEDModeValue)
  // {
  // case 0: // Blink in current color mode
  //   blinkColor(colorPalletteRGB);
  //   break;
  // case 1: // go from left to right
  //   pulseLTOR(grooveSignal, activePixelRatio);
  //   break;
  // case 2: // go from right to left
  //   pulseRTOL();
  //   break;
  // case 3: // go from middle to right and left
  //   pulseMiddle();
  //   break;
  // case 4: // go from outside right and left to middle
  //   pulseOutside();
  //   break;
  // case 5: // switch beween even and odd pixels
  //   alterNate();
  //   break;
  // default:
  //   break;
  // }
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