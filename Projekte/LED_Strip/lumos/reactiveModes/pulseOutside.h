#ifndef _PULSEOUTSIDE_H
#define _PULSEOUTSIDE_H
#include "../pixels.h"

/**
 * Blinks on signal from outside first (pixel 0) and last pixel (pixel NUMPIXELS) to (pixel NUMPIXELS/2)
 *  @param color Color of blinking
 */

void pulseOutside()
{

    for (int i = 0; i < NUMPIXELS / 2 + 1; i++)
    {
        colorPallette();
        pixels.setPixelColor(i, colorPalletteRGB);
        colorPallette();
        pixels.setPixelColor(NUMPIXELS - i, colorPalletteRGB);
        pixels.show();
    }
    pixels.clear();
    pixels.show();
}

#endif