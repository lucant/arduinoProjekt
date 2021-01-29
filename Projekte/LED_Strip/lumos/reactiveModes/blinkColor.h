#ifndef _BLINKCOLOR_H
#define _BLINKCOLOR_H
#include "../pixels.h"

/**
 * Blinks on signal 
 * @param color Color of blinking
 */
void blinkColor(uint32_t color)
{
    pixels.fill(color, 0, NUMPIXELS);
    pixels.show();
    pixels.clear();
    pixels.show();
}

#endif