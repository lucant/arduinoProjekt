#ifndef _PULSERTOL_H
#define _PULSERTOL_H
#include "../pixels.h"

/**
 * Blinks on signal from last (pixel NUMPIXELS) to first (pixel 0) 
 * @param color Color of blinking
 */

void pulseRTOL()
{
    for (int i = 0; i < NUMPIXELS + 1; i++)
    {
        colorPallette();
        pixels.setPixelColor(NUMPIXELS - i, colorPalletteRGB);
        pixels.show();
    }

    pixels.clear();
    pixels.show();
    // for (int i = 0; i < NUMPIXELS; i++)
    // {
    //     pixels.setPixelColor(i, off);
    //     pixels.show();
    // }
}
#endif