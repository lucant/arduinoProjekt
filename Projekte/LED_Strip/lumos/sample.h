#ifndef _SAMPLE_H
#define _SAMPLE_H
#include "pixels.h"
//#include "Filter.h"
// #include <microsmooth.h>

const int MICRO = A0; // Pin to get signal from microphone
const int SAMPLERATE = 52;

uint16_t sampling()
{

  long sample = 0;
  //Get sample of 32 loops and afterwards scale it (>>= 5) to 1024 bits
  for (int i = 0; i < SAMPLERATE; i++)
  {
    sample += analogRead(MICRO);
  }
  sample >>= 5;
  Serial.println(sample);
  return sample;
}

float RunningAverageBuffer[SAMPLERATE];
int NextRunningAverage;
uint16_t samplingMiddleWerd()
{
  float RawTemperature = analogRead(MICRO);

  RunningAverageBuffer[NextRunningAverage++] = RawTemperature;
  if (NextRunningAverage >= SAMPLERATE)
  {
    NextRunningAverage = 0;
  }
  float RunningAverageTemperature = 0;
  for (int i = 0; i < SAMPLERATE; ++i)
  {
    RunningAverageTemperature += RunningAverageBuffer[i];
  }
  RunningAverageTemperature /= SAMPLERATE;

  return RunningAverageTemperature * 2;
}

int ema_filter(int current_value)
{
  static uint16_t exponential_average = current_value;

  exponential_average = (0.1 * (uint32_t)current_value + (100 - 0.1) * (uint32_t)exponential_average) / 100;
  Serial.println(exponential_average);
  return exponential_average * 2;
}

float micLev = 0;
int sample;
uint8_t squelch = 7;
float sampleAvg = 0;
uint8_t maxVol = 15;
bool samplePeak = 0;
int sampleAgc, multAgc;
uint8_t targetAgc = 60;

void agcAvg()
{ // A simple averaging multiplier to automatically adjust sound sensitivity.

  multAgc = (sampleAvg < 1) ? targetAgc : targetAgc / sampleAvg; // Make the multiplier so that sampleAvg * multiplier = setpoint
  sampleAgc = sample * multAgc;
  if (sampleAgc > 255)
    sampleAgc = 255;

  //------------ Oscilloscope output ---------------------------
  //  Serial.print(targetAgc); Serial.print(" ");
  //  Serial.print(multAgc); Serial.print(" ");
  //  Serial.print(sampleAgc); Serial.print(" ");

  //  Serial.print(sample); Serial.print(" ");
  //  Serial.print(sampleAvg); Serial.print(" ");
  //  Serial.print(micLev); Serial.print(" ");
  //  Serial.print(samplePeak); Serial.print(" "); samplePeak = 0;
  //  Serial.print(100); Serial.print(" ");
  //  Serial.print(0); Serial.print(" ");
  //  Serial.println(" ");

} // agcAvg()

float getSample()
{

  int16_t micIn; // Current sample starts with negative values and large values, which is why it's 16 bit signed.
  static long peakTime;

  micIn = analogRead(A0);                                 // Poor man's analog Read.
  micLev = ((micLev * 31) + micIn) / 32;                  // Smooth it out over the last 32 samples for automatic centering. Needs to be a float.
  micIn -= micLev;                                        // Let's center it to 0 now.
  micIn = abs(micIn);                                     // And get the absolute value of each sample.
  sample = (micIn <= squelch) ? 0 : (sample + micIn) / 2; // Using a ternary operator, the resultant sample is either 0 or it's a bit smoothed out with the last sample.
  sampleAvg = ((sampleAvg * 31) + sample) / 32;           // Smooth it out over the last 32 samples.

  if (sample > (sampleAvg + maxVol) && millis() > (peakTime + 50))
  { // Poor man's beat detection by seeing if sample > Average + some value.
    samplePeak = 1;
    peakTime = millis();
  } // Then we got a peak, else we don't. Display routines need to reset the samplepeak value in case they miss the trigger.
  agcAvg();
  return sampleAvg*5;
} // getSample()



#endif