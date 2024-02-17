#pragma once

#include "Core.hpp"
#include "Simd.hpp"

#include <array>
#include <ostream>
#include <sstream>

namespace Pulsarion::Math
{
    template<float_type T, size_t N>
    class Vector;

    // Vector with 2 components
    template<float_type T>
    class Vector<T, 2>
    {
    public:
        explicit Vector(T x = 0, T y = 0) : x(x), y(y) {}
        Vector(const Vector& other) noexcept = default;
        Vector(Vector&& other) noexcept = default;
        Vector& operator=(const Vector& other) noexcept = default;
        Vector& operator=(Vector&& other) noexcept = default;
        ~Vector() noexcept = default;

        template<number_type R>
        Vector operator+(R scalar) const noexcept
        {
            const T scalarT = static_cast<T>(scalar);
            return Vector(x + scalarT, y + scalarT);
        }
        template<number_type R>
        Vector operator-(R scalar) const noexcept
        {
            const T scalarT = static_cast<T>(scalar);
            return Vector(x - scalarT, y - scalarT);
        }
        template<number_type R>
        Vector operator*(R scalar) const noexcept
        {
            const T scalarT = static_cast<T>(scalar);
            return Vector(x * scalarT, y * scalarT);
        }
        template<number_type R>
        Vector operator/(R scalar) const noexcept
        {
            const T scalarT = static_cast<T>(scalar);
            if (scalarT == 0)
                return Vector(0, 0); // Avoid division by zero
            return Vector(x / scalarT, y / scalarT);
        }

        Vector operator*(const Vector& other) const noexcept { return Vector(x * other.x, y * other.y); }
        Vector operator/(const Vector& other) const noexcept
        {
            if (other.x == 0 || other.y == 0)
                return Vector(0, 0); // Avoid division by zero
            return Vector(x / other.x, y / other.y);
        }
        [[nodiscard]] T Dot(const Vector& other) const noexcept { return x * other.x + y * other.y; }

        Vector operator+(const Vector& other) const noexcept { return Vector(x + other.x, y + other.y); }
        Vector operator-(const Vector& other) const noexcept { return Vector(x - other.x, y - other.y); }

        [[nodiscard]] float Cross(const Vector& other) const noexcept { return x * other.y - y * other.x; }
        [[nodiscard]] T Magnitude() const noexcept { return Sqrt(MagnitudeSquared()); }
        [[nodiscard]] T MagnitudeSquared() const noexcept { return x * x + y * y; }
        [[nodiscard]] T InverseMagnitudeLow() const noexcept { return FastInverseSqrt(MagnitudeSquared()); }
        [[nodiscard]] Vector Normalized() const noexcept
        {
            const T mag =  Magnitude();
            if (mag == 0)
                return Vector(0, 0); // Avoid division by zero
            return *this / mag;
        }
        Vector& Normalize() noexcept
        {
            const T magnitude = Magnitude();
            if (magnitude == 0)
                return *this; // Avoid division by zero
            x /= magnitude;
            y /= magnitude;
            return *this;
        }

        T operator[](size_t index) const noexcept
        {
            // std::array check bounds automatically in debug mode
            return data[index];
        }

        [[nodiscard]] std::string ToString() const
        {
            std::stringstream ss;
            ss << "Vector2(" << data[0] << ", " << data[1] << ")";
            return ss.str();
        }


        Vector operator+=(const Vector& other) noexcept
        {
            *this = *this + other;
            return *this;
        }
        Vector operator-=(const Vector& other) noexcept
        {
			*this = *this - other;
			return *this;
        }
        Vector operator*=(const Vector& other) noexcept
        {
			*this = *this * other;
			return *this;
        }
        Vector operator/=(const Vector& other) noexcept
        {
            *this = *this / other;
            return *this;
        }

        bool operator==(const Vector& other) const noexcept
		{
			return x == other.x && y == other.y;
		}

        union PULSARION_MATH_ALIGN
        {
            struct { T x, y; };
            std::array<T, 2> data;
        };
    };

    // Vector with 3 components
    template<float_type T>
    class Vector<T, 3>
    {
    public:
        explicit Vector(T x = 0, T y = 0, T z = 0) : x(x), y(y), z(z) {}
        explicit Vector(const Vector<T, 2>& other) noexcept : x(other.x), y(other.y), z(0) {}
        Vector(const Vector& other) noexcept = default;
        Vector(Vector&& other) noexcept = default;
        Vector& operator=(const Vector& other) noexcept = default;
        Vector& operator=(Vector&& other) noexcept = default;
        ~Vector() noexcept = default;

