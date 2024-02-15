#pragma once

/*
#include "Conversion.hpp"
#include "Quaternion.hpp"
#include "Vector.hpp"

namespace Pulsarion::Math
{
	template<float_type T>
	using EulerAngle = Vector<T, 3>;

    template<float_type T>
	EulerAngle<T> EulerAngleConvertToRadians(const EulerAngle<T>& angle)
	{
		return EulerAngle<T>(
			DegreesToRadians(angle.x),
			DegreesToRadians(angle.y),
			DegreesToRadians(angle.z)
		);
	}

	/// <summary>
	/// Converts an euler angle of radians to a quaternion.
	/// </summary>
	/// <typeparam name="T">float_type, can be float, double, or long double</typeparam>
	/// <param name="angle">The euler angle, as a vector3 of radians</param>
	/// <returns>Quaternion representing the euler angle rotation</returns>
	template<float_type T>
	Quaternion<T> FromEulerAngle(const EulerAngle<T>& angle)
	{
		static constexpr auto half = static_cast<T>(0.5);
		const T halfX = angle.x * half;
		const T halfY = angle.y * half;
		const T halfZ = angle.z * half;

		const T cosX = Cos(halfX);
		const T cosY = Cos(halfY);
		const T cosZ = Cos(halfZ);
		const T sinX = Sin(halfX);
		const T sinY = Sin(halfY);
		const T sinZ = Sin(halfZ);


		return Quaternion<T>( // SIMD is not worth it for this, as it requires a lot of copying
			cosX * cosY * cosZ + sinX * sinY * sinZ,
			sinX * cosY * cosZ - cosX * sinY * sinZ,
			cosX * sinY * cosZ + sinX * cosY * sinZ,
			cosX * cosY * sinZ - sinX * sinY * cosZ
		);
	}
}
*/
