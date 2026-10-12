#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>

#ifndef SIN_LUT_LENGTH
#define SIN_LUT_LENGTH 256
#endif

#ifndef TABLE_LENGTH
#define TABLE_LENGTH 512
#define TABLE_WRAP (TABLE_LENGTH - 1)
#endif

#ifndef SAMPLING_RATE
#define SAMPLING_RATE 8000
#endif

#ifndef MAX_SAMPLE_VALUE
#define MAX_SAMPLE_VALUE INT16_MAX
#endif

#ifndef MIN_SAMPLE_VALUE
#define MIN_SAMPLE_VALUE INT16_MIN
#endif

#ifndef SAMPLE_TYPE
#define SAMPLE_TYPE int16_t
#endif

#define TWO_PI 3.14159265f * 2

typedef SAMPLE_TYPE sound_sample_t;

#endif
