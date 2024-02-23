#pragma once

#include "Qualifier.hpp"
#include "DataStorage.hpp"
#include "VectorCommon.hpp"

namespace Pulsarion::Math
{
    template<std::size_t N, Arithmetic_t T, Qualifier Q>
    requires (N >= 2 && N <= 4)
    class Vector
    {
    public:
        DataStorage<N, T, Q> data;

        // ---- Constructors ----
        inline constexpr Vector(T x, T y, T z, T w) noexcept
        requires (N == 4) : data{ x, y, z, w } {}
        inline constexpr Vector(T x, T y, T z) noexcept
        requires (N == 3) : data{ x, y, z } {}
        inline constexpr Vector(T x, T y) noexcept
        requires (N == 2) : data{ x, y } {}
        explicit inline constexpr Vector(T value) noexcept {
            data.data[0] = value;
            data.data[1] = value;
            if constexpr (N >= 3) data.data[2] = value;
            if constexpr (N == 4) data.data[3] = value;
        }
        inline constexpr Vector() noexcept : Vector(0) {}

        inline constexpr Vector(const Vector&) noexcept = default;
        inline constexpr Vector(Vector&&) noexcept = default;
        inline constexpr Vector& operator=(const Vector&) noexcept = default;
        inline constexpr Vector& operator=(Vector&&) noexcept = default;

        // ---- Accessors ----
        inline constexpr T& operator[](std::size_t index) noexcept { return data.data[index]; }
        inline constexpr const T& operator[](std::size_t index) const noexcept { return data.data[index]; }
        inline constexpr T& x() noexcept { return data.data[0]; }
        [[nodiscard]] inline constexpr const T& x() const noexcept { return data.data[0]; }
        [[nodiscard]] inline constexpr T& y() noexcept { return data.data[1]; }
        [[nodiscard]] inline constexpr const T& y() const noexcept { return data.data[1]; }
        [[nodiscard]] inline constexpr T& z() noexcept
        requires (N >= 3) { return data.data[2]; }
        [[nodiscard]] inline constexpr const T& z() const noexcept
        requires (N >= 3) { return data.data[2]; }
        [[nodiscard]] inline constexpr T& w() noexcept
        requires (N == 4) { return data.data[3]; }
        [[nodiscard]] inline constexpr const T& w() const noexcept
        requires (N == 4) { return data.data[3]; }

        // ---- Unary arithmetic operators ----
        inline constexpr Vector operator+() const noexcept { return *this; }
        inline constexpr Vector operator-() const noexcept { return VectorFunctions<N, T, Q>::negate(*this); }

        // ---- Binary arithmetic operators ----
        inline constexpr Vector operator+(const Vector& other) const noexcept { return VectorFunctions<N, T, Q>::add(*this, other); }
        inline constexpr Vector operator-(const Vector& other) const noexcept { return VectorFunctions<N, T, Q>::subtract(*this, other); }
        inline constexpr Vector operator*(const Vector& other) const noexcept { return VectorFunctions<N, T, Q>::multiply(*this, other); }
        inline constexpr Vector operator/(const Vector& other) const noexcept { return VectorFunctions<N, T, Q>::divide(*this, other); }
        inline constexpr Vector operator*(T scalar) const noexcept { return VectorFunctions<N, T, Q>::multiplyScale(*this, scalar); }
        inline constexpr Vector operator/(T scalar) const noexcept { return VectorFunctions<N, T, Q>::divideScale(*this, scalar); }

        // ---- Compound assignment operators ----
        inline constexpr Vector& operator+=(const Vector& other) noexcept { return *this = *this + other; }
        inline constexpr Vector& operator-=(const Vector& other) noexcept { return *this = *this - other; }
        inline constexpr Vector& operator*=(const Vector& other) noexcept { return *this = *this * other; }
        inline constexpr Vector& operator/=(const Vector& other) noexcept { return *this = *this / other; }
        inline constexpr Vector& operator*=(T scalar) noexcept { return *this = *this * scalar; }
        inline constexpr Vector& operator/=(T scalar) noexcept { return *this = *this / scalar; }

        // ---- Comparison operators ----
        inline constexpr bool operator==(const Vector& other) const noexcept { return VectorFunctions<N, T, Q>::equal(*this, other); }
        inline constexpr bool operator!=(const Vector& other) const noexcept { return VectorFunctions<N, T, Q>::notEqual(*this, other); }

