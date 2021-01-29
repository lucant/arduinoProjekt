#ifndef _PULSEMIDDLE_H
#define _PULSEMIDDLE_H
#include "../pixels.h"

/**
 * Blinks on signal from middle (pixel NUMPIXELS/2) to first (pixel 0) and last pixel (pixel NUMPIXELS)
 * @param color Color of blinking
 */

void pulseMiddle()
{
    for (int i = 0; i < NUMPIXELS / 2 + 1; i++)
    {
        fadeRGB(stepsize);
        pixels.setPixelColor(MIDDLE + i, colorPalletteRGB);
        fadeRGB(stepsize);
        pixels.setPixelColor(MIDDLE - i, colorPalletteRGB);
        pixels.show();
    }
    pixels.clear();
    pixels.show();
}
#endif