#ifndef _BUTTON_H
#define _BUTTON_H
#include "pixels.h"

#define BUTTONMODE 8 // Pin that receives signal from MODE button
#define BUTTONUP 7   // Pin that receives signal from UP button
#define BUTTONDOWN 9 // Pin that receives signal from DOWN button
#define UP 1
#define DOWN 0
#define BRIGHTNESSSETTING 0
#define MODESETTING 1
#define SPEEDSETTING 2

/**
 * TODO: Comments on whole header as soon as implementation is done completly
 */

void brightnessSettingLED()
{
    for (int i = 0; i < 80; i++)
    {
        pixels.fill(grey);
        pixels.setBrightness(i);
        pixels.show();
    }
    for (int i = 0; i < 80; i++)
    {
        pixels.fill(grey);
        pixels.setBrightness(80 - i);
        pixels.show();
    }
    pixels.clear();
    pixels.show();
    pixels.setBrightness(brightness);
}

void modeSettingLED()
{
    for (int i = 0; i < NUMPIXELS; i++)
    {
        pixels.setPixelColor(i, white);
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

void speedSettingLED()
{
    for (int j = 0; j < 3; j++)
    {
        for (int i = 0; i < NUMPIXELS; i++)
        {
            pixels.setPixelColor(i, white);
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
    int modeSection[] = {0, MODE_NO + 1};
    int hueSection[] = {modeSection[1] + 2, (MAXBRIGHTNESS / STEPBRIGHTNESS)};
    // Show current Mode
    pixels.fill(grey, modeSection[0], modeSection[1]);
    pixels.fill(yellow, modeSection[0], LEDModeValue + 1);
    // Show current brightness
    pixels.fill(grey, hueSection[0], hueSection[1]);
    pixels.fill(cyan, hueSection[0], (brightness / STEPBRIGHTNESS));
    pixels.show();
}

void handleButtonMode()
{
    settingModeValue++;
    /**
     * TODO: Currently only 2 modes are implemented, therefore settingsModevalue is hardcoded
     */
    // settingModeValue = settingModeValue % SETTINGS_NO;
    settingModeValue = settingModeValue % 2;

    switch (settingModeValue)
    {
    case 0:
        brightnessSettingLED();
        break;
    case 1:
        modeSettingLED();
        break;
    case 2:
        speedSettingLED();
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
            break;
        case SPEEDSETTING:
            /**
             *   TODO: increase speed
             */
            break;
        case MODESETTING:
            LEDModeValue = (LEDModeValue + 1) % (MODE_NO + 1);
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
            break;
        case SPEEDSETTING:
            /**
             *   TODO: decrease speed
             */
            break;
        case MODESETTING:
            if (LEDModeValue > 0)
                LEDModeValue -= 1;
            else
                LEDModeValue = MODE_NO;
            break;
        default:
            break;
        }

    default:
        break;
    }
    showStatusLED();
    delay(400);
    pixels.clear();
    pixels.show();
}

#endif