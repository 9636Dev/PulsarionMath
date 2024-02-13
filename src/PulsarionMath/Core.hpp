#pragma once

#include <cstdint>
#include <cmath>
#include <concepts>

namespace Pulsarion::Math
{
    using float_normalp = float; // Normal precision float
    using float_highp = double; // High precision float
    using float_extp = long double; // Extended precision float

    template<typename T>
    concept float_type = std::same_as<T, float_normalp> || std::same_as<T, float_highp> || std::same_as<T, float_extp>;

    template<typename T>
    concept number_type = std::is_arithmetic_v<T>;

    // Fast inverse square root, from Quake III Arena
    inline float FastInverseSqrt(float number) {
        constexpr float threehalfs = 1.5F;
        constexpr std::int32_t correctionTerm = 0x5f3759df;

        const float x2 = number * 0.5F;
        float y  = number;

        std::int32_t i  = *reinterpret_cast<std::int32_t*>(&y);
        i  = correctionTerm - (i >> 1);
        y  = *reinterpret_cast<float *>(&i);

        y  = y * (threehalfs - (x2 * y * y));
        y  = y * (threehalfs - (x2 * y * y));

        return y;
    }

    // Define trigonometric functions using the standard library, so in the future we can use our own implementation
    template<float_type T>
    inline T Sin(T angle)
    {
        return std::sin(angle);
    }

    template<float_type T>
    inline T Cos(T angle)
    {
		return std::cos(angle);
	}

    template<float_type T>
    inline T Tan(T angle)
    {
        return std::tan(angle);
    }

    template<float_type T>
    inline T Sqrt(T number)
    {
        if constexpr (std::same_as<T, float_normalp>)
			return std::sqrtf(number);

		if constexpr (std::same_as<T, float_highp>)
			return std::sqrt(number);

        if constexpr (std::same_as<T, float_extp>)
			return std::sqrtl(number);

        // If we reach this point, we have an invalid float type
        return 0;
    }
}
