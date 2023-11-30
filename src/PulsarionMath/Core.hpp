#pragma once

#include <cstdint>
#include <compare>

#if (defined(__SSE__) || defined(__AVX__)) && !defined(PULSARION_MATH_DISABLE_SIMD)
#include <xsimd/xsimd.hpp>
#define PULSARION_MATH_USE_SIMD
#ifdef __SSE__
#define PULSARION_MATH_ALIGN alignas(16)
#ifdef __SSE4_1__
#define PULSARION_MATH_SIMD xsimd::sse4_1
#elif defined(__SSE3__)
#define PULSARION_MATH_SIMD xsimd::sse3
#elif defined(__SSE2__)
#define PULSARION_MATH_SIMD xsimd::sse2
#else
#error "SSE is not supported!"
#endif
#elif defined(__AVX__)
#define PULSARION_MATH_ALIGN alignas(32)
#define PULSARION_MATH_SIMD xsimd::avx
#endif
#else
#define PULSARION_MATH_NO_SIMD
#define PULSARION_MATH_ALIGN
#endif

namespace Pulsarion::Math
{
    // Normal precision float
    using float_normalp = float;

    // High precision float
    using float_highp = double;

    // Extended precision float
    using float_extp = long double;

    template<typename T>
    concept float_type = std::same_as<T, float_normalp> || std::same_as<T, float_highp> || std::same_as<T, float_extp>;

    template<typename T>
    concept number_type = std::is_arithmetic_v<T>;

    // Fast inverse square root, from Quake III Arena
    inline float FastInverseSqrt(float number) {
        constexpr float threehalfs = 1.5F;

        float x2 = number * 0.5F;
        float y  = number;

        int32_t i  = *reinterpret_cast<int32_t *>(&y);
        i  = 0x5f3759df - (i >> 1);
        y  = *reinterpret_cast<float *>(&i);

        y  = y * (threehalfs - (x2 * y * y));
        y  = y * (threehalfs - (x2 * y * y));

        return y;
    }


}
