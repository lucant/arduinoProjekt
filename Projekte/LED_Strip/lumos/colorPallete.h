#ifndef _FADERGB_H
#define _FADERGB_H
#include "pixels.h"

#define NUMCOLORS 8

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
void colorPallette()
{
  switch (currentColor)
  {
  case 0:
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
    break;
  case 1:
    colorPalletteRGB = red;
    break;
  case 2:
    colorPalletteRGB = green;
    break;
  case 3:
    colorPalletteRGB = blue;
    break;
  case 4:
    colorPalletteRGB = white;
    break;
  case 5:
    colorPalletteRGB = magenta;
    break;
  case 6:
    colorPalletteRGB = cyan;
    break;
  case 7:
    colorPalletteRGB = yellow;
    break;
  default:
    break;
  }
}
#endif