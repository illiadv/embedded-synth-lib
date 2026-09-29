#include "synth_lib/api_impls.h"

#include <math.h> // sin()

sound_sample_t GetSample_fm_sin(FM_Oscillator *osc)
{
    float value;

    float a = 2 * 3.14592f * osc->carrier_frequency;
    float b = 2 * 3.14592f * osc->modulation_frequency;

    float I = osc->d / osc->modulation_frequency;

    // e = Asin (at + I sin bt)
    value = osc->amplitude * sin(a * osc->t + I * sin(b * osc->t));

    osc->t += (1.0f / SAMPLING_RATE);

    return (sound_sample_t)(value * MAX_SAMPLE_VALUE);
}