        template<number_type R>
        Vector operator+(R scalar) const noexcept
        {
            const T scalarT = static_cast<T>(scalar);
            return Vector(x + scalarT, y + scalarT, z + scalarT);
        }

        template<number_type R>
        Vector operator-(R scalar) const noexcept
        {
            const T scalarT = static_cast<T>(scalar);
            return Vector(x - scalarT, y - scalarT, z - scalarT);
        }

        template<number_type R>
        Vector operator*(R scalar) const noexcept
        {
            const T scalarT = static_cast<T>(scalar);
            return Vector(x * scalarT, y * scalarT, z * scalarT);
        }

        template<number_type R>
        Vector operator/(R scalar) const noexcept
        {
            const T scalarT = static_cast<T>(scalar);
            if (scalarT == 0)
                return Vector(0, 0, 0); // Avoid division by zero
            return Vector(x / scalarT, y / scalarT, z / scalarT);
        }

        Vector operator+(const Vector& other) const noexcept { return Vector(x + other.x, y + other.y, z + other.z); }
        Vector operator-(const Vector& other) const noexcept { return Vector(x - other.x, y - other.y, z - other.z); }
        Vector operator*(const Vector& other) const noexcept { return Vector(x * other.x, y * other.y, z * other.z); }
        Vector operator/(const Vector& other) const noexcept { return Vector(x / other.x, y / other.y, z / other.z); }
        [[nodiscard]] Vector Cross(const Vector& other) const noexcept
        {
            return Vector(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
        }
        [[nodiscard]] T Dot(const Vector& other) const noexcept
        {
            return x * other.x + y * other.y + z * other.z;
        }
        [[nodiscard]] T Magnitude() const noexcept { return Sqrt(MagnitudeSquared()); }
        [[nodiscard]] T MagnitudeSquared() const noexcept { return x * x + y * y + z * z; }
        [[nodiscard]] T InverseMagnitudeLowP() const noexcept { return FastInverseSqrt(MagnitudeSquared()); }
        [[nodiscard]] Vector Normalized() const noexcept
        {
            const T mag = Magnitude();
            if (mag == 0)
                return Vector(0, 0, 0); // Avoid division by zero
            return *this / mag;
        }
        Vector& Normalize() noexcept
        {
            const T magnitude = Magnitude();
            if (magnitude == 0)
                return *this; // Avoid division by zero
            x /= magnitude;
            y /= magnitude;
            z /= magnitude;
            return *this;
        }

        T operator[](size_t index) const noexcept
        {
            return data[index];
        }

        [[nodiscard]] std::string ToString() const
        {
            std::stringstream ss;
            ss << "Vector3(";
            for (size_t i = 0; i < 3; i++)
            {
                ss << data[i];
                if (i != 2)
                {
                    ss << ", ";
                }
            }
            ss << ")";
            return ss.str();
        }

        Vector operator+=(const Vector& other) noexcept
        {
            *this = *this + other;
            return *this;
        }
        Vector operator-=(const Vector& other) noexcept
        {
            *this = *this - other;
            return *this;
        }
        Vector operator*=(const Vector& other) noexcept
        {
            *this = *this * other;
            return *this;
        }
        Vector operator/=(const Vector& other) noexcept
        {
            *this = *this / other;
            return *this;
        }

        bool operator==(const Vector& other) const noexcept
		{
			return x == other.x && y == other.y && z == other.z;
		}

        union PULSARION_MATH_ALIGN
        {
            struct { T x, y, z; };
            std::array<T, 3> data;
        };
    };

    // By default, w is set to 1
    template<float_type T>
    class Vector<T, 4>
    {
    public:
        explicit Vector(T x = 0, T y = 0, T z = 0, T w = 1) : x(x), y(y), z(z), w(w) {}
        explicit Vector(const Vector<T, 2>& other) noexcept : x(other.x), y(other.y), z(0), w(1) {}
        explicit Vector(const Vector<T, 3>& other) noexcept : x(other.x), y(other.y), z(other.z), w(1) {}
        Vector(const Vector& other) noexcept = default;
        Vector(Vector&& other) noexcept = default;
        Vector& operator=(const Vector& other) noexcept = default;
        Vector& operator=(Vector&& other) noexcept = default;
        ~Vector() noexcept = default;

        template<number_type R>
        Vector operator+(R scalar) const noexcept
        {
            const T scalarT = static_cast<T>(scalar);
            return Vector(x + scalarT, y + scalarT, z + scalarT, w + scalarT);
        }

