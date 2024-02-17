#pragma once

#include "Util.hpp"
#include "../Vector.hpp"

#include <array>

namespace Pulsarion::Math
{
    template<float_type T>
    class Matrix<T, 4, 4, MatrixMajor::RowMajor>
    {
    public:
        // ========================================================================================================
        // Constructors
        // ========================================================================================================
        constexpr Matrix(T m00, T m01, T m02, T m03,
               T m10, T m11, T m12, T m13,
               T m20, T m21, T m22, T m23,
               T m30, T m31, T m32, T m33)
            : m_Rows{ { m00, m01, m02, m03 }, { m10, m11, m12, m13 }, {m20, m21, m22, m23}, {m30, m31, m32, m33} }
        {
        }
        explicit constexpr Matrix(T diagonal)
            : m_Rows{ { diagonal, 0, 0, 0 }, { 0, diagonal, 0, 0 }, { 0, 0, diagonal, 0 }, { 0, 0, 0, diagonal } }
        {
        }

        static constexpr Matrix<T, 4, 4, MatrixMajor::RowMajor> Identity()
        {
            return Matrix<T, 4, 4, MatrixMajor::RowMajor>(1);
        }

        constexpr Matrix(const Matrix<T, 4, 4, MatrixMajor::RowMajor>& other) = default;
        constexpr Matrix(Matrix<T, 4, 4, MatrixMajor::RowMajor>&& other) noexcept = default;
        Matrix& operator=(const Matrix<T, 4, 4, MatrixMajor::RowMajor>& other) = default;
        Matrix& operator=(Matrix<T, 4, 4, MatrixMajor::RowMajor>&& other) noexcept = default;
        ~Matrix() = default;

        // ========================================================================================================
        // Accessors
        // ========================================================================================================

    private:
        std::array<Vector<T, 4>, 4> m_Rows;
    };
}
