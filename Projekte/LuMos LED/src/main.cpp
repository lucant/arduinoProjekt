/**
 * IMPORTANT: DO NOT CHANGE THE ORDER OF INCLUDES AND DEFINES
 */

#include "FastLED.h"
#include <FastLED.h>

#define OCTAVE 1   // Group buckets into octaves  (use the log output function LOG_OUT 1)
#define OCT_NORM 0 // Don't normalise octave intensities by number of bins
#define FHT_N 256  // set to 256 point fht
#define LED_PIN 5
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#include <FHT.h> // include the library

/**
 * Global variables
 */
//sint noise[] = {204, 198, 100, 85, 85, 80, 70, 70};
int noise[] = {100, 75, 100, 85, 85, 80, 70, 70};
float noise_fact[] = {15, 10, 1.5, 1, 1.2, 1.4, 1.7, 3};	 // noise level determined by playing pink noise and seeing levels [trial and error]{204,188,68,73,150,98,88,68}
float noise_fact_adj[] = {15, 10, 1.5, 1, 1.2, 1.4, 1.7, 3}; // noise level determined by playing pink noise and seeing levels [trial and error]{204,188,68,73,150,98,88,68}

int potiCounter = 0;
int hue = 0;

// Params for width and height
const uint8_t kMatrixWidth = 8;
const uint8_t kMatrixHeight = 18;
#define NUM_LEDS (kMatrixWidth * kMatrixHeight)
CRGB leds[NUM_LEDS];

int rollLEDCounter = 0;

void setup()
{
	Serial.begin(9600);
	delay(1000);
	FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
	FastLED.setBrightness(200);
	fill_solid(leds, NUM_LEDS, CRGB::Black);
	FastLED.show();

	//TIMSK0 = 0;	   // turn off timer0 for lower jitter
	ADCSRA = 0xe5; // set the adc to free running mode
	ADMUX = 0x40;  // use adc0
	DIDR0 = 0x01;  // turn off the digital input for adc0
}

// Returns the position of the next LED Pixel
uint16_t positionOfLED(uint8_t x, uint8_t y)
{
	return (((y * kMatrixWidth) + x) + rollLEDCounter) % NUM_LEDS;
}

void FHTWrapper()
{
	sei(); // reduces jitter
	cli(); // UDRE interrupt slows this way down on arduino1.0

	/*
		*   Fast Hartley Transform (FHT)
 		*/

	for (int i = 0; i < FHT_N; i++) // save 256 samples
	{
		while (!(ADCSRA & 0x10))
		{
			// wait for adc to be ready
		}

		ADCSRA = 0xf5; // restart adc
		byte m = ADCL; // fetch adc data
		byte j = ADCH;
		int k = (j << 8) | m; // form into an int
		k -= 0x0200;		  // form into a signed int
		k <<= 6;			  // form into a 16b signed int
		fht_input[i] = k;	  // put real data into bins
	}

	fht_window();	  // window the data for better frequency response
	fht_reorder();	  // reorder the data before doing the fht
	fht_run();		  // process the data in the fht
	fht_mag_octave(); // take the output of the fht  fht_mag_log()

	/**
 		* Potentiometer 
		*/

	if (potiCounter >= 50) // read from potentiometers every 50 loops
	{
		// set master_volume that defines the sensitivity of the LED
		ADMUX = 0x40 | (1 & 0x07);					 // set admux to look at Analogpin A1 - Master Volume
		while (!(ADCSRA & 0x10))					 // wait for adc to be ready
			ADCSRA = 0xf5;							 // restart adc
		delay(2);									 //
		while (!(ADCSRA & 0x10))					 // wait for adc to be ready
			ADCSRA = 0xf5;							 // restart adc
		byte m = ADCL;								 // fetch adc data
		byte j = ADCH;								 //
		int k = (j << 8) | m;						 // form into an int
		float master_volume = (k + 0.1) / 1000 + .5; // so the value will be between ~0.5 and 1.5
		for (int i = 1; i < 8; i++)					 // adjust every noise factor by new master_volume
		{
			noise_fact_adj[i] = noise_fact[i] * master_volume;
		}

		// set hue that defines color of the LED
		ADMUX = 0x40 | (2 & 0x07); // set admux to look at Analogpin A2 - Hue
		while (!(ADCSRA & 0x10))   // wait for adc to be ready
			ADCSRA = 0xf5;		   // restart adc
		delay(2);				   //
		while (!(ADCSRA & 0x10))   // wait for adc to be ready
			ADCSRA = 0xf5;		   // restart adc
		byte o = ADCL;			   // fetch adc data
		byte l = ADCH;			   //
		int h = (l << 8) | o;	   // form into an int
		if (h < 1023)
		{
			hue = map(h, 0, 1023, 0, 255); // map the value of h to 0 to 255
		}
		else
		{
			hue += 1;
			if (hue > 255)
			{
				hue = 0;
			}
		}

		ADMUX = 0x40 | (0 & 0x07); // set admux back to look at A0 analog pin again (to read the microphone input)
		potiCounter = 0;		   // reset potiCounter
	}

	sei();
	potiCounter++;
	// End of Fourier Transform code - output is stored in fht_oct_out[i].

	// i=0-7 frequency (octave) bins (don't use 0 or 1), fht_oct_out[1]= amplitude of frequency for bin 1
	// for loop a) removes background noise average and takes absolute value b) low / high pass filter as still very noisy
	// c) maps amplitude of octave to a colour between blue and red d) sets pixel colour to amplitude of each frequency (octave)
}