        template<number_type R>
        Vector operator-(R scalar) const noexcept
        {
            const T scalarT = static_cast<T>(scalar);
            return Vector(x - scalarT, y - scalarT, z - scalarT, w - scalarT);
        }

        template<number_type R>
        Vector operator*(R scalar) const noexcept
        {
            const T scalarT = static_cast<T>(scalar);
            return Vector(x * scalarT, y * scalarT, z * scalarT, w * scalarT);
        }

        template<number_type R>
        Vector operator/(R scalar) const noexcept
        {
            const T scalarT = static_cast<T>(scalar);
            if (scalarT == 0)
                return Vector(0, 0, 0, 0); // Avoid division by zero
            return Vector(x / scalarT, y / scalarT, z / scalarT, w / scalarT);
        }

        Vector operator+(const Vector& other) const noexcept { return Vector(x + other.x, y + other.y, z + other.z, w + other.w); }
        Vector operator-(const Vector& other) const noexcept { return Vector(x - other.x, y - other.y, z - other.z, w - other.w); }
        Vector operator*(const Vector& other) const noexcept { return Vector(x * other.x, y * other.y, z * other.z, w * other.w); }
        Vector operator/(const Vector& other) const noexcept { return Vector(x / other.x, y / other.y, z / other.z, w / other.w); }
        [[nodiscard]] T Dot(const Vector& other) const noexcept { return x * other.x + y * other.y + z * other.z + w * other.w; }
        [[nodiscard]] Vector Cross3D(const Vector& other) const noexcept
        {
            return Vector(
                y * other.z - z * other.y,  // x component
                z * other.x - x * other.z,  // y component
                x * other.y - y * other.x,  // z component
                0                       // w component
            );
        }

        [[nodiscard]] T Magnitude() const noexcept { return Sqrt(MagnitudeSquared()); }
        [[nodiscard]] T MagnitudeSquared() const noexcept { return x * x + y * y + z * z + w * w; }
        [[nodiscard]] T InverseMagnitudeLowP() const noexcept { return FastInverseSqrt(MagnitudeSquared()); }
        [[nodiscard]] Vector Normalized() const noexcept
        {
            const T mag = Magnitude();
            if (mag == 0)
                return Vector(0, 0, 0, 0); // Avoid division by zero
            return *this / mag;
        }
        Vector& Normalize() noexcept
        {
            const T magnitude = Magnitude();
            if (magnitude == 0)
                return *this; // Avoid division by zero
            x /= magnitude;
            y /= magnitude;
            z /= magnitude;
            w /= magnitude;
            return *this;
        }
        // Normalize 3D
        Vector& Normalize3D() noexcept
        {
            const T magnitude = Sqrt(x * x + y * y + z * z);
            if (magnitude == 0)
                return *this; // Avoid division by zero
            x /= magnitude;
            y /= magnitude;
            z /= magnitude;
            return *this;
        }

        const T& operator[](size_t index) const noexcept
        {
            return data[index];
        }

        T& operator[](size_t index) noexcept
        {
            return data[index];
        }

        [[nodiscard]] std::string ToString() const
        {
            std::stringstream ss;
            ss << "Vector4(";
            for (size_t i = 0; i < 4; i++)
            {
                ss << data[i];
                if (i != 3)
                {
                    ss << ", ";
                }
            }
            ss << ")";
            return ss.str();
        }

        Vector operator+=(const Vector& other) noexcept
        {
            *this = *this + other;
            return *this;
        }
        Vector operator-=(const Vector& other) noexcept
        {
            *this = *this - other;
            return *this;
        }
        Vector operator*=(const Vector& other) noexcept
        {
            *this = *this * other;
            return *this;
        }
        Vector operator/=(const Vector& other) noexcept
        {
            *this = *this / other;
            return *this;
        }

        bool operator==(const Vector& other) const noexcept
        {
            return x == other.x && y == other.y && z == other.z && w == other.w;
        }

        union
        {
            struct { T x, y, z, w; };
            std::array<T, 4> data;
        };
    };

    // Explicit instantiations
    template class Vector<float_normalp, 2>;
    template class Vector<float_highp, 2>;
    template class Vector<float_extp, 2>;
    template class Vector<float_normalp, 3>;
    template class Vector<float_highp, 3>;
    template class Vector<float_extp, 3>;
    template class Vector<float_normalp, 4>;
    template class Vector<float_highp, 4>;
    template class Vector<float_extp, 4>;
}
