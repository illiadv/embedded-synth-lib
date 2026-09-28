#include "../build/generated/api.h"
#include "unity/unity.h"


void setUp(void) {}
void tearDown(void) {}

void TestFrequency()
{
    Oscillator osc;
    InitOsc(osc, 440.0f);

    sound_sample_t previous;
    int numCrossess = 0;

    for (int i = 0; i < SAMPLING_RATE; i++)
    {
	sound_sample_t sample = GetSample(&osc);
	if (previous <= 0 && sample > 0)
	{
	    numCrossess++;
	}
	previous = sample;
    }

    TEST_ASSERT_EQUAL_INT(440, numCrossess);
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(TestFrequency);
    return UNITY_END();
}
