#pragma once

#include "Core.hpp"
#include "Matrix.hpp"

namespace Pulsarion::Math
{
    template<float_type T>
    class Quaternion
    {
    public:
        explicit Quaternion(T w = 1, T x = 0, T y = 0, T z = 0) noexcept : x(x), y(y), z(z), w(w) {}; // Identity
        Quaternion(const Quaternion& other) noexcept : w(other.w), x(other.x), y(other.y), z(other.z) {};
        Quaternion(Quaternion&& other) noexcept : w(std::move(other.w)), x(std::move(other.x)), y(std::move(other.y)), z(std::move(other.z)) {};
        ~Quaternion() noexcept = default;

        Quaternion& operator=(const Quaternion& other) noexcept
        {
            w = other.w;
            x = other.x;
            y = other.y;
            z = other.z;
            return *this;
        }

        Quaternion& operator=(Quaternion&& other) noexcept
        {
            w = std::move(other.w);
            x = std::move(other.x);
            y = std::move(other.y);
            z = std::move(other.z);
            return *this;
        }

        void Identity() noexcept
        {
            w = 1;
            x = 0;
            y = 0;
            z = 0;
        }

        Quaternion operator*(T scalar) const noexcept
        {
            return Quaternion(w * scalar, x * scalar, y * scalar, z * scalar);
        }

        Quaternion operator/(T scalar) const noexcept
		{
			return Quaternion(w / scalar, x / scalar, y / scalar, z / scalar);
		}

        Quaternion operator+(T scalar) const noexcept
        {
            return Quaternion(w + scalar, x, y, z);
        }

        Quaternion operator-(T scalar) const noexcept
        {
			return Quaternion(w - scalar, x, y, z);
        }

        // Quaternion operators
        Quaternion operator+(const Quaternion& other) const noexcept
		{
			return Quaternion(w + other.w, x + other.x, y + other.y, z + other.z);
		}
        
        Quaternion operator-(const Quaternion& other) const noexcept
        {
            return Quaternion(w - other.w, x - other.x, y - other.y, z - other.z);
        }

        Quaternion operator*(const Quaternion& other) const noexcept
		{
			return Quaternion(
				w * other.w - x * other.x - y * other.y - z * other.z,
				w * other.x + x * other.w + y * other.z - z * other.y,
				w * other.y - x * other.z + y * other.w + z * other.x,
				w * other.z + x * other.y - y * other.x + z * other.w
			);
		}

        Quaternion operator/(const Quaternion& other) const noexcept
		{
            return *this * other.Inverse();
        }

        T Norm() const noexcept
		{
			return std::sqrt(w * w + x * x + y * y + z * z);
		}

        Quaternion Conjugate() const noexcept
		{
            return Quaternion(w, -x, -y, -z);
		}

        Quaternion Inverse() const noexcept
		{
            return Conjugate() / Norm();
        }

        Quaternion Normalized() const noexcept
        {
			T norm = Norm();
			return Quaternion(w / norm, x / norm, y / norm, z / norm);
        }

        Quaternion& Normalize() noexcept
		{
            T norm = Norm();
			w /= norm;
            x /= norm;
			y /= norm;
            z /= norm;
			return *this;
        }

        Quaternion& operator+=(const Quaternion& other) noexcept
		{
            w += other.w;
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
		}

        Quaternion& operator-=(const Quaternion& other) noexcept
        {
            w -= other.w;
            x -= other.x;
            y -= other.y;
            z -= other.z;
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

        Matrix<T, 4, 4> ToMatrix() const noexcept
        {
            return Matrix<T, 4, 4>(
				1 - 2 * y * y - 2 * z * z, 2 * x * y - 2 * z * w, 2 * x * z + 2 * y * w, 0,
				2 * x * y + 2 * z * w, 1 - 2 * x * x - 2 * z * z, 2 * y * z - 2 * x * w, 0,
				2 * x * z - 2 * y * w, 2 * y * z + 2 * x * w, 1 - 2 * x * x - 2 * y * y, 0,
				0, 0, 0, 1
			);
		}

        union
        {
            struct PULSARION_MATH_ALIGN
            {
                T x, y, z, w; // Aligns with Vector<T, 4>, where w is the real part
            };
            Vector<T, 4> vector; // Can be interpreted as a 4D vector where w is the real part
            std::array<T, 4> data;
        };
    };
}


