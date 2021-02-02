#define FASTLED_INTERNAL
#include "FastLED.h"
#define NUM_LEDS 60
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];
void setup() {
  FastLED.addLeds<WS2812B, 5, COLOR_ORDER >(leds, NUM_LEDS);
}
void loop()
{
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Red;
    FastLED.show();

  }
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
    FastLED.show();

  }

}
