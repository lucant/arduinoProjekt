#ifndef _PULSEMIDDLE_H
#define _PULSEMIDDLE_H
#include "../pixels.h"

/**
 * Blinks on signal from middle (pixel NUMPIXELS/2) to first (pixel 0) and last pixel (pixel NUMPIXELS)
 * @param color Color of blinking
 */

void pulseMiddle(uint16_t grooveSignal, int activePixels)
{
    // if (grooveSignal > 500)
    // {
        for (int i = 0; i < activePixels + 1; i++)
        {
            fadeRGB(1);
            pixels.setPixelColor(MIDDLE + i, colorPalletteRGB);
            pixels.setPixelColor(MIDDLE + i + activePixels, off);
            // fadeRGB(stepsize);
            pixels.setPixelColor(MIDDLE - i, colorPalletteRGB);
            pixels.setPixelColor(MIDDLE - i - activePixels, off);
            pixels.show();
        }
        pixels.clear();
        pixels.show();
    // }
}
#endif