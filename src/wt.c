#include "synth_lib/api_impls.h"
#include "wavetables.h"

WT_Oscillator _wt_osc_default;

const sound_sample_t* tables[3] = {sinewaveTable, sawtoothTable, triangleTable};

void SetFrequency_wt(WT_Oscillator *osc, float frequency)
{
    osc->increment = (uint32_t)((frequency * 0x100000000) / SAMPLING_RATE);
}

void InitOsc_wt(WT_Oscillator *osc, float frequency, int table, float amplitude)
{
    osc->table = table;
    osc->amplitude = amplitude;
    osc->active = true;
    osc->phase = 0.0f;
    osc->increment = 0.0f;

    SetFrequency_wt(osc, frequency);
}
