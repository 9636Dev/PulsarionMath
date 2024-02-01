#pragma once

#include "Matrix.hpp"

namespace Pulsarion::Math
{
    template<float_type T>
    using axis_type = Vector<T, 3>;

    template<float_type T>
    axis_type<T> AxisX()
    {
        return { 1, 0, 0 };
    }

    template<float_type T>
    axis_type<T> AxisY()
    {
        return { 0, 1, 0 };
    }

    template<float_type T>
    Matrix<T, 4, 4> MatrixTranslate(const Vector<T, 3>& translation, const Matrix<T, 4, 4>& matrix = IdentityMatrix<T, 4>())
    {
        auto result = matrix; // Copy
        result[3][0] += translation[0];
        result[3][1] += translation[1];
        result[3][2] += translation[2];
        return result;
    }

    template<float_type T>
    Matrix<T, 4, 4> MatrixScale(const Vector<T, 3>& scale)
    {
        auto result = Matrix<T, 4, 4>();
        result[0][0] *= scale.x;
        result[1][1] *= scale.y;
        result[2][2] *= scale.z;
        
        return result;
    }

    template<float_type T>
    Matrix<T, 4, 4> MatrixScale(const Vector<T, 3>& scale, const Matrix<T, 4, 4>& matrix)
    {
		return matrix * MatrixScale(scale);
	}

    template<float_type T>
    Matrix<T, 4, 4> MatrixRotateX(const T& angle)
    {
        auto result = Matrix<T, 4, 4>();
        const T cos = Cos(angle); // T is automatically deduced
        const T sin = Sin(angle);
        result[1][1] = cos;
        result[1][2] = sin;
        result[2][1] = -sin;
        result[2][2] = cos;
        return result;
    }

    template<float_type T>
    Matrix<T, 4, 4> MatrixRotateX(const T& angle, const Matrix<T, 4, 4>& matrix)
    {
        return matrix * MatrixRotateX(angle);
    }

    template<float_type T>
    Matrix<T, 4, 4> MatrixRotateY(const T& angle)
    {
        auto result = Matrix<T, 4, 4>();
        const T cos = Cos(angle);
        const T sin = Sin(angle);
        result[0][0] = cos;
        result[0][2] = -sin;
        result[2][0] = sin;
        result[2][2] = cos;
        return result;
    }

    template<float_type T>
    Matrix<T, 4, 4> MatrixRotateY(const T& angle, const Matrix<T, 4, 4>& matrix)
    {
        return matrix * MatrixRotateY(angle);
    }

    template<float_type T>
    Matrix<T, 4, 4> MatrixRotateZ(const T& angle)
    {
        auto result = Matrix<T, 4, 4>();
        const T cos = Cos(angle);
        const T sin = Sin(angle);
        result[0][0] = cos;
        result[0][1] = sin;
        result[1][0] = -sin;
        result[1][1] = cos;
        return result;
    }

    template<float_type T>
    Matrix<T, 4, 4> MatrixRotateZ(const T& angle, const Matrix<T, 4, 4>& matrix)
    {
        return matrix * MatrixRotateZ(angle);
    }

    template<float_type T>
    Matrix<T, 4, 4> MatrixRotate(const T& angle, const Vector<T, 3>& axis)
    {
        auto result = Matrix<T, 4, 4>();
        const T cos = Cos(angle);
        const T sin = Sin(angle);
        const T oneMinusCos = 1 - cos;
        const T x = axis.x;
        const T y = axis.y;
        const T z = axis.z;
        result[0][0] = cos  + x     * x             * oneMinusCos;
        result[0][1] = x    * y     * oneMinusCos   + z * sin;
        result[0][2] = x    * z     * oneMinusCos   - y * sin;
        result[1][0] = y    * x     * oneMinusCos   - z * sin;
        result[1][1] = cos  + y     * y             * oneMinusCos;
        result[1][2] = y    * z     * oneMinusCos   + x * sin;
        result[2][0] = z    * x     * oneMinusCos   + y * sin;
        result[2][1] = z    * y     * oneMinusCos   - x * sin;
        result[2][2] = cos  + z     * z             * oneMinusCos;
        return result;
    }

    template<float_type T>
    Matrix<T, 4, 4> MatrixRotate(const T& angle, const Vector<T, 3>& axis, const Matrix<T, 4, 4>& matrix)
    {
		return matrix * MatrixRotate(angle, axis);
	}
}
