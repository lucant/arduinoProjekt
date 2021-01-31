#ifndef _SINGLEPIXEL_H
#define _SINGLEPIXEL_H
#include "../pixels.h"
long GroveVal = 0;
const int SampleRate = 64;
const int pinAdc = A0;

//Get sample of 32 loops and afterwards scale it (>>= 5) to 1024 bits

void singlePixel()
{
    for (int i = 0; i < SampleRate; i++)
    {
        GroveVal += analogRead(pinAdc);
    }
    GroveVal >>= 5;

    uint32_t color = pixels.Color(0, 0, 0);
    double ratio = 0.0;
    double pixelCount = NUMPIXELS;
    //Color(R,G,B)

    if (GroveVal < 300)
    {
        color = pixels.Color(0, 0, GroveVal);
    }

    if (GroveVal >= 300 && GroveVal < 600)
    {
        color = pixels.Color(0, GroveVal, 0);
    }

    if (GroveVal >= 600 && GroveVal < 1000)
    {
        color = pixels.Color(GroveVal, 0, 0);
    }

    for (int i = 0; i < NUMPIXELS; i++)
    {
        ratio = ((double)GroveVal / 1024.0);
        pixels.setPixelColor(ratio * pixelCount, color);
        pixels.show();
    }
    pixels.clear();
    pixels.show();
}

#endif