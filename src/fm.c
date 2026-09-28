#include "synth_lib/api_impls.h"

FM_Oscillator _fm_osc_default;

void FM_InitOsc(FM_Oscillator *osc, float carrier_freq, float modulation_freq, float d, float amplitude)
{
    osc->carrier_frequency = carrier_freq;
    osc->modulation_frequency = modulation_freq;
    osc->d = d;
    osc->amplitude = amplitude;
    osc->t = 0.0f;
    osc->active = true;
}
