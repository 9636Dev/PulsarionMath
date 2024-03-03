#pragma once
#ifndef PULSARION_MATH_VECTOR_HPP
#include "Vector.hpp"
#endif

#include <immintrin.h>

namespace Pulsarion::Math
{
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

        static inline Vector<4, float, Qualifier::Packed> multiply(const Vector<4, float, Qualifier::Packed>& left, const Vector<4, float, Qualifier::Packed>& right) noexcept
        {
            __m128 left128 = _mm_loadu_ps(&left.x());
            __m128 right128 = _mm_loadu_ps(&right.x());
            // NOLINTNEXTLINE(portability-simd-intrinsics)
            __m128 result = _mm_mul_ps(left128, right128);
            Vector<4, float, Qualifier::Packed> resultVector;
            _mm_storeu_ps(&resultVector.x(), result);
            return resultVector;
        }

        static inline Vector<4, float, Qualifier::Packed> divide(const Vector<4, float, Qualifier::Packed>& left, const Vector<4, float, Qualifier::Packed>& right) noexcept
        {
            __m128 left128 = _mm_loadu_ps(&left.x());
            __m128 right128 = _mm_loadu_ps(&right.x());
            // NOLINTNEXTLINE(portability-simd-intrinsics)
            __m128 result = _mm_div_ps(left128, right128);
            Vector<4, float, Qualifier::Packed> resultVector;
            _mm_storeu_ps(&resultVector.x(), result);
            return resultVector;
        }

        static inline Vector<4, float, Qualifier::Packed> multiplyScale(const Vector<4, float, Qualifier::Packed>& vector, float scalar) noexcept
        {
            __m128 vector128 = _mm_loadu_ps(&vector.x());
            // NOLINTNEXTLINE(portability-simd-intrinsics)
            __m128 result = _mm_mul_ps(vector128, _mm_set1_ps(scalar));
            Vector<4, float, Qualifier::Packed> resultVector;
            _mm_storeu_ps(&resultVector.x(), result);
            return resultVector;
        }

        static inline Vector<4, float, Qualifier::Packed> divideScale(const Vector<4, float, Qualifier::Packed>& vector, float scalar) noexcept
        {
            __m128 vector128 = _mm_loadu_ps(&vector.x());
            // NOLINTNEXTLINE(portability-simd-intrinsics)
            __m128 result = _mm_div_ps(vector128, _mm_set1_ps(scalar));
            Vector<4, float, Qualifier::Packed> resultVector;
            _mm_storeu_ps(&resultVector.x(), result);
            return resultVector;
        }

        static inline constexpr bool equal(const Vector<4, float, Qualifier::Packed>& left, const Vector<4, float, Qualifier::Packed>& right) noexcept
        {
            return left.x() == right.x() && left.y() == right.y() && left.z() == right.z() && left.w() == right.w();
        }

        static inline constexpr bool notEqual(const Vector<4, float, Qualifier::Packed>& left, const Vector<4, float, Qualifier::Packed>& right) noexcept
        {
            return left.x() != right.x() || left.y() != right.y() || left.z() != right.z() || left.w() != right.w();
        }

        static inline float dot(const Vector<4, float, Qualifier::Packed>& left, const Vector<4, float, Qualifier::Packed>& right) noexcept
        {
            __m128 left128 = _mm_loadu_ps(&left.x());
            __m128 right128 = _mm_loadu_ps(&right.x());
            // NOLINTNEXTLINE(portability-simd-intrinsics)
            __m128 result = _mm_dp_ps(left128, right128, 0b11110001);
            return _mm_cvtss_f32(result);
        }

        static inline float lengthSquared(const Vector<4, float, Qualifier::Packed>& vector) noexcept
        {
            // x * x + y * y + z * z + w * w == dot(vector, vector)
            return dot(vector, vector); // This is to save caching another function
        }
    };
}
