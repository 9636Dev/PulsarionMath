#pragma once

#include "Core.hpp"
#include "Vector.hpp"

namespace Pulsarion::Math
{
    template <float_type T, size_t C, size_t R>
    class Matrix;

    template<float_type T, size_t N>
    Matrix<T, N, N> IdentityMatrix()
    {
        Matrix<T, N, N> result;
        for (size_t i = 0; i < N; i++)
        {
            result.data[i * N + i] = 1;
        }
        return result;
    }

    template <float_type T>
    class Matrix<T, 4, 4> // 4x4 Matrix, column-major
    {
    public:
        Matrix() : data()
        {
            Identity(); // Start with identity matrix
        }
        Matrix(std::array<T, 16> data) : data(data) {}

        void Identity() noexcept
        {
            data[0] = 1;
            data[1] = 0;
            data[2] = 0;
            data[3] = 0;
            data[4] = 0;
            data[5] = 1;
            data[6] = 0;
            data[7] = 0;
            data[8] = 0;
            data[9] = 0;
            data[10] = 1;
            data[11] = 0;
            data[12] = 0;
            data[13] = 0;
            data[14] = 0;
            data[15] = 1;
        }

        Matrix operator+(const Matrix& other) const noexcept
        {
            Matrix result;
            for (size_t i = 0; i < 16; i++)
            {
                result.data[i] = data[i] + other.data[i];
            }
            return result;
        }

        Matrix operator-(const Matrix& other) const noexcept
        {
            Matrix result;
            for (size_t i = 0; i < 16; i++)
            {
                result.data[i] = data[i] - other.data[i];
            }
            return result;
        }

#ifdef PULSARION_MATH_USE_SIMD
        Matrix operator*(const Matrix& other) const noexcept
        requires std::same_as<T, float> || std::same_as<T, double>
        {
            static constexpr size_t batchSize = xsimd::batch<T>::size;
        }
#endif

        Matrix operator*(const Matrix& other) const noexcept
        {
            Matrix result;
            for (int row = 0; row < 4; ++row) {
                for (int col = 0; col < 4; ++col) {
                    result[col][row] =
                        data[row] * other.data[col * 4] +
                        data[4 + row] * other.data[col * 4 + 1] +
                        data[8 + row] * other.data[col * 4 + 2] +
                        data[12 + row] * other.data[col * 4 + 3];
                }
            }
            return result;
        }

#ifdef PULSARION_MATH_USE_SIMD
        Vector<T, 4> operator*(const Vector<T, 4>& other) const noexcept
        requires std::same_as<T, float> || std::same_as<T, double>
        {
            Vector<T, 4> result;
            static constexpr size_t batchSize = xsimd::batch<T>::size;

            for (size_t i = 0; i < 4; ++i) {
                xsimd::batch<T> sum = xsimd::batch<T>(0);

                for (size_t j = 0; j < 4; j += batchSize) {
                    xsimd::batch<T> batch_vec = xsimd::load_unaligned(&other.data[j]);
                    xsimd::batch<T> batch_mat = xsimd::load_unaligned(&data[i * 4 + j]);

                    sum = sum + batch_mat * batch_vec;
                }

                sum.store_aligned(&result[i]);
            }

            return result;
        }
#endif

        Vector<T, 4> operator*(const Vector<T, 4>& other) const noexcept
        {
            Vector<T, 4> result;
            for (int row = 0; row < 4; ++row) {
                result[row] =
                    this[0][row] * other[0] +
                    this[1][row] * other[1] +
                    this[2][row] * other[2] +
                    this[3][row] * other[3];
            }
            return result;
        }

        const Vector<T, 4>& operator[](size_t index) const noexcept
        {
            PULSARION_ASSERT(index < 4, "Index out of bounds!");
            return columns[index];
        }

        Vector<T, 4>& operator[](size_t index) noexcept
        {
            PULSARION_ASSERT(index < 4, "Index out of bounds!");
            return columns[index];
        }

        std::string ToString()
        {
            std::stringstream ss;
            ss << "Matrix4x4(";
            for (size_t i = 0; i < 16; i++)
            {
                ss << data[i];
                if (i != 15)
                {
                    ss << ", ";
                }
            }
            ss << ")";
            return ss.str();
        }

        union
        {
            Vector<T, 4> columns[4];
            std::array<T, 16> data;
        };
    };

    using Mat4 = Matrix<float, 4, 4>;
    using Mat4f = Matrix<float, 4, 4>;
    using Mat4d = Matrix<double, 4, 4>;
    using Mat4ld = Matrix<long double, 4, 4>;
    using Mat4x4 = Matrix<float, 4, 4>;
    using Mat4x4f = Matrix<float, 4, 4>;
    using Mat4x4d = Matrix<double, 4, 4>;
    using Mat4x4ld = Matrix<long double, 4, 4>;
}