#pragma once

#include "Core.hpp"
#include "Vector.hpp"

#include <xsimd/xsimd.hpp>

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
        requires std::same_as<T, float_normalp> || (std::same_as<PULSARION_MATH_SIMD, xsimd::avx> && std::same_as<T, float_highp>)
        {
            PULSARION_MATH_ALIGN std::array<T, 4> temp{};
            xsimd::batch<T> this_batch_rows[4];
            xsimd::batch<T> other_batch_cols[4];

            for (int i = 0; i < 4; i++)
            {
                temp = { data[i], data[i + 4], data[i + 8], data[i + 12] };
                this_batch_rows[i] = xsimd::batch<T>::load_aligned(temp.data());
                other_batch_cols[i] = xsimd::batch<T>::load_unaligned(other.columns[i].data.data());
            }

            Matrix result;
            for (int row = 0; row < 4; ++row)
            {
                for (int col = 0; col < 4; ++col)
                {
                    xsimd::batch<float> batch_result = this_batch_rows[row] * other_batch_cols[col];
                    result.data[row + 4 * col] = xsimd::reduce_add(batch_result);
                }
            }


            return result;
        }

        Matrix operator*(const Matrix& other) const noexcept
            // ReSharper disable once CppRedundantBooleanExpressionArgument (Can be AVX on some platforms)
            requires (!std::same_as<PULSARION_MATH_SIMD, xsimd::avx> && std::same_as<T, float_highp>)
        {
            PULSARION_MATH_ALIGN std::array<double, 2> temp{};
            xsimd::batch<double> this_batch_rows[8];
            xsimd::batch<double> other_batch_cols[8];

            for (int i = 0; i < 4; i++)
            {
                temp = { data[i], data[i + 4] };
                this_batch_rows[i * 2] = xsimd::batch<T>::load_aligned(temp.data());
                temp = { data[i + 8], data[i + 12] };
                this_batch_rows[i * 2 + 1] = xsimd::batch<T>::load_aligned(temp.data());
                other_batch_cols[i * 2] = xsimd::batch<T>::load_unaligned(other.columns[i].data.data());
                other_batch_cols[i * 2 + 1] = xsimd::batch<T>::load_unaligned(&other.columns[i].data[2]);
            }

            Matrix result;
            for (int row = 0; row < 4; ++row)
            {
                for (int col = 0; col < 4; ++col)
                {
                    xsimd::batch<double> batch_result1 = this_batch_rows[row * 2] * other_batch_cols[col * 2];
                    xsimd::batch<double> batch_result2 = this_batch_rows[row * 2 + 1] * other_batch_cols[col * 2 + 1];
                    result.data[row + 4 * col] = xsimd::reduce_add(batch_result1) + xsimd::reduce_add(batch_result2);
                }
            }


            return result;
        }


        Matrix operator*(const Matrix& other) const noexcept
        requires std::same_as<T, float_extp> 
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
#else   

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
#endif

#ifdef PULSARION_MATH_USE_SIMD
        Vector<T, 4> operator*(const Vector<T, 4>& other) const noexcept
        requires std::same_as<T, float_normalp> || (std::same_as<PULSARION_MATH_SIMD, xsimd::avx> && std::same_as<T, float_highp>)
        {
            Vector<T, 4> result;

            xsimd::batch<T> batch_other, batch_col;
            batch_other = xsimd::batch<T>::load_aligned(other.data.data());
            for (int i = 0;i < 4; ++i)
            {
                batch_col = xsimd::batch<T>::load_unaligned(columns[i].data.data());
                xsimd::batch<float> batch_result = batch_col * batch_other;
                result.data[i] = xsimd::reduce_add(batch_result);
            }

            return result;
        }

        Vector<T, 4> operator*(const Vector<T, 4>& other) const noexcept
        requires std::same_as<T, float_extp> 
        {
            return {
                data[0] * other.x + data[1] * other.y + data[2] * other.z + data[3] * other.w,
                data[4] * other.x + data[5] * other.y + data[6] * other.z + data[7] * other.w,
                data[8] * other.x + data[9] * other.y + data[10] * other.z + data[11] * other.w,
                data[12] * other.x + data[13] * other.y + data[14] * other.z + data[15] * other.w
            };
        }
#else
        Vector<T, 4> operator*(const Vector<T, 4>& other) const noexcept
        {
            return {
                data[0] * other.x + data[1] * other.y + data[2] * other.z + data[3] * other.w,
                data[4] * other.x + data[5] * other.y + data[6] * other.z + data[7] * other.w,
                data[8] * other.x + data[9] * other.y + data[10] * other.z + data[11] * other.w,
                data[12] * other.x + data[13] * other.y + data[14] * other.z + data[15] * other.w
            };
        }
#endif

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

        [[nodiscard]] std::string ToString() const
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


    // Explicit template instantiations
    template class Matrix<float_normalp, 4, 4>;
    template class Matrix<float_highp, 4, 4>;
    template class Matrix<float_extp, 4, 4>;
}

