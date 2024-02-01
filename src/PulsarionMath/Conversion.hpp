#pragma once

#include "Constants.hpp"
#include "Core.hpp"

namespace Pulsarion::Math
{
    template<float_type T>
    T DegreesToRadians(T degrees)
    {
        static constexpr T pi_over_180 = Constants<T>::Pi /180;
        return degrees * pi_over_180;
    }

    template<float_type T>
    T RadiansToDegrees(T radians)
    {
        static constexpr T one_eighty_over_pi = 180 / Constants<T>::Pi;
        return radians * one_eighty_over_pi;
    }

    template<float_type T>
    T RadiansToTurns(T radians)
    {
        static constexpr T one_over_two_pi = 1 / (2 * Constants<T>::Pi);
        return radians * one_over_two_pi;
    }

    template<float_type T>
    T TurnsToRadians(T turns)
    {
        static constexpr T two_pi = 2 * Constants<T>::Pi;
        return turns * two_pi;
    }
    
}
