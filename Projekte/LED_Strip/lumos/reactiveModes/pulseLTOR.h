#ifndef _PULSELTOR_H
#define _PULSELTOR_H
#include "../pixels.h"

/**
 * Blinks on signal from first (pixel 0) to last (pixel NUMPIXELS)
 * @param color Color of blinking
 */

void pulseLTOR(uint16_t activePixels)
{
    pixels.fill(colorPalletteRGB, 0, activePixels);
    pixels.show();
    pixels.clear();
    pixels.show();
}
#endif