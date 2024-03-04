#pragma once

#ifndef PULSARION_MATH_MATRIX_HPP
#include "Matrix.hpp"
#endif
#include <immintrin.h>

namespace Pulsarion::Math
{
    template<>
    struct MatrixFunctions<4, 4, float>
    {
        inline constexpr static void TransposeInPlace(Matrix<4, 4, float>& matrix) noexcept
        {
            __m128 row0 = _mm_load_ps(&matrix[0].x());
            __m128 row1 = _mm_load_ps(&matrix[1].x());
            __m128 row2 = _mm_load_ps(&matrix[2].x());
            __m128 row3 = _mm_load_ps(&matrix[3].x());

            _MM_TRANSPOSE4_PS(row0, row1, row2, row3);

            _mm_store_ps(&matrix[0].x(), row0);
            _mm_store_ps(&matrix[1].x(), row1);
            _mm_store_ps(&matrix[2].x(), row2);
            _mm_store_ps(&matrix[3].x(), row3);
        };

        inline static Matrix<4, 4, float> Multiply(const Matrix<4, 4, float>& left, const Matrix<4, 4, float>& right) noexcept
        {
            __m128 in1[4];
            __m128 in2[4];
            __m128 out[4];

            in1[0] = _mm_load_ps(&left[0].x());
            in1[1] = _mm_load_ps(&left[1].x());
            in1[2] = _mm_load_ps(&left[2].x());
            in1[3] = _mm_load_ps(&left[3].x());

            in2[0] = _mm_load_ps(&right[0].x());
            in2[1] = _mm_load_ps(&right[1].x());
            in2[2] = _mm_load_ps(&right[2].x());
            in2[3] = _mm_load_ps(&right[3].x());

            Matrix<4, 4, float> result;
            {
                __m128 e0 = _mm_shuffle_ps(in2[0], in2[0], _MM_SHUFFLE(0, 0, 0, 0));
                __m128 e1 = _mm_shuffle_ps(in2[0], in2[0], _MM_SHUFFLE(1, 1, 1, 1));
                __m128 e2 = _mm_shuffle_ps(in2[0], in2[0], _MM_SHUFFLE(2, 2, 2, 2));
                __m128 e3 = _mm_shuffle_ps(in2[0], in2[0], _MM_SHUFFLE(3, 3, 3, 3));

                //NOLINTNEXTLINE(portability-simd-intrinsics)
                __m128 m0 = _mm_mul_ps(in1[0], e0);
                //NOLINTNEXTLINE(portability-simd-intrinsics)
                __m128 m1 = _mm_mul_ps(in1[1], e1);
                //NOLINTNEXTLINE(portability-simd-intrinsics)
                __m128 m2 = _mm_mul_ps(in1[2], e2);
                //NOLINTNEXTLINE(portability-simd-intrinsics)
                __m128 m3 = _mm_mul_ps(in1[3], e3);

                //NOLINTNEXTLINE(portability-simd-intrinsics)
                __m128 a0 = _mm_add_ps(m0, m1);
                //NOLINTNEXTLINE(portability-simd-intrinsics)
                __m128 a1 = _mm_add_ps(m2, m3);
                //NOLINTNEXTLINE(portability-simd-intrinsics)
                __m128 a2 = _mm_add_ps(a0, a1);

                out[0] = a2;
            }

            {
                __m128 e0 = _mm_shuffle_ps(in2[1], in2[1], _MM_SHUFFLE(0, 0, 0, 0));
                __m128 e1 = _mm_shuffle_ps(in2[1], in2[1], _MM_SHUFFLE(1, 1, 1, 1));
                __m128 e2 = _mm_shuffle_ps(in2[1], in2[1], _MM_SHUFFLE(2, 2, 2, 2));
                __m128 e3 = _mm_shuffle_ps(in2[1], in2[1], _MM_SHUFFLE(3, 3, 3, 3));

                //NOLINTNEXTLINE(portability-simd-intrinsics)
                __m128 m0 = _mm_mul_ps(in1[0], e0);
                //NOLINTNEXTLINE(portability-simd-intrinsics)
                __m128 m1 = _mm_mul_ps(in1[1], e1);
                //NOLINTNEXTLINE(portability-simd-intrinsics)
                __m128 m2 = _mm_mul_ps(in1[2], e2);
                //NOLINTNEXTLINE(portability-simd-intrinsics)
                __m128 m3 = _mm_mul_ps(in1[3], e3);

                //NOLINTNEXTLINE(portability-simd-intrinsics)
                __m128 a0 = _mm_add_ps(m0, m1);
                //NOLINTNEXTLINE(portability-simd-intrinsics)
                __m128 a1 = _mm_add_ps(m2, m3);
                //NOLINTNEXTLINE(portability-simd-intrinsics)
                __m128 a2 = _mm_add_ps(a0, a1);

                out[1] = a2;
            }

            {
                __m128 e0 = _mm_shuffle_ps(in2[2], in2[2], _MM_SHUFFLE(0, 0, 0, 0));
                __m128 e1 = _mm_shuffle_ps(in2[2], in2[2], _MM_SHUFFLE(1, 1, 1, 1));
                __m128 e2 = _mm_shuffle_ps(in2[2], in2[2], _MM_SHUFFLE(2, 2, 2, 2));
                __m128 e3 = _mm_shuffle_ps(in2[2], in2[2], _MM_SHUFFLE(3, 3, 3, 3));

                //NOLINTNEXTLINE(portability-simd-intrinsics)
                __m128 m0 = _mm_mul_ps(in1[0], e0);
                //NOLINTNEXTLINE(portability-simd-intrinsics)
                __m128 m1 = _mm_mul_ps(in1[1], e1);
                //NOLINTNEXTLINE(portability-simd-intrinsics)
                __m128 m2 = _mm_mul_ps(in1[2], e2);
                //NOLINTNEXTLINE(portability-simd-intrinsics)
                __m128 m3 = _mm_mul_ps(in1[3], e3);

                //NOLINTNEXTLINE(portability-simd-intrinsics)
                __m128 a0 = _mm_add_ps(m0, m1);
                //NOLINTNEXTLINE(portability-simd-intrinsics)
                __m128 a1 = _mm_add_ps(m2, m3);
                //NOLINTNEXTLINE(portability-simd-intrinsics)
                __m128 a2 = _mm_add_ps(a0, a1);

                out[2] = a2;
            }

            {
                //(__m128&)_mm_shuffle_epi32(__m128i&)in2[0], _MM_SHUFFLE(3, 3, 3, 3))
                __m128 e0 = _mm_shuffle_ps(in2[3], in2[3], _MM_SHUFFLE(0, 0, 0, 0));
                __m128 e1 = _mm_shuffle_ps(in2[3], in2[3], _MM_SHUFFLE(1, 1, 1, 1));
                __m128 e2 = _mm_shuffle_ps(in2[3], in2[3], _MM_SHUFFLE(2, 2, 2, 2));
                __m128 e3 = _mm_shuffle_ps(in2[3], in2[3], _MM_SHUFFLE(3, 3, 3, 3));

                //NOLINTNEXTLINE(portability-simd-intrinsics)
                __m128 m0 = _mm_mul_ps(in1[0], e0);
                //NOLINTNEXTLINE(portability-simd-intrinsics)
                __m128 m1 = _mm_mul_ps(in1[1], e1);
                //NOLINTNEXTLINE(portability-simd-intrinsics)
                __m128 m2 = _mm_mul_ps(in1[2], e2);
                //NOLINTNEXTLINE(portability-simd-intrinsics)
                __m128 m3 = _mm_mul_ps(in1[3], e3);

                //NOLINTNEXTLINE(portability-simd-intrinsics)
                __m128 a0 = _mm_add_ps(m0, m1);
                //NOLINTNEXTLINE(portability-simd-intrinsics)
                __m128 a1 = _mm_add_ps(m2, m3);
                //NOLINTNEXTLINE(portability-simd-intrinsics)
                __m128 a2 = _mm_add_ps(a0, a1);

                out[3] = a2;
            }

            _mm_store_ps(&result[0].x(), out[0]);
            _mm_store_ps(&result[1].x(), out[1]);
            _mm_store_ps(&result[2].x(), out[2]);
            _mm_store_ps(&result[3].x(), out[3]);

            return result;
        }
    };
}
