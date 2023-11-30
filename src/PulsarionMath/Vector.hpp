#pragma once

#include "Core.hpp"

#include <ostream>

#include "PulsarionCore/Assert.hpp"

namespace Pulsarion::Math
{
    template<float_type T, size_t N>
    requires (N > 0 && N <= 4)
    class Vector;

    // Vector with 2 components
    template<float_type T>
    class Vector<T, 2>
    {
    public:
        Vector(T x = 0, T y = 0) : x(x), y(y) {}
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

        Vector operator+(const Vector& other) const noexcept { return Vector(x + other.x, y + other.y); }
        Vector operator-(const Vector& other) const noexcept { return Vector(x - other.x, y - other.y); }
        Vector operator*(const Vector& other) const noexcept { return Vector(x * other.x, y * other.y); }
        Vector operator/(const Vector& other) const noexcept
        {
            if (other.x == 0 || other.y == 0)
                return Vector(0, 0); // Avoid division by zero
            return Vector(x / other.x, y / other.y);
        }
        [[nodiscard]] Vector Cross(const Vector& other) const noexcept { return Vector(x * other.y, y * other.x); }
        [[nodiscard]] T Dot(const Vector& other) const noexcept { return x * other.x + y * other.y; }
        [[nodiscard]] T Magnitude() const noexcept { return std::sqrt(MagnitudeSquared()); }
        [[nodiscard]] T MagnitudeSquared() const noexcept { return x * x + y * y; }
        [[nodiscard]] T InverseMagnitude() const noexcept { return 1 / Magnitude(); }
        [[nodiscard]] T InverseMagnitudeLowPrecision() const noexcept { return FastInverseSqrt(MagnitudeSquared()); }
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
            PULSARION_ASSERT(index < 2, "Index out of bounds");
            return data[index];
        }

        union
        {
            struct { T x, y; };
            T data[2];
        };
    };

    // Vector with 3 components
    template<float_type T>
    class Vector<T, 3>
    {
    public:
        Vector(T x = 0, T y = 0, T z = 0) : x(x), y(y), z(z) {}
        Vector(const Vector<T, 2>& other) noexcept : x(other.x), y(other.y), z(0) {}
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
        [[nodiscard]] Vector Cross(const Vector& other) const noexcept { return Vector(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x); }
        [[nodiscard]] T Dot(const Vector& other) const noexcept { return x * other.x + y * other.y + z * other.z; }
        [[nodiscard]] T Magnitude() const noexcept { return std::sqrt(MagnitudeSquared()); }
        [[nodiscard]] T MagnitudeSquared() const noexcept { return x * x + y * y + z * z; }
        [[nodiscard]] T InverseMagnitude() const noexcept { return 1 / Magnitude(); }
        [[nodiscard]] T InverseMagnitudeLowPrecision() const noexcept { return FastInverseSqrt(MagnitudeSquared()); }
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
            PULSARION_ASSERT(index < 3, "Index out of bounds");
            return data[index];
        }

        union
        {
            struct { T x, y, z; };
            T data[3];
        };
    };

    // Vector with 4 components
    template<float_type T>
    class Vector<T, 4>
    {
    public:
        Vector(T x = 0, T y = 0, T z = 0, T w = 0) : x(x), y(y), z(z), w(w) {}
        Vector(const Vector<T, 2>& other) noexcept : x(other.x), y(other.y), z(0), w(0) {}
        Vector(const Vector<T, 3>& other) noexcept : x(other.x), y(other.y), z(other.z), w(0) {}
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
        [[nodiscard]] Vector Cross(const Vector& other) const noexcept
        {
            return Vector(
                y * other.z - z * other.y,  // x component
                z * other.x - x * other.z,  // y component
                x * other.y - y * other.x,  // z component
                0                       // w component
            );
        }
        [[nodiscard]] T Dot(const Vector& other) const noexcept { return x * other.x + y * other.y + z * other.z + w * other.w; }
        [[nodiscard]] T Magnitude() const noexcept { return std::sqrt(MagnitudeSquared()); }
        [[nodiscard]] T MagnitudeSquared() const noexcept { return x * x + y * y + z * z + w * w; }
        [[nodiscard]] T InverseMagnitude() const noexcept { return 1 / Magnitude(); }
        [[nodiscard]] T InverseMagnitudeLowPrecision() const noexcept { return FastInverseSqrt(MagnitudeSquared()); }
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
            const T magnitude = std::sqrt(x * x + y * y + z * z);
            if (magnitude == 0)
                return *this; // Avoid division by zero
            x /= magnitude;
            y /= magnitude;
            z /= magnitude;
            return *this;
        }

        const T& operator[](size_t index) const noexcept
        {
            PULSARION_ASSERT(index < 4, "Index out of bounds");
            return data[index];
        }

        T& operator[](size_t index) noexcept
        {
            PULSARION_ASSERT(index < 4, "Index out of bounds");
            return data[index];
        }

        PULSARION_MATH_ALIGN union
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

    // To string methods
    template<float_type T, size_t Dimension>
    std::ostream& operator<<(std::ostream& os, const Vector<T, Dimension>& vector)
    {
        os << "(";
        for (size_t i = 0; i < Dimension; ++i)
        {
            os << vector.data[i];
            if (i != Dimension - 1)
                os << ", ";
        }
        os << ")";
        return os;
    }
}
