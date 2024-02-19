#pragma once

#include "Core.hpp"
#include "Qualifier.hpp"
#include "DataStorage.hpp"

namespace Pulsarion::Math
{
    template<std::size_t N, Arithmetic_t T, Qualifier Q>
    struct VectorFunctions; // Access functions for the Vector class.

    template<>
    struct VectorFunctions<4, float, Qualifier::Packed>;


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
        explicit inline constexpr Vector(T value) noexcept : data{ value } {}
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
        inline constexpr Vector operator-() const noexcept { return VectorFunctions<N, T, Q>::negate(this); }

        // ---- Binary arithmetic operators ----
        inline constexpr Vector operator+(const Vector& other) const noexcept { return VectorFunctions<N, T, Q>::add(this, &other); }
        inline constexpr Vector operator-(const Vector& other) const noexcept { return VectorFunctions<N, T, Q>::subtract(this, &other); }
        inline constexpr Vector operator*(const Vector& other) const noexcept { return VectorFunctions<N, T, Q>::multiply(this, &other); }
        inline constexpr Vector operator/(const Vector& other) const noexcept { return VectorFunctions<N, T, Q>::divide(this, &other); }
        inline constexpr Vector operator*(T scalar) const noexcept { return VectorFunctions<N, T, Q>::multiply(this, scalar); }
        inline constexpr Vector operator/(T scalar) const noexcept { return VectorFunctions<N, T, Q>::divide(this, scalar); }
    };
}

#ifdef PULSARION_MATH_HEADER_ONLY
#include "Vector.inl"
#endif
