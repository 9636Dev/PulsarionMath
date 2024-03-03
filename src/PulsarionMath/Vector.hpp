#pragma once
#define PULSARION_MATH_VECTOR_HPP // This is so we can include the inl file correctly

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
        inline Vector operator*(const Vector& other) const noexcept { return VectorFunctions<N, T, Q>::multiply(*this, other); }
        inline Vector operator/(const Vector& other) const noexcept { return VectorFunctions<N, T, Q>::divide(*this, other); }
        inline Vector operator*(T scalar) const noexcept { return VectorFunctions<N, T, Q>::multiplyScale(*this, scalar); }
        inline Vector operator/(T scalar) const noexcept { return VectorFunctions<N, T, Q>::divideScale(*this, scalar); }

        // ---- Compound assignment operators ----
        inline constexpr Vector& operator+=(const Vector& other) noexcept { return *this = *this + other; }
        inline constexpr Vector& operator-=(const Vector& other) noexcept { return *this = *this - other; }
        inline Vector& operator*=(const Vector& other) noexcept { return *this = *this * other; }
        inline Vector& operator/=(const Vector& other) noexcept { return *this = *this / other; }
        inline Vector& operator*=(T scalar) noexcept { return *this = *this * scalar; }
        inline Vector& operator/=(T scalar) noexcept { return *this = *this / scalar; }

        // ---- Comparison operators ----
        inline constexpr bool operator==(const Vector& other) const noexcept { return VectorFunctions<N, T, Q>::equal(*this, other); }
        inline constexpr bool operator!=(const Vector& other) const noexcept { return VectorFunctions<N, T, Q>::notEqual(*this, other); }

        // ---- Special Math functions ----
        [[nodiscard]] inline T Dot(const Vector& other) const noexcept { return VectorFunctions<N, T, Q>::dot(*this, other); }
        [[nodiscard]] inline constexpr Vector<3, T, Q> Cross(const Vector<3, T, Q>& other)
        requires (N == 3) { return VectorFunctions<N, T, Q>::cross(*this, other); }
        [[nodiscard]] inline T LengthSquared() const noexcept { return VectorFunctions<N, T, Q>::lengthSquared(*this); }

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
}

#ifdef PULSARION_MATH_SIMD_SSE4_1
#include "Vector4PackedSSE.hpp"
#include "Vector4AlignedSSE.hpp"
#elif defined(PULSARION_MATH_SIMD_AVX)
#error "AVX is not yet supported"
#else
#include "Vector4Packed.hpp"
#include "Vector4Aligned.hpp"
#endif
