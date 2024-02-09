#pragma once

#include "Core.hpp"

#include <numbers>

namespace Pulsarion::Math
{
    template<float_type T>
    struct Constants;

    template<>
    struct Constants<float_normalp>
    {
        static constexpr float Pi = std::numbers::pi_v<float>;
		static constexpr float E = std::numbers::e_v<float>;
    };

    template<>
	struct Constants<float_highp>
	{
		static constexpr double Pi = std::numbers::pi_v<double>;
        static constexpr double E = std::numbers::e_v<double>;
    };

    template<>
	struct Constants<float_extp>
    {
		static constexpr long double Pi = std::numbers::pi_v<long double>;
		static constexpr long double E = std::numbers::e_v<long double>;
    };
}
