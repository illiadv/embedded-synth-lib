#include <math.h>
#include <stdio.h>

#include "synth_lib/api_impls.h"
#include "unity/unity.h"

void setUp(void) {}
void tearDown(void) {}


void TestSinError()
{
    float error_threshold = 64.0f / SIN_LUT_LENGTH;

    float max_error = 0.0f;
    for (float x = 0.0f; x < 8 * 3.1415926f; x += 0.1f)
    {
	float y = sinf(x);
	float y_lut = sinfLUT(x);
	float error = fabsf(y - y_lut);
	// printf("x: %.5f, sinf: %.5f, lut: %.5f, error: %.5f\n", x, y, y_lut, error);
	
	TEST_ASSERT_FLOAT_WITHIN(error_threshold, y, y_lut);

	if (error > max_error)
	{
	    max_error = error;
	}
    }

    printf("max error: %.5f\n", max_error);
}

int main()
{
    UNITY_BEGIN();
    FM_GenerateLUT();
    RUN_TEST(TestSinError);
    return UNITY_END();
}
