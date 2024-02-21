#pragma once

#include <PulsarionCore/Core.hpp>
#include <concepts>

#ifdef PULSARION_BUILD_SHARED_LIB
#ifdef PULSARION_BUILD_DLL
#define PULSARION_MATH_API PULSARION_DLL_EXPORT
#else
#define PULSARION_MATH_API PULSARION_DLL_IMPORT
#endif
#else
#define PULSARION_MATH_API
#endif

namespace Pulsarion::Math
{
    template<typename T>
    concept Arithmetic_t = std::is_arithmetic_v<T>;

    template<typename T>
    concept Integral_t = std::is_integral_v<T>;

    template<typename T>
    concept FloatingPoint_t = std::is_floating_point_v<T>;
}

