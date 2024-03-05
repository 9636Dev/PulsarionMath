#pragma once
#define PULSARION_MATH_MATRIX_HPP

#include "PulsarionMath/Qualifier.hpp"
#include "Vector.hpp"
#include "Simd.hpp"
#include "MatrixCommon.hpp"

namespace Pulsarion::Math
{
    template<std::size_t R, std::size_t C, Arithmetic_t T>
    class Matrix
    {
    public:
#ifdef PULSARION_MATH_MATRIX_COLUMN_MAJOR
        PULSARION_MATH_ALIGN Vector<C, T, Qualifier::Aligned> data[R];
#else
        Vector<R, T, Qualifier::Aligned> data[C];
#endif

        // ---- Constructors ----
#ifdef PULSARION_MATH_MATRIX_COLUMN_MAJOR
        inline constexpr Matrix(const T& m00, const T& m01, const T& m02, const T& m03,
                                const T& m10, const T& m11, const T& m12, const T& m13,
                                const T& m20, const T& m21, const T& m22, const T& m23,
                                const T& m30, const T& m31, const T& m32, const T& m33) noexcept
            : data{ Vector<C, T, Qualifier::Aligned>(m00, m10, m20, m30),
                    Vector<C, T, Qualifier::Aligned>(m01, m11, m21, m31),
                    Vector<C, T, Qualifier::Aligned>(m02, m12, m22, m32),
                    Vector<C, T, Qualifier::Aligned>(m03, m13, m23, m33) } {}
#else
        inline constexpr Matrix(const T& m00, const T& m01, const T& m02, const T& m03,
                                const T& m10, const T& m11, const T& m12, const T& m13,
                                const T& m20, const T& m21, const T& m22, const T& m23,
                                const T& m30, const T& m31, const T& m32, const T& m33) noexcept
            : data{ Vector<R, T, Qualifier::Aligned>(m00, m01, m02, m03),
                    Vector<R, T, Qualifier::Aligned>(m10, m11, m12, m13),
                    Vector<R, T, Qualifier::Aligned>(m20, m21, m22, m23),
                    Vector<R, T, Qualifier::Aligned>(m30, m31, m32, m33) } {}

#endif
        explicit inline constexpr Matrix(const T& value) noexcept : Matrix(value, 0, 0, 0,
                                                                        0, value, 0, 0,
                                                                        0, 0, value, 0,
                                                                        0, 0, 0, value) {}

        // Identity matrix by default
        inline constexpr Matrix() noexcept : Matrix(1) {}

        // ---- Accessors ----
#ifdef PULSARION_MATH_MATRIX_COLUMN_MAJOR
        inline constexpr T& Get(std::size_t row, std::size_t column) noexcept { return data[column][row]; }
        [[nodiscard]] inline constexpr const T& Get(std::size_t row, std::size_t column) const noexcept { return data[column][row]; }
#else
        inline constexpr T& Get(std::size_t row, std::size_t column) noexcept { return data[row][column]; }
        [[nodiscard]] inline constexpr const T& Get(std::size_t row, std::size_t column) const noexcept { return data[row][column]; }
#endif

        [[nodiscard]] inline constexpr bool IsSquare() const noexcept { return R == C; }
#ifdef PULSARION_MATH_MATRIX_COLUMN_MAJOR
        [[nodiscard]] inline constexpr bool IsColumnMajor() const noexcept { return true; }
        [[nodiscard]] inline constexpr bool IsRowMajor() const noexcept { return false; }
#else
        [[nodiscard]] inline constexpr bool IsColumnMajor() const noexcept { return false; }
        [[nodiscard]] inline constexpr bool IsRowMajor() const noexcept { return true; }
#endif

        // This shouldn't be used for anything, but it is used for transposing
        inline constexpr Vector<C, T, Qualifier::Aligned>& operator[](std::size_t index) noexcept { return data[index]; }
        inline constexpr const Vector<C, T, Qualifier::Aligned>& operator[](std::size_t index) const noexcept { return data[index]; }

#ifdef PULSARION_MATH_MATRIX_COLUMN_MAJOR
        // Returning const references is fine, since they are used the same way as a copy
        [[nodiscard]] inline constexpr const Vector<C, T, Qualifier::Aligned>& Row(std::size_t index) const noexcept { return data[index]; }
        [[nodiscard]] inline constexpr Vector<R, T, Qualifier::Aligned> Column(std::size_t index) const noexcept
        {
            Vector<R, T, Qualifier::Aligned> result;
            for (std::size_t i = 0; i < R; ++i)
                result[i] = data[i][index];
            return result;
        }
#else
        [[nodiscard]] inline constexpr const Vector<R, T, Qualifier::Aligned>& Row(std::size_t index) const noexcept { return data[index]; }
        [[nodiscard]] inline constexpr Vector<C, T, Qualifier::Aligned> Column(std::size_t index) const noexcept
        {
            Vector<C, T, Qualifier::Aligned> result;
            for (std::size_t i = 0; i < C; ++i)
                result[i] = data[i][index];
            return result;
        }
#endif
        inline void TransposeInPlace() noexcept
        {
            MatrixFunctions<R, C, T>::TransposeInPlace(*this);
        }

        Matrix<C, R, T> Transpose() const noexcept
        {
            Matrix<C, R, T> result;
            result.TransposeInPlace();
            return result;
        }

        inline Matrix<R, C, T> operator*(const Matrix<R, C, T>& other) const noexcept
        {
            return MatrixFunctions<R, C, T>::Multiply(*this, other);
        }

        inline Vector<R, T, Qualifier::Aligned> operator*(const Vector<R, T, Qualifier::Aligned>& other) const noexcept
        {
            return MatrixFunctions<R, C, T>::VecMultiply(*this, other);
        }
    };
}

#ifdef PULSARION_MATH_MATRIX_COLUMN_MAJOR
#ifdef PULSARION_MATH_SIMD_SSE4_1
#include "Matrix4x4MSSE.hpp"
#else
#include "Matrix4x4M.hpp"
#endif
#else
#error Not implemented
#endif

