#ifndef _BUTTONSETTINGS_H
#define _BUTTONSETTINGS_H
#include "pixels.h"

#define BUTTONMODE 8 // Pin that receives signal from MODE button
#define BUTTONUP 7   // Pin that receives signal from UP button
#define BUTTONDOWN 9 // Pin that receives signal from DOWN button
#define UP 1
#define DOWN 0
#define BRIGHTNESSSETTING 0
#define MODESETTING 1
#define COLORSETTING 2

/**
 * TODO: Comments on whole header as soon as implementation is done completly
 */

void brightnessSettingLED()
{
    uint8_t fadeWhite = 128;

    for (int i = 0; i < fadeWhite; i++)
    {
        pixels.fill(pixels.Color(i, i, i));
        pixels.show();
    }
    for (int i = 0; i < 80; i++)
    {
        pixels.fill(pixels.Color(fadeWhite - i, fadeWhite - i, fadeWhite - i));
        pixels.show();
    }
    pixels.clear();
    pixels.show();
}

void modeSettingLED()
{

    for (int i = 0; i < NUMPIXELS; i++)
    {
        colorPallette();
        pixels.setPixelColor(i, colorPalletteRGB);
        pixels.show();
        delay(10);
    }
    for (int i = 0; i < NUMPIXELS; i++)
    {
        pixels.setPixelColor(i, off);
        pixels.show();
        delay(10);
    }
}

void colorSettingLED()
{
    for (int j = 0; j < 3; j++)
    {
        for (int i = 0; i < NUMPIXELS; i++)
        {
            colorPallette();
            pixels.setPixelColor(i, colorPalletteRGB);
            pixels.show();
        }
        for (int i = 0; i < NUMPIXELS; i++)
        {
            pixels.setPixelColor(i, off);
            pixels.show();
        }
    }
}

void showStatusLED()
{
    pixels.clear();
    pixels.show();
    int modeSection[] = {0, MODE_NO};
    int colorSection[] = {MODE_NO + 3, 43};
    int hueSection[] = {NUMPIXELS - (MAXBRIGHTNESS / STEPBRIGHTNESS) - 1, (MAXBRIGHTNESS / STEPBRIGHTNESS)};

    // Show current Mode
    pixels.fill(grey, modeSection[0], modeSection[1]);
    pixels.fill(red, modeSection[0], LEDModeValue + 1);

    // Show current color pallete
    for (int i = colorSection[0]; i < colorSection[0] + colorSection[1]; i++)
    {
        colorPallette();
        pixels.setPixelColor(i, colorPalletteRGB);
    }
    // Show current brightness

    pixels.fill(grey, hueSection[0], hueSection[1]);
    pixels.fill(blue, hueSection[0], (brightness / STEPBRIGHTNESS));
    pixels.show();
}

void handleButtonMode()
{
    settingModeValue++;
    /**
     * TODO: Currently only 2 modes are implemented, therefore settingsModevalue is hardcoded
     */
    settingModeValue = settingModeValue % SETTINGS_NO;
    // settingModeValue = settingModeValue % 2;

    switch (settingModeValue)
    {
    case 0:
        brightnessSettingLED();
        break;
    case 1:
        modeSettingLED();
        break;
    case 2:
        colorSettingLED();
        break;
    default:
        break;
    }
}

void handleButton(int button)
{

    showStatusLED();
    delay(200);
    switch (button)
    {
    case UP:
        switch (settingModeValue)
        {
        case BRIGHTNESSSETTING:
            if (brightness + STEPBRIGHTNESS <= MAXBRIGHTNESS)
            {
                brightness += STEPBRIGHTNESS;
                pixels.setBrightness(brightness);
            }
            Serial.println(pixels.getBrightness());
            break;
        case COLORSETTING:
            currentColor = (currentColor + 1) % (NUMCOLORS);
            break;
        case MODESETTING:
            LEDModeValue = (LEDModeValue + 1) % (MODE_NO);
            Serial.println(LEDModeValue);
            break;
        default:
            break;
        }
        break;
    case DOWN:
        switch (settingModeValue)
        {
        case BRIGHTNESSSETTING:
            if (brightness > STEPBRIGHTNESS)
            {
                brightness -= STEPBRIGHTNESS;
                pixels.setBrightness(brightness);
            }
            Serial.println(pixels.getBrightness());
            break;
        case COLORSETTING:
            if (currentColor > 0)
                currentColor -= 1;
            else
                currentColor = 8;
            colorPalletteRGB = NUMCOLORS;
            break;
        case MODESETTING:
            if (LEDModeValue > 0)
                LEDModeValue -= 1;
            else
                LEDModeValue = MODE_NO - 1;
            Serial.println(LEDModeValue);
            break;
        default:
            break;
        }

    default:
        break;
    }
    showStatusLED();
    delay(500);
    pixels.clear();
    pixels.show();
}

#endif