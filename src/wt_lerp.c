#include "synth_lib/api_impls.h"

sound_sample_t WT_GetSampleLerp(WT_Oscillator *osc)
{
    if (!osc->active)
	return 0;

    sound_sample_t outputValue = 0;

    int x0 = osc->phase >> 23;
    int x1 = (x0 + 1) & TABLE_WRAP;

    float y0 = tables[osc->table][x0];
    float y1 = tables[osc->table][x1];

    float f = (osc->phase & 0x7FFFFF) / (float)0x800000;
    float y = y0 + (y1 - y0) * f;

    outputValue = (sound_sample_t)(y * osc->amplitude);

    osc->phase += osc->increment;

    return outputValue;
}
