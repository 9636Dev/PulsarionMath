#pragma once

#include "../Core.hpp"

// The user can choose if they want column-major or row-major matrices, or both
#if !defined(PULSARION_MATH_MATRIX_ROW_MAJOR) && !defined(PULSARION_MATH_MATRIX_COLUMN_MAJOR)
#error "You must define either PULSARION_MATH_MATRIX_ROW_MAJOR or PULSARION_MATH_MATRIX_COLUMN_MAJOR"
#endif

// We need to check for both
#if defined(PULSARION_MATH_MATRIX_ROW_MAJOR) && defined(PULSARION_MATH_MATRIX_COLUMN_MAJOR)
#error "You can't define both PULSARION_MATH_MATRIX_ROW_MAJOR and PULSARION_MATH_MATRIX_COLUMN_MAJOR"
#endif

namespace Pulsarion::Math
{
    enum class MatrixMajor
    {
        RowMajor,
        ColumnMajor,
    };

    /// <summary>
    /// A Matrix class that represents a matrix of any size and type.
    /// </summary>
    /// <typeparam name="T">The type, this could be normal_p, high_p or ext_p</typeparam>
    /// <typeparam name="C">The number of columns</typeparam>
    /// <typeparam name="R">The number of rows</typeparam>
    /// <typeparam name="M">The Major of the Matrix type</typeparam>
    template <float_type T, size_t C, size_t R, MatrixMajor M>
    class Matrix;
}
