#pragma once

#if defined(PULSARION_MATH_SIMD_NONE) || defined(PULSARION_MATH_SIMD_DISABLE)
#define PULSARION_MATH_SIMD_NONE
#define PULSARION_MATH_ALIGN // We don't need to align anything
#elif defined(PULSARION_MATH_SIMD_SSE4_1)
#include <smmintrin.h>
#define PULSARION_MATH_ALIGN alignas(16) // SSE4.1 requires 16-byte alignment
#elif defined(PULSARION_MATH_SIMD_AVX)
#include <immintrin.h>
#define PULSARION_MATH_ALIGN alignas(32) // AVX requires 32-byte alignment
#else
#define PULSARION_MATH_SIMD_NONE
#define PULSARION_MATH_ALIGN // We don't need to align anything
#endif

#ifndef PULSARION_MATH_SIMD_NONE
#ifdef PULSARION_DISABLE_ALIGNMENT
#define PULSARION_MATH_ALIGN
#define PULSARION_MATH_ALIGNMENT_NONE
#endif
#endif
