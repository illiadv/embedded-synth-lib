#ifndef API_IMPLS_H
#define API_IMPLS_H

#include "config.h"
#include "stdbool.h"

typedef struct
{
    int table;
    uint32_t increment;
    uint32_t phase;
    bool active;
    float amplitude;
} WT_Oscillator;

typedef struct
{
    float carrier_frequency;
    float modulation_frequency;
    float d;
    bool active;
    float amplitude;
    float t;
} FM_Oscillator;

extern sound_sample_t* tables[3];

void WT_GenerateTables();
void WT_InitOsc(WT_Oscillator *osc, float frequency, int table, float amplitude);
void WT_SetFrequency(WT_Oscillator *osc, float frequency);
sound_sample_t WT_GetSampleTrunc(WT_Oscillator *osc);
sound_sample_t WT_GetSampleLerp(WT_Oscillator *osc);

void FM_GenerateLUT();
float sinfLUT(float x);
void FM_InitOsc(FM_Oscillator *osc, float carrier_freq, float modulation_freq, float d, float amplitude);
sound_sample_t FM_GetSample(FM_Oscillator *osc);
sound_sample_t FM_GetSampleLUT(FM_Oscillator *osc);

#endif
