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

        Quaternion operator/(T scalar) const noexcept
		{
			return Quaternion(w / scalar, i / scalar, j / scalar, k / scalar);
		}

        Quaternion operator+(T scalar) const noexcept
        {
            return Quaternion(w + scalar, i, j, k);
        }

        Quaternion operator-(T scalar) const noexcept
        {
			return Quaternion(w - scalar, i, j, k);
        }

        // Quaternion operators
        Quaternion operator+(const Quaternion& other) const noexcept
		{
			return Quaternion(w + other.w, i + other.i, j + other.j, k + other.k);
		}
        
        Quaternion operator-(const Quaternion& other) const noexcept
        {
            return Quaternion(w - other.w, i - other.i, j - other.j, k - other.k);
        }

        Quaternion operator*(const Quaternion& other) const noexcept
		{
			return Quaternion(
				w * other.w - i * other.i - j * other.j - k * other.k,
				w * other.i + i * other.w + j * other.k - k * other.j,
				w * other.j - i * other.k + j * other.w + k * other.i,
				w * other.k + i * other.j - j * other.i + k * other.w
			);
		}

        Quaternion operator/(const Quaternion& other) const noexcept
		{
            return *this * other.Inverse();
        }

        T Norm() const noexcept
		{
			return std::sqrt(w * w + i * i + j * j + k * k);
		}

        Quaternion Conjugate() const noexcept
		{
            return Quaternion(w, -i, -j, -k);
		}

        Quaternion Inverse() const noexcept
		{
            return Conjugate() / Norm();
        }

        Quaternion Normalized() const noexcept
        {
			T norm = Norm();
			return Quaternion(w / norm, i / norm, j / norm, k / norm);
        }

        Quaternion& Normalize() noexcept
		{
            T norm = Norm();
			w /= norm;
            i /= norm;
			j /= norm;
            k /= norm;
			return *this;
        }

        Quaternion& operator+=(const Quaternion& other) noexcept
		{
            w += other.w;
            i += other.i;
            j += other.j;
            k += other.k;
            return *this;
		}

        Quaternion& operator-=(const Quaternion& other) noexcept
        {
            w -= other.w;
            i -= other.i;
            j -= other.j;
            k -= other.k;
            return *this;
        }

        Quaternion& operator*=(const Quaternion& other) noexcept
        {
            *this = *this * other;
			return *this;
        }

        Quaternion& operator/=(const Quaternion& other) noexcept
		{
			*this = *this / other;
			return *this;
        }

        union
        {
            struct PULSARION_MATH_ALIGN
            {
                T i, j, k, w; // Aligns with Vector<T, 4>, where w is the real part
            };
            Vector<T, 4> vector; // Can be interpreted as a 4D vector where w is the real part
            std::array<T, 4> data;
        };
    };
}


