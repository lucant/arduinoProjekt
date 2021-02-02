#ifndef _SAMPLE_H
#define _SAMPLE_H
#include "pixels.h"
//#include "Filter.h"
// #include <microsmooth.h>

const int MICRO = A0; // Pin to get signal from microphone
const int SAMPLERATE = 16;
unsigned long minSessionSample = 9999999;
unsigned long maxSessionSample = 0;
uint16_t sampling()
{

  unsigned long sample = 0;

  for (int i = 0; i < SAMPLERATE; i++)
  {
    sample += analogRead(MICRO);
  }
  if (sample < minSessionSample)
  {
    minSessionSample = sample;
  }

  if (sample > maxSessionSample)
  {
    maxSessionSample = sample;
  }

  sample = map(sample, minSessionSample, maxSessionSample, 1, 255);

  return sample;
}

float RunningAverageBuffer[SAMPLERATE];
int NextRunningAverage;
uint16_t samplingFloatingAverage()
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
  return RunningAverageTemperature;
}

int ema_filter(int current_value)
{
  static uint16_t exponential_average = current_value;

  exponential_average = (0.1 * (uint32_t)current_value + (100 - 0.1) * (uint32_t)exponential_average) / 100;
  return exponential_average;
}
#endif