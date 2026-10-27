#include "synth_lib/api_impls.h"

#include <math.h> // sinf()

sound_sample_t GetSample_fm_sinf(FM_Oscillator *osc)
{

    float mod = osc->I * sinf(osc->modulation_phase);

    float value = osc->amplitude * sinf(osc->carrier_phase + mod);

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
