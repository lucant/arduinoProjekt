#ifndef _PULSEMIDDLE_H
#define _PULSEMIDDLE_H
#include "../pixels.h"

/**
 * Blinks on signal from middle (pixel NUMPIXELS/2) to first (pixel 0) and last pixel (pixel NUMPIXELS)
 * @param color Color of blinking
 */

void pulseMiddle(uint8_t activePixels)
{
    int start = (MIDDLE - activePixels / 2);
    pixels.fill(colorPalletteRGB, start, activePixels);
    pixels.show();
    pixels.clear();
    pixels.show();
}
#endif