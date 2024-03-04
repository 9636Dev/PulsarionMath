#pragma once

#ifdef PULSARION_MATH_SIMD_SSE4_1
#define PULSARION_MATH_ALIGN alignas(16)
#elif defined(PULSARION_MATH_SIMD_AVX)
#define PULSARION_MATH_ALIGN alignas(32)
#else
#define PULSARION_MATH_ALIGN
#endif
