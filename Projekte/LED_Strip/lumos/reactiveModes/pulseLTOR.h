#ifndef _PULSELTOR_H
#define _PULSELTOR_H
#include "../pixels.h"

/**
 * Blinks on signal from first (pixel 0) to last (pixel NUMPIXELS)
 * @param color Color of blinking
 */

void pulseLTOR()
{

    for (int i = 0; i < NUMPIXELS + 1; i++)
    {
        colorPallette();
        pixels.setPixelColor(i, colorPalletteRGB);
        pixels.show();
    }

    for (int i = 0; i < NUMPIXELS; i++)
    {
        pixels.setPixelColor(NUMPIXELS - i, off);
        pixels.show();
    }
}
#endif