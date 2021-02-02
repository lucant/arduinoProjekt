#ifndef _PULSERTOL_H
#define _PULSERTOL_H
#include "../pixels.h"

/**
 * Blinks on signal from last (pixel NUMPIXELS) to first (pixel 0) 
 * @param color Color of blinking
 */

void pulseRTOL(uint8_t activePixels)
{
    for (int i = 0; i < activePixels; i++)
    {
        pixels.setPixelColor(NUMPIXELS - i, colorPalletteRGB);
        pixels.show();
    }
    pixels.clear();
    pixels.show();
}
#endif