void wiggleRoll(bool bRoll)
{

	char str[500];

	int prev_octaveValues[8];
	int beat = 0;
	int prev_oct_j;
	int prev_beat = 0;
	int led_index = 0;
	int saturation = 0;
	int saturation_prev = 0;
	int saturation_treshold = 50;
	int brightness = 0;
	int brightness_prev = 0;
	for (int i = 2; i < 8; i++) // goes through each octave. skip the first 1, which is not useful
	{

		int octaveValue = 0;
		octaveValue = (fht_oct_out[i] - noise[i]); // take the pink noise average level out, take the asbolute value to avoid negative numbers

		if (octaveValue < 10)
		{
			octaveValue = 0;
		}
		octaveValue = octaveValue * noise_fact_adj[i];

		if (octaveValue < 10)
		{
			octaveValue = 0;
		}
		else
		{
			octaveValue = octaveValue * noise_fact_adj[i];
			if (octaveValue > 180) // if the current octave value reaches a certain threshold
			{
				if (i >= 7)
				{
					beat += 2;
				}
				else
				{
					beat += 1;
				}
			}
			octaveValue = octaveValue / 30;
			octaveValue = octaveValue * 30; // (force it to more discrete values)
		}

		prev_octaveValues[i] = octaveValue;
		// char mid[5];
		// strcat(str, "(");
		// strcat(str, itoa(i, mid, 10));
		// strcat(str, ") ");
		// char mid2[5];
		// strcat(str, itoa(octaveValue, mid2, 10));
		// strcat(str, "\t");
		// if (i == 7)
		// {
		// 	Serial.println(str);
		// 	memset(str, 0, sizeof(str));
		// }

		if (i >= 2)
		{
			led_index = 2 * i - 3; // creates values according to i (i->led_index: 2->1 ,3->3, 4->5, 5->7, 6->9, 7->11, 8->13)
			prev_oct_j = (octaveValue + prev_octaveValues[i - 1]) / 2;

			saturation = constrain(octaveValue + 30, 0, 255);
			saturation_prev = constrain(prev_oct_j + 30, 0, 255);
			brightness = constrain(octaveValue, 0, 255);
			brightness_prev = constrain(prev_oct_j, 0, 255);
			if (brightness == 255)
			{
				saturation = saturation_treshold;
				brightness = 200;
			}
			if (brightness_prev == 255)
			{
				saturation_prev = saturation_treshold;
				brightness_prev = 200;
			}

			for (uint8_t y = 0; y < kMatrixHeight; y++)
			{

				if (saturation != saturation_treshold)
					saturation = constrain(170 + saturation, 170, 255);
				leds[positionOfLED(led_index - 1, y)] = CHSV(hue, saturation, brightness);

				if (i > 2)
				{
					prev_oct_j = (octaveValue + prev_octaveValues[i - 1]) / 2;

					if (saturation_prev != saturation_treshold)
						saturation_prev = constrain(170 + saturation_prev, 170, 255);
					leds[positionOfLED(led_index - 2, y)] = CHSV(hue, saturation_prev, brightness_prev);
				}
			}
		}

		if (i == 2 && octaveValue > 100)
		{

			fill_solid(leds, NUM_LEDS, CHSV(((2 * hue) % hue), saturation_prev, brightness_prev));

		} 
	}
	if (beat >= 7)
	{
		fill_solid(leds, NUM_LEDS, CRGB::Gray);
		FastLED.setBrightness(120);
	}
	else
	{
		if (prev_beat != beat)
		{
			FastLED.setBrightness(40 + beat * beat * 5);
			prev_beat = beat;
		}
	}

	FastLED.show();

	if (bRoll)
	{
		if (beat) // if value of beat is anything else than 0 go
		{
			rollLEDCounter += ((beat + 4) / 2 - 2); //
			if (rollLEDCounter < 0)
			{
				rollLEDCounter = 1000;
			}
			if (beat > 3 && beat < 7)
			{
				FastLED.delay(20);
			}
			beat = 0;
		}
	}
	else
	{
		rollLEDCounter = 0;
		beat = 0;
	}
}

