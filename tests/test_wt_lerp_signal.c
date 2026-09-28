#include "synth_lib/api_impls.h"
#include "unity/unity.h"

extern sound_sample_t* tables[3];

void setUp(void) {}
void tearDown(void) {}

void TestFrequency()
{
    WT_Oscillator osc;
    InitOsc_wt(&osc, 440.0f, 0, 1.0f);

    sound_sample_t previous;
    int numCrossess = 0;

    for (int i = 0; i < SAMPLING_RATE; i++)
    {
	sound_sample_t sample = GetSample_wt_lerp(&osc);
	if (previous <= 0 && sample > 0)
	{
	    numCrossess++;
	}
	previous = sample;
    }

    TEST_ASSERT_EQUAL_INT(440, numCrossess);
}

void TestOffset()
{
    WT_Oscillator osc;
    InitOsc_wt(&osc, 440.0f, 0, 1.0f);
    int32_t sum = 0;

    for (int i = 0; i < SAMPLING_RATE; i++)
    {
	sum += GetSample_wt_lerp(&osc);
    }

    sound_sample_t threshold = MAX_SAMPLE_VALUE * 0.001f;
    TEST_ASSERT_INT_WITHIN(threshold, 0, sum);
    
}

int main()
{
    WT_GenerateTables();
    UNITY_BEGIN();
    RUN_TEST(TestFrequency);
    RUN_TEST(TestOffset);
    return UNITY_END();
}
