#ifndef _PULSEMIDDLE_H
#define _PULSEMIDDLE_H
#include "../pixels.h"

/**
 * Blinks on signal from middle (pixel NUMPIXELS/2) to first (pixel 0) and last pixel (pixel NUMPIXELS)
 * @param color Color of blinking
 */

void pulseMiddle(uint16_t activePixels, uint16_t lastActivePixels)
{
    if (activePixels > lastActivePixels)
    {
        pixels.clear();
        pixels.show();
    }
    int start = (MIDDLE - activePixels / 2);
    pixels.fill(colorPalletteRGB, start, activePixels);
    pixels.show();
}
#endif