#ifndef _FADERGB_H
#define _FADERGB_H
#include "pixels.h"

#define NUMCOLORS 9

// Fade variables
uint8_t redNew = 255;   // start from red
uint8_t greenNew = 0;   // initialize 0 to fade into
uint8_t blueNew = 0;    // initialize 0 to fade into
uint8_t fadeStatus = 0; // switches the RGB fade
uint8_t stepsize = 3;   // defines velocity of fade, must be odd number!

uint8_t currentColor = 0;

/**
 * Fades on each iteration from Red->Green->Blue with 
 * @param stepsize determines how fast you fade into the new color
 * @return pixels.Color(R, G, B) with new faded R G B values
 */
void fadeRGB(uint8_t stepsize)
{
  if (currentColor == 1) // Fade only when currentColor is on Fade
  {
    // Make stepsize and odd number if it es even
    if (stepsize % 2 == 0)
      stepsize += 1;

    if (fadeStatus == 0) // Fade from Red to Green
    {
      redNew = constrain(redNew - stepsize, 0, 255);
      greenNew = constrain(greenNew + stepsize, 0, 255);
      if (redNew == 0)
        fadeStatus = 1;
    }
    else if (fadeStatus == 1) // Fade from Green to Blue
    {
      greenNew = constrain(greenNew - stepsize, 0, 255);
      blueNew = constrain(blueNew + stepsize, 0, 255);
      if (greenNew == 0)
        fadeStatus = 2;
    }
    else // Fade from Blue to Red
    {
      blueNew = constrain(blueNew - stepsize, 0, 255);
      redNew = constrain(redNew + stepsize, 0, 255);
      if (blueNew == 0)
        fadeStatus = 0;
    }
    colorPalletteRGB = pixels.Color(redNew, greenNew, blueNew);
  }
}

void soundTemperature(uint8_t signalRGB)
{
  if (currentColor == 0) // Fade only when currentColor is on Fade
  {
    redNew = 255;
    if (signalRGB <= 80)
    {
      blueNew = constrain(blueNew + 10, 0, 255);
      greenNew = constrain(greenNew + 10, 0, 255);
    }
    if (signalRGB > 80 && signalRGB <= 200)
    {
      blueNew = constrain(blueNew - 75, 0, 255);
      greenNew = constrain(greenNew - 10, 0, 255);
    }
    if (signalRGB > 200)
    {
      blueNew = constrain(blueNew - 150, 0, 255);
      greenNew = constrain(greenNew - 150, 0, 255);
    }
    colorPalletteRGB = pixels.Color(redNew, greenNew, blueNew);
  }
}

#endif