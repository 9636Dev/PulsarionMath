#pragma once

#include "Core.hpp"
#include "Matrix.hpp"

namespace Pulsarion::Math
{
    template<float_type T>
    class Quaternion
    {
    public:
        Quaternion(T w = 1, T i = 0, T j = 0, T k = 0) noexcept : w(w), i(i), j(j), k(k) {}; // Identity
        Quaternion(const Quaternion& other) noexcept : w(other.w), i(other.i), j(other.j), k(other.k) {};
        Quaternion(Quaternion&& other) noexcept : w(std::move(other.w)), i(std::move(other.i)), j(std::move(other.j)), k(std::move(other.k)) {};
        ~Quaternion() noexcept = default;

        Quaternion& operator=(const Quaternion& other) noexcept
        {
            w = other.w;
            i = other.i;
            j = other.j;
            k = other.k;
            return *this;
        }

        Quaternion& operator=(Quaternion&& other) noexcept
        {
            w = std::move(other.w);
            i = std::move(other.i);
            j = std::move(other.j);
            k = std::move(other.k);
            return *this;
        }

        void Identity() noexcept
        {
            w = 1;
            i = 0;
            j = 0;
            k = 0;
        }

        Quaternion operator*(T scalar) const noexcept
        {
            return Quaternion(w * scalar, i * scalar, j * scalar, k * scalar);
        }

        union
        {
            struct PULSARION_MATH_ALIGN
            {
                T i, j, k, w; // Aligns with Vector<T, 4>, where w is the real part
            };
            Vector<T, 4> vector;
            std::array<T, 4> data;
        };
    };
}


