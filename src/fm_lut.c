#include "synth_lib/api_impls.h"
#include "sin_lut.h"


float sinfLUT(float x)
{
    unsigned int i = x / (2 * 3.1415926) * SIN_LUT_LENGTH;
    i &= (SIN_LUT_LENGTH - 1);
    return sinTable[i];
}

sound_sample_t GetSample_wt_lut(FM_Oscillator *osc)
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
