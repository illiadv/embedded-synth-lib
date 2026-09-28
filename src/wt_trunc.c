#include "synth_lib/api_impls.h"


sound_sample_t GetSample_wt_trunc(WT_Oscillator *osc)
{
    if (!osc->active)
	return 0;

    sound_sample_t outputValue = 0;

    int index = osc->phase >> 23;
    float y = tables[osc->table][index];
    outputValue = (sound_sample_t)(y * osc->amplitude);

    osc->phase += osc->increment;

    return outputValue;
}
