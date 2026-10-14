#include "synth_lib/api_impls.h"
#include "sin_lut.h"

#define LUT_SCALE ((float)SIN_LUT_LENGTH / TWO_PI)
#define LUT_MASK  (SIN_LUT_LENGTH - 1)

float sinfLUTLerp(float x)
{
    float scaled = x * LUT_SCALE;

    int x0 = (int)scaled; 
    float f = scaled - (float)x0;

    int x1 = (x0 + 1) & LUT_MASK;
    x0 = x0 & LUT_MASK;

    float y0 = sinTable[x0];
    float y1 = sinTable[x1];

    return y0 + (y1 - y0) * f;
}

sound_sample_t GetSample_fm_lut_lerp(FM_Oscillator *osc)
{

    float mod = osc->I * sinfLUTLerp(osc->modulation_phase);

    float value = osc->amplitude * sinfLUTLerp(osc->carrier_phase + mod);

    osc->carrier_phase += osc->carrier_phase_inc;
    if (osc->carrier_phase >= TWO_PI) {
        osc->carrier_phase -= TWO_PI;
    }

    osc->modulation_phase += osc->modulation_phase_inc;
    if (osc->modulation_phase >= TWO_PI) {
        osc->modulation_phase -= TWO_PI;
    }

    return (sound_sample_t)(value * MAX_SAMPLE_VALUE);
}
