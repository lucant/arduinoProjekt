#ifndef _PULSEOUTSIDE_H
#define _PULSEOUTSIDE_H
#include "../pixels.h"

/**
 * Blinks on signal from outside first (pixel 0) and last pixel (pixel NUMPIXELS) to (pixel NUMPIXELS/2)
 *  @param color Color of blinking
 */

void pulseOutside(uint8_t activePixels)
{

    pixels.fill(colorPalletteRGB, 0, (activePixels / 2));
    pixels.fill(colorPalletteRGB, MIDDLE + (MIDDLE - (activePixels / 2)), (activePixels / 2));
    pixels.show();
    pixels.clear();
    pixels.show();
}

#endif