#pragma once

// Contains typedefs in the Pulsarion namespace

#include "Vector.hpp"
#include "Matrix.hpp"
#include "MatrixTransform.hpp"
#include "Constants.hpp"
#include "Conversion.hpp"
#include "Quaternion.hpp"

namespace Pulsarion
{
    using Vec2 = Math::Vector<float, 2>;
    using Vec3 = Math::Vector<float, 3>;
    using Vec4 = Math::Vector<float, 4>;
    using Vec2f = Math::Vector<float, 2>;
    using Vec3f = Math::Vector<float, 3>;
    using Vec4f = Math::Vector<float, 4>;
    using Vec2d = Math::Vector<double, 2>;
    using Vec3d = Math::Vector<double, 3>;
    using Vec4d = Math::Vector<double, 4>;
    using Vec2ld = Math::Vector<long double, 2>;
    using Vec3ld = Math::Vector<long double, 3>;
    using Vec4ld = Math::Vector<long double, 4>;

    using float2 = Math::Vector<float, 2>;
    using float3 = Math::Vector<float, 3>;
    using float4 = Math::Vector<float, 4>;
    using double2 = Math::Vector<double, 2>;
    using double3 = Math::Vector<double, 3>;
    using double4 = Math::Vector<double, 4>;
    using ldouble2 = Math::Vector<long double, 2>;
    using ldouble3 = Math::Vector<long double, 3>;
    using ldouble4 = Math::Vector<long double, 4>;

    using Mat4 = Math::Matrix<float, 4, 4>;
    using Mat4f = Math::Matrix<float, 4, 4>;
    using Mat4d = Math::Matrix<double, 4, 4>;
    using Mat4ld = Math::Matrix<long double, 4, 4>;
    using Mat4x4 = Math::Matrix<float, 4, 4>;
    using Mat4x4f = Math::Matrix<float, 4, 4>;
    using Mat4x4d = Math::Matrix<double, 4, 4>;
    using Mat4x4ld = Math::Matrix<long double, 4, 4>;
}
