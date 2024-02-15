#pragma once

#include "Core.hpp"
#include "Simd.hpp"

// The user can choose if they want column-major or row-major matrices, or both
#if !defined(PULSARION_MATH_MATRIX_ROW_MAJOR) && !defined(PULSARION_MATH_MATRIX_COLUMN_MAJOR)
#error "You must define either PULSARION_MATH_MATRIX_ROW_MAJOR or PULSARION_MATH_MATRIX_COLUMN_MAJOR"
#endif

// We need to check for both
#if (defined(PULSARION_MATH_MATRIX_ROW_MAJOR) && defined(PULSARION_MATH_MATRIX_COLUMN_MAJOR)) || defined(PULSARION_MATH_MATRIX_DUAL_MAJOR)
#undef PULSARION_MATH_MATRIX_ROW_MAJOR
#undef PULSARION_MATH_MATRIX_COLUMN_MAJOR
#define PULSARION_MATH_MATRIX_DUAL_MAJOR
#endif

namespace Pulsarion::Math
{
    enum class MatrixMajor
    {
        RowMajor,
        ColumnMajor,
        BothMajor, // This costs double the space, but increases SIMD speeds
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

    /// <summary>
    /// A row of a matrix, this is used to access the elements of the matrix.
    /// </summary>
    /// <typeparam name="T">The type</typeparam>
    /// <typeparam name="C">The number of columns in the row</typeparam>
    template<float_type T, size_t C>
    class MatrixRow
    {
    private:
        template <float_type, size_t, size_t, MatrixMajor>
        friend class Matrix;
        explicit MatrixRow(std::array<T, C>&& data) : data(data) {}
    public:
        T operator[](size_t index) const noexcept
        {
            return data[index];
        }

        T& operator[](size_t index) noexcept
        {
            return data[index];
        }

        std::array<T, C> data;
    };

    /// <summary>
    /// A column of a matrix, this is used to access the elements of the matrix.
    /// </summary>
    /// <typeparam name="T">The type</typeparam>
    /// <typeparam name="R">The number of rows in the column</typeparam>
    template<float_type T, size_t R>
    class MatrixColumn
    {
    private:
        template <float_type, size_t, size_t, MatrixMajor>
        friend class Matrix;
        explicit MatrixColumn(std::array<T, R>&& data) : data(data) {}
    public:
        T operator[](size_t index) const noexcept
        {
            return data[index];
        }

        T& operator[](size_t index) noexcept
        {
            return data[index];
        }

        std::array<T, R> data;
    };

    template<float_type T>
    class Matrix<T, 4, 4, MatrixMajor::BothMajor> // Only 4x4 matrices are supported for now, since they are required for graphics
    {
    private:
        void UpdateColumns() noexcept
        {
            for (size_t i = 0; i < 4; i++)
                columns[i] = MatrixColumn<T, 4>(std::array<T, 4>{data[i], data[i + 4], data[i + 8], data[i + 12]});
        }
    public:
        // We want it to be implicit here
        //NOLINTNEXTLINE(google-explicit-constructor)
        Matrix(const std::array<T, 16>& data) : data(data) {
            UpdateColumns();
        }

        explicit Matrix(std::array<T, 16>&& data) : data(std::move(data)) {
            UpdateColumns();
        }

        Matrix(const Matrix& other) : data(other.data) {
            for (size_t i = 0; i < 4; i++)
                columns[i] = other.columns[i];
        }

        Matrix(Matrix&& other) noexcept : data(std::move(other.data)) {
            for (size_t i = 0; i < 4; i++)
                columns[i] = std::move(other.columns[i]);
        }

        // Different float types need to explicitly convert
        template<float_type U, MatrixMajor N>
        explicit Matrix(const Matrix<U, 4, 4, N>& other) : data(other.data) {
            for (size_t i = 0; i < 4; i++)
                columns[i] = other.columns[i];
        }

        // We don't support move with different float types

        // Implicity convert row-major to column-major
        template<MatrixMajor N>
        //NOLINTNEXTLINE(google-explicit-constructor)
        Matrix(const Matrix<T, 4, 4, N>& other) : data(other.data) {
            if constexpr (N == MatrixMajor::ColumnMajor)
                Transpose(); // We have to transpose te data
            else if constexpr (N == MatrixMajor::RowMajor)
                UpdateColumns(); // We need to update the columns
            else
            {
                for (size_t i = 0; i < 4; i++)
                    columns[i] = other.columns[i];
            }
        }

        template<MatrixMajor N>
        //NOLINTNEXTLINE(google-explicit-constructor)
        Matrix(const Matrix<T, 4, 4, N>&& other) : data(std::move(other.data)) {
            if constexpr (N == MatrixMajor::ColumnMajor)
                Transpose(); // We have to transpose te data
            else if constexpr (N == MatrixMajor::RowMajor)
                UpdateColumns(); // We need to update the columns
            else
            {
                for (size_t i = 0; i < 4; i++)
                    columns[i] = std::move(other.columns[i]);
            }
        }

        std::array<MatrixRow<T, 4>, 4> GetRows() const noexcept { return rows; }
        std::array<MatrixColumn<T, 4>, 4> GetColumns() const noexcept { return columns; }

        void Transpose() noexcept
        {
            // We just transpose the matrix
            for (size_t row = 0; row < 4; row++)
            {
                for (size_t col = 0; col < row; col++)
                {
                    std::swap(data[row + 4 * col], data[col + 4 * row]);
                }
            }

            UpdateColumns();
        }

        // TODO: Figure out how to make references work with rows and columns

        PULSARION_MATH_ALIGN union
        {
            std::array<T, 16> data;
            std::array<MatrixRow<T, 4>, 4> rows;
        };
        PULSARION_MATH_ALIGN std::array<MatrixColumn<T, 4>, 4> columns;
    };

    // We use the defines to create aliases for the different types of matrices
#ifdef PULSARION_MATH_MATRIX_ROW_MAJOR
    using Mat4 = Matrix<float_normalp, 4, 4, MatrixMajor::RowMajor>;
#elif defined(PULSARION_MATH_MATRIX_COLUMN_MAJOR)
    using Mat4 = Matrix<float_normalp, 4, 4, MatrixMajor::ColumnMajor>;
#elif defined(PULSARION_MATH_MATRIX_DUAL_MAJOR)
    using Mat4 = Matrix<float_normalp, 4, 4, MatrixMajor::BothMajor>;
#endif
}

