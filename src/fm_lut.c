#include "synth_lib/api_impls.h"
#include "sin_lut.h"

#define LUT_SCALE ((float)SIN_LUT_LENGTH / TWO_PI)
#define LUT_MASK  (SIN_LUT_LENGTH - 1)

float sinfLUT(float x)
{
    int i = (int)(x * LUT_SCALE);  
    return sinTable[i & LUT_MASK]; 
}

sound_sample_t GetSample_fm_lut(FM_Oscillator *osc)
{

    float mod = osc->I * sinfLUT(osc->modulation_phase);

    float value = osc->amplitude * sinfLUT(osc->carrier_phase + mod);

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
