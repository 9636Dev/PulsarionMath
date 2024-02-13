#pragma once

#if defined(PULSARION_MATH_SIMD_NONE) || defined(PULSARION_MATH_SIMD_DISABLE)
#define PULSARION_MATH_SIMD_NONE
#define PULSARION_MATH_ALIGN alignas(1) // We don't need to align anything
#elif defined(PULSARION_MATH_SIMD_SSE4_1)
#include <smmintrin.h>
#define PULSARION_MATH_ALIGN alignas(16) // SSE4.1 requires 16-byte alignment
#elif defined(PULSARION_MATH_SIMD_AVX)
#include <immintrin.h>
#define PULSARION_MATH_ALIGN alignas(32) // AVX requires 32-byte alignment
#endif

namespace Pulsarion::Shader
{

}
