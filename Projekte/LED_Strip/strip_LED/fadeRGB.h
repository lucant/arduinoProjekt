#ifndef _FADERGB_H
#define _FADERGB_H
#include "pixels.h"

// Fade variables
uint32_t fadeRGBColor = pixels.Color(0, 0, 0); // initiliaze fader color
uint8_t redNew = 255;                          // start from red
uint8_t greenNew = 0;                          // initialize 0 to fade into
uint8_t blueNew = 0;                           // initialize 0 to fade into
uint8_t fadeStatus = 0;                        // switches the RGB fade
uint8_t stepsize = 5;                          // defines velocity of fade, must be odd number!
/**
 * Fades on each iteration from Red->Green->Blue with 
 * @param stepsize determines how fast you fade into the new color
 * @return pixels.Color(R, G, B) with new faded R G B values
 */
uint32_t fadeRGB()
{
  if (fadeStatus == 0) // Fade from Red to Green
  {
    redNew -= stepsize;
    greenNew += stepsize;
    if (redNew == 0)
      fadeStatus = 1;
  }
  else if (fadeStatus == 1) // Fade from Green to Blue
  {
    greenNew -= stepsize;
    blueNew += stepsize;
    if (greenNew == 0)
      fadeStatus = 2;
  }
  else // Fade from Blue to Red
  {
    blueNew -= stepsize;
    redNew += stepsize;
    if (blueNew == 0)
      fadeStatus = 0;
  }
  return pixels.Color(redNew, greenNew, blueNew);
}
#endif