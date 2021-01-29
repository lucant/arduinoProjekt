#ifndef _ALTERNATE_H
#define _ALTERNATE_H
#include "../pixels.h"

void alterNate(uint32_t color)
{
    set = set % 2;
    for (int i = 0; i < NUMPIXELS - 1; i++)
    {
        if (set == 1)
        {
            pixels.setPixelColor(i + i % 2, color);
            pixels.show();
            pixels.setPixelColor(i + i % 1 + 1, off);
            pixels.show();
        }
        else
        {
            pixels.setPixelColor(i + i % 2, off);
            pixels.show();
            pixels.setPixelColor(i + i % 1 + 1, color);
            pixels.show();
        }
    }

    set++;
}

#endif