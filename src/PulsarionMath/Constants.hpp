#pragma once

#include "Core.hpp"

namespace Pulsarion::Math
{
    template<float_type T>
    struct Constants;

    template<>
    struct Constants<float_normalp>
    {
        static constexpr float Pi = 3.141592653589793F; // Most accurate float pi
		static constexpr float E = 2.718281828459045F; // Most accurate float e
    };

    template<>
	struct Constants<float_highp>
	{
		static constexpr double Pi = 3.1415926535897932384626433832795028; // Most accurate double pi
        static constexpr double E = 2.71828182845904523536028747135266231; // Most accurate double e
	};

    template<>
	struct Constants<float_extp>
    {
		static constexpr long double Pi = 3.1415926535897932384626433832795028L; // Most accurate long double pi for 80-bit
		static constexpr long double E = 2.71828182845904523536028747135266231L; // Most accurate long double e for 80-bit, we ignore 128-bit, as 80 bit precision is enough
    };
}
