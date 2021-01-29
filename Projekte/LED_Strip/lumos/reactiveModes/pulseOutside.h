#ifndef _PULSEOUTSIDE_H
#define _PULSEOUTSIDE_H
#include "../pixels.h"

/**
 * Blinks on signal from outside first (pixel 0) and last pixel (pixel NUMPIXELS) to (pixel NUMPIXELS/2)
 *  @param color Color of blinking
 */

void pulseOutside(uint32_t color)
{

    for (int i = 0; i < NUMPIXELS / 2 + 1; i++)
    {
        fadeRGBColor = fadeRGB();
        pixels.setPixelColor(i, fadeRGBColor);
        pixels.show();
        pixels.setPixelColor(NUMPIXELS - i, fadeRGBColor);
        pixels.show();
    }
    pixels.clear();
    pixels.show();
}

#endif