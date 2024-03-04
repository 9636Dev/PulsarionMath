#pragma once
#ifndef PULSARION_MATH_VECTOR_HPP
#include "Vector.hpp"
#endif

namespace Pulsarion::Math
{
    template<Arithmetic_t T>
    struct VectorFunctions<4, T, Qualifier::Packed>
    {
        static inline constexpr Vector<4, T, Qualifier::Packed> negate(const Vector<4, T, Qualifier::Packed>& vector) noexcept
        {
            return Vector<4, T, Qualifier::Packed>{ -vector.x(), -vector.y(), -vector.z(), -vector.w() };
        }

        static inline constexpr Vector<4, T, Qualifier::Packed> add(const Vector<4, T, Qualifier::Packed>& left, const Vector<4, T, Qualifier::Packed>& right) noexcept
        {
            return Vector<4, T, Qualifier::Packed>{ left.x() + right.x(), left.y() + right.y(), left.z() + right.z(), left.w() + right.w() };
        }

        static inline constexpr Vector<4, T, Qualifier::Packed> subtract(const Vector<4, T, Qualifier::Packed>& left, const Vector<4, T, Qualifier::Packed>& right) noexcept
        {
            return Vector<4, T, Qualifier::Packed>{ left.x() - right.x(), left.y() - right.y(), left.z() - right.z(), left.w() - right.w() };
        }

        static inline constexpr Vector<4, T, Qualifier::Packed> multiply(const Vector<4, T, Qualifier::Packed>& left, const Vector<4, T, Qualifier::Packed>& right) noexcept
        {
            return Vector<4, T, Qualifier::Packed>{ left.x() * right.x(), left.y() * right.y(), left.z() * right.z(), left.w() * right.w() };
        }

        static inline constexpr Vector<4, T, Qualifier::Packed> divide(const Vector<4, T, Qualifier::Packed>& left, const Vector<4, T, Qualifier::Packed>& right) noexcept
        {
            return Vector<4, T, Qualifier::Packed>{ left.x() / right.x(), left.y() / right.y(), left.z() / right.z(), left.w() / right.w() };
        }

        static inline constexpr Vector<4, T, Qualifier::Packed> multiplyScale(const Vector<4, T, Qualifier::Packed>& vector, T scalar) noexcept
        {
            return Vector<4, T, Qualifier::Packed>{ vector.x() * scalar, vector.y() * scalar, vector.z() * scalar, vector.w() * scalar };
        }

        static inline constexpr Vector<4, T, Qualifier::Packed> divideScale(const Vector<4, T, Qualifier::Packed>& vector, T scalar) noexcept
        {
            return Vector<4, T, Qualifier::Packed>{ vector.x() / scalar, vector.y() / scalar, vector.z() / scalar, vector.w() / scalar };
        }

        static inline constexpr bool equal(const Vector<4, T, Qualifier::Packed>& left, const Vector<4, T, Qualifier::Packed>& right) noexcept
        {
            return left.x() == right.x() && left.y() == right.y() && left.z() == right.z() && left.w() == right.w();
        }

        static inline constexpr bool notEqual(const Vector<4, T, Qualifier::Packed>& left, const Vector<4, T, Qualifier::Packed>& right) noexcept
        {
            return left.x() != right.x() || left.y() != right.y() || left.z() != right.z() || left.w() != right.w();
        }

        static inline constexpr T dot(const Vector<4, T, Qualifier::Packed>& left, const Vector<4, T, Qualifier::Packed>& right) noexcept
        {
            return left.x() * right.x() + left.y() * right.y() + left.z() * right.z() + left.w() * right.w();
        }

        static inline constexpr T lengthSquared(const Vector<4, T, Qualifier::Packed>& vector) noexcept
        {
            return vector.x() * vector.x() + vector.y() * vector.y() + vector.z() * vector.z() + vector.w() * vector.w();
        }
    };
}
