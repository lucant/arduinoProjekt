#ifndef _SINGLEPIXEL_H
#define _SINGLEPIXEL_H
#include "../pixels.h"

void singlePixel(uint8_t activePixelRatio)
{

    pixels.setPixelColor(MIDDLE + (activePixelRatio / 2), colorPalletteRGB);
    pixels.setPixelColor(MIDDLE - (activePixelRatio / 2), colorPalletteRGB);
    pixels.show();
    pixels.clear();
    pixels.show();
}

#endif