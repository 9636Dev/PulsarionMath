#include "Core.hpp"

namespace Pulsarion::Math
{
    template<float_type T>
    T Pi()
    {
        if constexpr (std::same_as<T, float>)
        {
            return 3.141592653589793F; // Most accurate float pi
        }
        else if constexpr (std::same_as<T, double>)
        {
            return 3.1415926535897932384626433832795028; // Most accurate double pi
        }
        else if constexpr (std::same_as<T, long double>)
        {
            if constexpr (sizeof(long double) == 16)
                return 3.14159265358979323846264338327950288419712L; // Most accurate long double pi for 128-bit
            return 3.1415926535897932384626433832795028L; // Most accurate long double pi for 80-bit
        }
    }

    template<float_type T>
    T NaturalConstant()
    {
        if constexpr (std::same_as<T, float>)
            return 2.718281828459045F; // Most accurate float e
        else if constexpr (std::same_as<T, double>)
            return 2.71828182845904523536028747135266231; // Most accurate double e
        else if constexpr (std::same_as<T, long double>)
        {
            if constexpr (sizeof(long double) == 16)
                return 2.71828182845904523536028747135266249775721L; // Most accurate long double e for 128-bit
            return 2.71828182845904523536028747135266231L; // Most accurate long double e for 80-bit
        }
    }
}
