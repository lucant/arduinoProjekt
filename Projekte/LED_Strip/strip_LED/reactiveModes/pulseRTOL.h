#ifndef _PULSERTOL_H
#define _PULSERTOL_H
#include "../pixels.h"
/**
 * Blinks on signal from last (pixel NUMPIXELS) to first (pixel 0) 
 * @param color Color of blinking
 */

void pulseRTOL(uint32_t color)
{
    for (int i = 0; i < NUMPIXELS; i++)
    {
        pixels.setPixelColor(NUMPIXELS - i, color);
        pixels.show();
    }

    for (int i = 0; i < NUMPIXELS; i++)
    {
        pixels.setPixelColor(i, off);
        pixels.show();
    }
}
#endif