#include "synth_lib/api_impls.h"

FM_Oscillator _fm_osc_default;

void InitOsc_fm(FM_Oscillator *osc, float carrier_freq, float modulation_freq, float d, float amplitude)
{
    osc->amplitude = amplitude;
    osc->active = true;
    SetFrequency_fm(osc, carrier_freq, modulation_freq, d);
}

void SetFrequency_fm(FM_Oscillator *osc, float f_c, float f_m, float d)
{
    float inv_sr = 1.0f / SAMPLING_RATE;
    
    osc->carrier_phase_inc = 3.14159 * 2 * f_c * inv_sr;
    osc->modulation_phase_inc=  3.14159 * 2 * f_m * inv_sr;
    
    // Prevent division by zero
    osc->I = (f_m > 0.001f) ? (d / f_m) : 0.0f;
}