void wiggleFromOutside(bool bRoll)
{
	int prev_octaveValues[8];
	int beat = 0;
	int prev_oct_j;
	int prev_beat = 0;
	int led_index = 0;
	int saturation = 0;
	int saturation_prev = 0;
	int saturation_treshold = 50;
	int brightness = 0;
	int brightness_prev = 0;
	for (int i = 1; i < 8; i++) // goes through each octave. skip the first 1, which is not useful
	{

		int octaveValue = 0;
		octaveValue = (fht_oct_out[i] - noise[i]); // take the pink noise average level out, take the asbolute value to avoid negative numbers

		if (octaveValue < 10)
		{
			octaveValue = 0;
		}
		octaveValue = octaveValue * noise_fact_adj[i];

		if (octaveValue < 10)
		{
			octaveValue = 0;
		}
		else
		{
			octaveValue = octaveValue * noise_fact_adj[i];
			if (octaveValue > 180) // if the current octave value reaches a certain threshold
			{
				if (i >= 7)
				{
					beat += 2;
				}
				else
				{
					beat += 1;
				}
			}
			octaveValue = octaveValue / 30;
			octaveValue = octaveValue * 30; // (force it to more discrete values)
		}

		prev_octaveValues[i] = octaveValue;

		if (i >= 2)
		{
			led_index = 2 * i - 3; // creates values according to i (i->led_index: 2->1 ,3->3, 4->5, 5->7, 6->9, 7->11, 8->13)
			prev_oct_j = (octaveValue + prev_octaveValues[i - 1]) / 2;

			saturation = constrain(octaveValue + 30, 0, 255);
			saturation_prev = constrain(prev_oct_j + 30, 0, 255);
			brightness = constrain(octaveValue, 0, 255);
			brightness_prev = constrain(prev_oct_j, 0, 255);
			if (brightness == 255)
			{
				saturation = saturation_treshold;
				brightness = 200;
			}
			if (brightness_prev == 255)
			{
				saturation_prev = saturation_treshold;
				brightness_prev = 200;
			}

			// Left to right
			for (uint8_t y = 0; y < kMatrixHeight; y++)
			{
				if (saturation != saturation_treshold)
					saturation = constrain(170 + saturation, 170, 255);
				leds[positionOfLED(led_index - 1, y)] = CHSV(hue, saturation, brightness);
				leds[(NUM_LEDS - 1) - positionOfLED(led_index - 1, y)] = CHSV(hue, saturation, brightness);
				if (i > 2)
				{
					prev_oct_j = (octaveValue + prev_octaveValues[i - 1]) / 2;

					if (saturation_prev != saturation_treshold)
						saturation_prev = constrain(170 + saturation_prev, 170, 255);
					leds[positionOfLED(led_index - 2, y)] = CHSV(hue, saturation_prev, brightness_prev);
					leds[(NUM_LEDS - 1) - positionOfLED(led_index - 2, y)] = CHSV(hue, saturation_prev, brightness_prev);
				}
			}
		}
	}
	if (beat >= 7)
	{
		fill_solid(leds, NUM_LEDS, CRGB::Gray);
		FastLED.setBrightness(120);
	}
	else
	{
		if (prev_beat != beat)
		{
			FastLED.setBrightness(40 + beat * beat * 5);
			prev_beat = beat;
		}
	}

	FastLED.show();

	if (bRoll)
	{
		if (beat) // if value of beat is anything else than 0 go
		{
			rollLEDCounter += ((beat + 4) / 2 - 2); //
			if (rollLEDCounter < 0)
			{
				rollLEDCounter = 1000;
			}
			if (beat > 3 && beat < 7)
			{
				FastLED.delay(20);
			}
			beat = 0;
		}
	}
	else
	{
		rollLEDCounter = 0;
		beat = 0;
	}
}

void loop()
{

	bool bRoll = true; // set to true if you want the LED strip to roll reaching certain treshholds
	int mode = 0;

	while (1)
	{

		FHTWrapper();
		wiggleRoll(bRoll);
		//wiggleFromOutside(bRoll);
		// switch (mode)
		// {
		// case 0:
		//
		// 	break;
		// case 1:
		//
		// 	break;
		// default:
		// 	break;
		// }
	}
}
