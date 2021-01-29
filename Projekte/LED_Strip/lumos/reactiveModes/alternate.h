#ifndef _ALTERNATE_H
#define _ALTERNATE_H
#include "../pixels.h"

void alterNate()
{
    set = set % 2;
    for (int i = 0; i < NUMPIXELS - 1; i++)
    {
        colorPallette();
        if (set == 1)
        {
            pixels.setPixelColor(i + i % 2, colorPalletteRGB);
            pixels.setPixelColor(i + i % 1 + 1, off);
        }
        else
        {
            pixels.setPixelColor(i + i % 2, off);
            pixels.setPixelColor(i + i % 1 + 1, colorPalletteRGB);
        }
        pixels.show();
    }

    set++;
}

#endif