#include "synth_lib/api_impls.h"

#include <math.h> // sin() needed by WT_GenerateTables()

sound_sample_t sinewaveTable[TABLE_LENGTH] = {0};
sound_sample_t sawtoothTable[TABLE_LENGTH] = {0};
sound_sample_t triangleTable[TABLE_LENGTH] = {0};

sound_sample_t* tables[3] = {sinewaveTable, sawtoothTable, triangleTable};

void WT_SetFrequency(WT_Oscillator *osc, float frequency)
{
    osc->increment = (uint32_t)((frequency * 0x100000000) / SAMPLING_RATE);
}

void WT_InitOsc(WT_Oscillator *osc, float frequency, int table, float amplitude)
{
    osc->table = table;
    osc->amplitude = amplitude;
    osc->active = true;
    osc->phase = 0.0f;
    osc->increment = 0.0f;

    WT_SetFrequency(osc, frequency);
}

void WT_GenerateTables()
{
    for (int i = 0; i < TABLE_LENGTH; i++)
    {
	sinewaveTable[i] = (sin(i* 2 * 3.141592f / TABLE_LENGTH)) * (MAX_SAMPLE_VALUE);

	sawtoothTable[i] = ((float)i / TABLE_LENGTH * 2 - 1.0f) * MAX_SAMPLE_VALUE;

	float v = (i < TABLE_LENGTH / 2) ? (float)i : TABLE_LENGTH - (float)i;
	v = v * 2;
	v = v / TABLE_LENGTH * 2 - 1.0f;
	triangleTable[i] = v * MAX_SAMPLE_VALUE;
    }
}
