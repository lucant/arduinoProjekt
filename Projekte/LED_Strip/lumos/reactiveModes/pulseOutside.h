#ifndef _PULSEOUTSIDE_H
#define _PULSEOUTSIDE_H
#include "../pixels.h"

/**
 * Blinks on signal from outside first (pixel 0) and last pixel (pixel NUMPIXELS) to (pixel NUMPIXELS/2)
 *  @param color Color of blinking
 */

void pulseOutside(uint16_t activePixels, uint16_t lastActivePixels)
{
    if (activePixels > lastActivePixels)
    {
        pixels.clear();
        pixels.show();
    }
    pixels.fill(colorPalletteRGB, 0, (activePixels / 2));
    pixels.fill(colorPalletteRGB, MIDDLE + (MIDDLE - (activePixels / 2)), (activePixels / 2));
    pixels.show();
}

#endif