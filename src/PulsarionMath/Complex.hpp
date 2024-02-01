#pragma once

#include "Core.hpp"

namespace Pulsarion::Math
{
    template<number_type T>
    class Complex
    {
    public:
        explicit Complex(T a = 0, T b = 0) noexcept : a(a), b(b) {};
        Complex(const Complex& other) noexcept : a(other.a), b(other.b) {};
        Complex(Complex&& other) noexcept : a(std::move(other.a)), b(std::move(other.b)) {};
        ~Complex() noexcept = default;

        Complex& operator=(const Complex& other) noexcept
        {
            a = other.a;
            b = other.b;
            return *this;
        }

        Complex& operator=(Complex&& other) noexcept
        {
            a = std::move(other.a);
            b = std::move(other.b);
            return *this;
        }

        Complex operator+(const Complex& other) const noexcept
        {
            return Complex(a + other.a, b + other.b);
        }

        Complex operator-(const Complex& other) const noexcept
        {
            return Complex(a - other.a, b - other.b);
        }


        Complex operator*(T scalar) const noexcept
        {
            return Complex(a * scalar, b * scalar);
        }

        Complex operator*(const Complex& other) const noexcept
        {
            return Complex(a * other.a - b * other.b, a * other.b + b * other.a);
        }

        Complex operator/(T scalar) const noexcept
        {
            return Complex(a / scalar, b / scalar);
        }

        Complex operator/(const Complex& other) const noexcept
        {
            return Complex((a * other.a + b * other.b) / (other.a * other.a + other.b * other.b), (b * other.a - a * other.b) / (other.a * other.a + other.b * other.b));
        }

        // Square
        Complex Square() const noexcept
        {
            return Complex(a * a - b * b, 2 * a * b);
        }

        Complex Conjugate() const noexcept
        {
            return Complex(a, -b);
        }

        Complex Abs() const noexcept
        {
            return Complex(std::sqrt(a * a + b * b));
        }

        // c = a + bi, where i^2 = -1
        T a, b;
    };
}
