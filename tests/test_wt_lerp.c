#include "synth_lib/api_impls.h"
#include "unity/unity.h"

void setUp(void) {}
void tearDown(void) {}

void TestLerp()
{
    GenerateTables_WT();
    WT_Oscillator osc;
    InitOsc_wt(&osc, 1.0f, 0, 1.0f);

    tables[0][0] = 0;
    tables[0][1] = 100;
    // osc.phase = 0.5f;
    osc.phase = 1 << 22;

    sound_sample_t output = GetSample_wt_lerp(&osc);
    TEST_ASSERT_EQUAL_INT(50, output);
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(TestLerp);
    return UNITY_END();
}
