#pragma once
#ifndef PULSARION_MATH_VECTOR_HPP
#include "Vector.hpp"
#endif

#include <immintrin.h>

namespace Pulsarion::Math
{
    template<>
    struct VectorFunctions<4, float, Qualifier::Aligned>
    {
        static inline constexpr Vector<4, float, Qualifier::Aligned> negate(const Vector<4, float, Qualifier::Aligned>& vector) noexcept
        {
            return Vector<4, float, Qualifier::Aligned>{ -vector.x(), -vector.y(), -vector.z(), -vector.w() };
        }

        static inline constexpr Vector<4, float, Qualifier::Aligned> add(const Vector<4, float, Qualifier::Aligned>& left, const Vector<4, float, Qualifier::Aligned>& right) noexcept
        {
            return Vector<4, float, Qualifier::Aligned>{ left.x() + right.x(), left.y() + right.y(), left.z() + right.z(), left.w() + right.w() };
        }

        static inline constexpr Vector<4, float, Qualifier::Aligned> subtract(const Vector<4, float, Qualifier::Aligned>& left, const Vector<4, float, Qualifier::Aligned>& right) noexcept
        {
            return Vector<4, float, Qualifier::Aligned>{ left.x() - right.x(), left.y() - right.y(), left.z() - right.z(), left.w() - right.w() };
        }

        static inline Vector<4, float, Qualifier::Aligned> multiply(const Vector<4, float, Qualifier::Aligned>& left, const Vector<4, float, Qualifier::Aligned>& right) noexcept
        {
            __m128 left128 = _mm_load_ps(&left.x());
            __m128 right128 = _mm_load_ps(&right.x());
            // NOLINTNEXTLINE(portability-simd-intrinsics)
            __m128 result = _mm_mul_ps(left128, right128);
            Vector<4, float, Qualifier::Aligned> resultVector;
            _mm_store_ps(&resultVector.x(), result);
            return resultVector;
        }

        static inline Vector<4, float, Qualifier::Aligned> divide(const Vector<4, float, Qualifier::Aligned>& left, const Vector<4, float, Qualifier::Aligned>& right) noexcept
        {
            __m128 left128 = _mm_load_ps(&left.x());
            __m128 right128 = _mm_load_ps(&right.x());
            // NOLINTNEXTLINE(portability-simd-intrinsics)
            __m128 result = _mm_div_ps(left128, right128);
            Vector<4, float, Qualifier::Aligned> resultVector;
            _mm_store_ps(&resultVector.x(), result);
            return resultVector;
        }

        static inline Vector<4, float, Qualifier::Aligned> multiplyScale(const Vector<4, float, Qualifier::Aligned>& vector, float scalar) noexcept
        {
            __m128 vector128 = _mm_load_ps(&vector.x());
            // NOLINTNEXTLINE(portability-simd-intrinsics)
            __m128 result = _mm_mul_ps(vector128, _mm_set1_ps(scalar));
            Vector<4, float, Qualifier::Aligned> resultVector;
            _mm_store_ps(&resultVector.x(), result);
            return resultVector;
        }

        static inline Vector<4, float, Qualifier::Aligned> divideScale(const Vector<4, float, Qualifier::Aligned>& vector, float scalar) noexcept
        {
            __m128 vector128 = _mm_load_ps(&vector.x());
            // NOLINTNEXTLINE(portability-simd-intrinsics)
            __m128 result = _mm_div_ps(vector128, _mm_set1_ps(scalar));
            Vector<4, float, Qualifier::Aligned> resultVector;
            _mm_store_ps(&resultVector.x(), result);
            return resultVector;
        }

        static inline constexpr bool equal(const Vector<4, float, Qualifier::Aligned>& left, const Vector<4, float, Qualifier::Aligned>& right) noexcept
        {
            return left.x() == right.x() && left.y() == right.y() && left.z() == right.z() && left.w() == right.w();
        }

        static inline constexpr bool notEqual(const Vector<4, float, Qualifier::Aligned>& left, const Vector<4, float, Qualifier::Aligned>& right) noexcept
        {
            return left.x() != right.x() || left.y() != right.y() || left.z() != right.z() || left.w() != right.w();
        }

        static inline float dot(const Vector<4, float, Qualifier::Aligned>& left, const Vector<4, float, Qualifier::Aligned>& right) noexcept
        {
            __m128 left128 = _mm_load_ps(&left.x());
            __m128 right128 = _mm_load_ps(&right.x());
            // NOLINTNEXTLINE(portability-simd-intrinsics)
            __m128 result = _mm_dp_ps(left128, right128, 0b11110001);
            return _mm_cvtss_f32(result);
        }

        static inline float lengthSquared(const Vector<4, float, Qualifier::Aligned>& vector) noexcept
        {
            // x * x + y * y + z * z + w * w == dot(vector, vector)
            return dot(vector, vector); // This is to save caching another function
        }
    };
}


