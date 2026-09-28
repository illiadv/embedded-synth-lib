#ifndef API_IMPLS_H
#define API_IMPLS_H

#include "config.h"
#include "stdbool.h"

#ifdef __cplusplus
extern "C"
{
#endif

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

extern const sound_sample_t* tables[3];

void WT_GenerateTables();
void InitOsc_wt(WT_Oscillator *osc, float frequency, int table, float amplitude);
void SetFrequency_wt(WT_Oscillator *osc, float frequency);
sound_sample_t GetSample_wt_trunc(WT_Oscillator *osc);
sound_sample_t GetSample_wt_lerp(WT_Oscillator *osc);

void FM_GenerateLUT();
float sinfLUT(float x);
void InitOsc_fm(FM_Oscillator *osc, float carrier_freq, float modulation_freq, float d, float amplitude);
sound_sample_t GetSample_wt_sin(FM_Oscillator *osc);
sound_sample_t GetSample_wt_lut(FM_Oscillator *osc);

#ifdef __cplusplus
}
#endif

#endif
