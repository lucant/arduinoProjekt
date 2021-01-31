#ifndef _PULSELTOR_H
#define _PULSELTOR_H
#include "../pixels.h"

/**
 * Blinks on signal from first (pixel 0) to last (pixel NUMPIXELS)
 * @param color Color of blinking
 */

void pulseLTOR(uint16_t grooveSignal, int activePixels)
{
    // if (grooveSignal > 250)
    // {

        double activePixelRatio = ((double)grooveSignal / 1024.0) * NUMPIXELS;
        for (int i = 0; i < activePixelRatio + 1; i++)
        {
            fadeRGB(1);
            //pixels.setPixelColor(i, pixels.Color(grooveSignal, 0, 0));
            pixels.setPixelColor(i, colorPalletteRGB);
            pixels.show();
        }

        pixels.clear();
        pixels.show();
    // }
}
#endif