#include "synth_lib/api_impls.h"
#include "unity/unity.h"

void setUp(void) {}
void tearDown(void) {}

void TestLerp()
{
    WT_GenerateTables();
    WT_Oscillator osc;
    WT_InitOsc(&osc, 1.0f, 0, 1.0f);

    tables[0][0] = 0;
    tables[0][1] = 100;
    // osc.phase = 0.5f;
    osc.phase = 1 << 22;

    sound_sample_t output = WT_GetSampleLerp(&osc);
    TEST_ASSERT_EQUAL_INT(50, output);
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(TestLerp);
    return UNITY_END();
}
