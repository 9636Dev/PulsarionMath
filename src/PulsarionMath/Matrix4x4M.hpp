#pragma once

#ifndef PULSARION_MATH_MATRIX_HPP
#include "Matrix.hpp"
#endif

namespace Pulsarion::Math
{
    template<Arithmetic_t T>
    struct MatrixFunctions<4, 4, T>
    {
        inline static void TransposeInPlace(Matrix<4, 4, T>& matrix) noexcept
        {
            for (std::size_t i = 0; i < 4; ++i)
            {
                for (std::size_t j = i + 1; j < 4; ++j)
                {
                    std::swap(matrix.Get(i, j), matrix.Get(j, i));
                }
            }
        };


        inline static Matrix<4, 4, T> Multiply(const Matrix<4, 4, T>& left, const Matrix<4, 4, T>& right) noexcept
        {
            Matrix<4, 4, T> result;
            // Column major multiplication algorithm
            for (std::size_t i = 0; i < 4; ++i)
            {
                for (std::size_t j = 0; j < 4; ++j)
                {
                    result.Get(i, j) = left.Get(i, 0) * right.Get(0, j) +
                                       left.Get(i, 1) * right.Get(1, j) +
                                       left.Get(i, 2) * right.Get(2, j) +
                                       left.Get(i, 3) * right.Get(3, j);
                }
            }
            return result;
        }

        inline static Vector<4, T, Qualifier::Aligned> VecMultiply(const Matrix<4, 4, T>& left, const Vector<4, T, Qualifier::Aligned>& right) noexcept
        {
            Vector<4, T, Qualifier::Aligned> result;
            for (std::size_t i = 0; i < 4; ++i)
            {
                result[i] = left.Get(i, 0) * right[0] +
                            left.Get(i, 1) * right[1] +
                            left.Get(i, 2) * right[2] +
                            left.Get(i, 3) * right[3];
            }
            return result;
        }
    };
}