        // ---- Special Math functions ----
        [[nodiscard]] inline constexpr T Dot(const Vector& other) const noexcept { return VectorFunctions<N, T, Q>::dot(*this, other); }
        [[nodiscard]] inline constexpr Vector<3, T, Q> Cross(const Vector<3, T, Q>& other)
        requires (N == 3) { return VectorFunctions<N, T, Q>::cross(*this, other); }
        [[nodiscard]] inline constexpr T LengthSquared() const noexcept { return VectorFunctions<N, T, Q>::lengthSquared(*this); }

    };

    // Operators for scalar on the left side
    template<std::size_t N, Arithmetic_t T, Qualifier Q>
    inline constexpr Vector<N, T, Q> operator*(T scalar, const Vector<N, T, Q>& vector) noexcept
    {
        return vector * scalar;
    }

    template<std::size_t N, Arithmetic_t T, Qualifier Q>
    inline constexpr Vector<N, T, Q> operator/(T scalar, const Vector<N, T, Q>& vector) noexcept
    {
        return VectorFunctions<N, T, Q>::divideScale(vector, scalar);
    }

    template<>
    struct VectorFunctions<4, float, Qualifier::Packed>
    {
        static inline constexpr Vector<4, float, Qualifier::Packed> negate(const Vector<4, float, Qualifier::Packed>& vector) noexcept
        {
            return Vector<4, float, Qualifier::Packed>{ -vector.x(), -vector.y(), -vector.z(), -vector.w() };
        }


        static inline constexpr Vector<4, float, Qualifier::Packed> add(const Vector<4, float, Qualifier::Packed>& left, const Vector<4, float, Qualifier::Packed>& right) noexcept
        {
            return Vector<4, float, Qualifier::Packed>{ left.x() + right.x(), left.y() + right.y(), left.z() + right.z(), left.w() + right.w() };
        }

        static inline constexpr Vector<4, float, Qualifier::Packed> subtract(const Vector<4, float, Qualifier::Packed>& left, const Vector<4, float, Qualifier::Packed>& right) noexcept
        {
            return Vector<4, float, Qualifier::Packed>{ left.x() - right.x(), left.y() - right.y(), left.z() - right.z(), left.w() - right.w() };
        }

        static inline constexpr Vector<4, float, Qualifier::Packed> multiply(const Vector<4, float, Qualifier::Packed>& left, const Vector<4, float, Qualifier::Packed>& right) noexcept
        {
            return Vector<4, float, Qualifier::Packed>{ left.x() * right.x(), left.y() * right.y(), left.z() * right.z(), left.w() * right.w() };
        }

        static inline constexpr Vector<4, float, Qualifier::Packed> divide(const Vector<4, float, Qualifier::Packed>& left, const Vector<4, float, Qualifier::Packed>& right) noexcept
        {
            return Vector<4, float, Qualifier::Packed>{ left.x() / right.x(), left.y() / right.y(), left.z() / right.z(), left.w() / right.w() };
        }

        static inline constexpr Vector<4, float, Qualifier::Packed> multiplyScale(const Vector<4, float, Qualifier::Packed>& vector, float scalar) noexcept
        {
            return Vector<4, float, Qualifier::Packed>{ vector.x() * scalar, vector.y() * scalar, vector.z() * scalar, vector.w() * scalar };
        }

        static inline constexpr Vector<4, float, Qualifier::Packed> divideScale(const Vector<4, float, Qualifier::Packed>& vector, float scalar) noexcept
        {
            return Vector<4, float, Qualifier::Packed>{ vector.x() / scalar, vector.y() / scalar, vector.z() / scalar, vector.w() / scalar };
        }

        static inline constexpr bool equal(const Vector<4, float, Qualifier::Packed>& left, const Vector<4, float, Qualifier::Packed>& right) noexcept
        {
            return left.x() == right.x() && left.y() == right.y() && left.z() == right.z() && left.w() == right.w();
        }

        static inline constexpr bool notEqual(const Vector<4, float, Qualifier::Packed>& left, const Vector<4, float, Qualifier::Packed>& right) noexcept
        {
            return left.x() != right.x() || left.y() != right.y() || left.z() != right.z() || left.w() != right.w();
        }

        static inline constexpr float dot(const Vector<4, float, Qualifier::Packed>& left, const Vector<4, float, Qualifier::Packed>& right) noexcept
        {
            return left.x() * right.x() + left.y() * right.y() + left.z() * right.z() + left.w() * right.w();
        }

        static inline constexpr float lengthSquared(const Vector<4, float, Qualifier::Packed>& vector) noexcept
        {
            return vector.x() * vector.x() + vector.y() * vector.y() + vector.z() * vector.z() + vector.w() * vector.w();
        }
    };
}
