#ifndef _PULSEMIDDLE_H
#define _PULSEMIDDLE_H
#include "../pixels.h"

/**
 * Blinks on signal from middle (pixel NUMPIXELS/2) to first (pixel 0) and last pixel (pixel NUMPIXELS)
 * @param color Color of blinking
 */

void pulseMiddle(uint32_t color)
{
    for (int i = 0; i < NUMPIXELS / 2 + 1; i++)
    {
        pixels.setPixelColor(MIDDLE + i, color);
        pixels.setPixelColor(MIDDLE - i, color);
        pixels.show();
    }
    pixels.clear();
    pixels.show();
}
#endif