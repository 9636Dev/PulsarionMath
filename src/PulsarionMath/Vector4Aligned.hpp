#pragma once

#ifndef PULSARION_MATH_VECTOR_HPP
#include "Vector.hpp"
#endif

namespace Pulsarion::Math
{
    template<Arithmetic_t T>
    struct VectorFunctions<4, T, Qualifier::Aligned>
    {
        static inline constexpr Vector<4, T, Qualifier::Aligned> negate(const Vector<4, T, Qualifier::Aligned>& vector) noexcept
        {
            return Vector<4, T, Qualifier::Aligned>{ -vector.x(), -vector.y(), -vector.z(), -vector.w() };
        }

        static inline constexpr Vector<4, T, Qualifier::Aligned> add(const Vector<4, T, Qualifier::Aligned>& left, const Vector<4, T, Qualifier::Aligned>& right) noexcept
        {
            return Vector<4, T, Qualifier::Aligned>{ left.x() + right.x(), left.y() + right.y(), left.z() + right.z(), left.w() + right.w() };
        }

        static inline constexpr Vector<4, T, Qualifier::Aligned> subtract(const Vector<4, T, Qualifier::Aligned>& left, const Vector<4, T, Qualifier::Aligned>& right) noexcept
        {
            return Vector<4, T, Qualifier::Aligned>{ left.x() - right.x(), left.y() - right.y(), left.z() - right.z(), left.w() - right.w() };
        }

        static inline constexpr Vector<4, T, Qualifier::Aligned> multiply(const Vector<4, T, Qualifier::Aligned>& left, const Vector<4, T, Qualifier::Aligned>& right) noexcept
        {
            return Vector<4, T, Qualifier::Aligned>{ left.x() * right.x(), left.y() * right.y(), left.z() * right.z(), left.w() * right.w() };
        }

        static inline constexpr Vector<4, T, Qualifier::Aligned> divide(const Vector<4, T, Qualifier::Aligned>& left, const Vector<4, T, Qualifier::Aligned>& right) noexcept
        {
            return Vector<4, T, Qualifier::Aligned>{ left.x() / right.x(), left.y() / right.y(), left.z() / right.z(), left.w() / right.w() };
        }

        static inline constexpr Vector<4, T, Qualifier::Aligned> multiplyScale(const Vector<4, T, Qualifier::Aligned>& vector, T scalar) noexcept
        {
            return Vector<4, T, Qualifier::Aligned>{ vector.x() * scalar, vector.y() * scalar, vector.z() * scalar, vector.w() * scalar };
        }

        static inline constexpr Vector<4, T, Qualifier::Aligned> divideScale(const Vector<4, T, Qualifier::Aligned>& vector, T scalar) noexcept
        {
            return Vector<4, T, Qualifier::Aligned>{ vector.x() / scalar, vector.y() / scalar, vector.z() / scalar, vector.w() / scalar };
        }

        static inline constexpr bool equal(const Vector<4, T, Qualifier::Aligned>& left, const Vector<4, T, Qualifier::Aligned>& right) noexcept
        {
            return left.x() == right.x() && left.y() == right.y() && left.z() == right.z() && left.w() == right.w();
        }

        static inline constexpr bool notEqual(const Vector<4, T, Qualifier::Aligned>& left, const Vector<4, T, Qualifier::Aligned>& right) noexcept
        {
            return left.x() != right.x() || left.y() != right.y() || left.z() != right.z() || left.w() != right.w();
        }

        static inline constexpr T dot(const Vector<4, T, Qualifier::Aligned>& left, const Vector<4, T, Qualifier::Aligned>& right) noexcept
        {
            return left.x() * right.x() + left.y() * right.y() + left.z() * right.z() + left.w() * right.w();
        }

        static inline constexpr T lengthSquared(const Vector<4, T, Qualifier::Aligned>& vector) noexcept
        {
            return vector.x() * vector.x() + vector.y() * vector.y() + vector.z() * vector.z() + vector.w() * vector.w();
        }
    };
}
