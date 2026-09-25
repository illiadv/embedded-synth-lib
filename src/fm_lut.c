#include "synth_lib/api_impls.h"

#include <math.h> // sin() needed by FM_GenerateLUT

float LUT[SIN_LUT_LENGTH];

void FM_GenerateLUT()
{
    for (int i = 0; i < SIN_LUT_LENGTH; i++)
    {
	float x = (float)i / SIN_LUT_LENGTH * 2 * 3.1415926f;
	LUT[i] = sinf(x);
    }
}

float sinfLUT(float x)
{
    unsigned int i = x / (2 * 3.1415926) * SIN_LUT_LENGTH;
    i &= (SIN_LUT_LENGTH - 1);
    return LUT[i];
}

sound_sample_t FM_GetSampleLUT(FM_Oscillator *osc)
{
    float value;

    float a = 2 * 3.14592f * osc->carrier_frequency;
    float b = 2 * 3.14592f * osc->modulation_frequency;

    float I = osc->d / osc->modulation_frequency;

    // e = Asin (at + I sin bt)
    value = osc->amplitude * sinfLUT(a * osc->t + I * sinfLUT(b * osc->t));

    osc->t += (1.0f / SAMPLING_RATE);

    return (sound_sample_t)(value * MAX_SAMPLE_VALUE);
}
