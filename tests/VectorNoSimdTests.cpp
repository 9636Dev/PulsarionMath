#include <gtest/gtest.h>
#define PULSARION_MATH_DISABLE_SIMD
#include <PulsarionMath/Math.hpp>

using namespace Pulsarion;

class Vector2DNoSimdTest : public ::testing::Test {
protected:
	float2 v1, v2, zeroVector;
	double2 dv1, dv2, dzeroVector;
	ldouble2 ldv1, ldv2, ldzeroVector;

	void SetUp() override {
		v1 = float2(1.0f, 2.0f);
		v2 = float2(3.0f, 4.0f);
		zeroVector = float2(0.0f, 0.0f);

		dv1 = double2(1.0, 2.0);
		dv2 = double2(3.0, 4.0);
		dzeroVector = double2(0.0, 0.0);

		ldv1 = ldouble2(1.0, 2.0);
		ldv2 = ldouble2(3.0, 4.0);
		ldzeroVector = ldouble2(0.0, 0.0);
	}

	static bool IsZeroVector(const float2& vec) {
		return vec.x == 0.0f && vec.y == 0.0f;
	}

	static bool IsZeroVector(const double2& vec) {
		return vec.x == 0.0 && vec.y == 0.0;
	}

	static bool IsZeroVector(const ldouble2& vec) {
		return vec.x == 0.0 && vec.y == 0.0;
	}
};

// Test for division by zero
TEST_F(Vector2DNoSimdTest, HandlesDivisionByZero) {
	auto result1 = v1 / 0.0f;
	EXPECT_TRUE(IsZeroVector(result1));

	auto result2 = dv1 / 0.0;
	EXPECT_TRUE(IsZeroVector(result2));

	auto result3 = ldv1 / 0.0;
	EXPECT_TRUE(IsZeroVector(result3));
}

// Test for normalization
TEST_F(Vector2DNoSimdTest, HandlesNormalization) {
	auto normalizedVec1 = v1.Normalized();
	if (!IsZeroVector(v1)) {
		float magnitude = normalizedVec1.Magnitude();
		EXPECT_NEAR(magnitude, 1.0f, 1e-6f);
	}
	else {
		EXPECT_TRUE(IsZeroVector(normalizedVec1));
	}

	auto normalizedVec2 = dv1.Normalized();
	if (!IsZeroVector(dv1)) {
		double magnitude = normalizedVec2.Magnitude();
		EXPECT_NEAR(magnitude, 1.0, 1e-6);
	}
	else {
		EXPECT_TRUE(IsZeroVector(normalizedVec2));
	}

	auto normalizedVec3 = ldv1.Normalized();
	if (!IsZeroVector(ldv1)) {
		long double magnitude = normalizedVec3.Magnitude();
		EXPECT_NEAR(magnitude, 1.0, 1e-6);
	}
	else {
		EXPECT_TRUE(IsZeroVector(normalizedVec3));
	}
}

TEST_F(Vector2DNoSimdTest, HandlesScalerAddition)
{
	auto result1 = v1 + 1.0f;
	EXPECT_FLOAT_EQ(result1.x, 2.0f);
	EXPECT_FLOAT_EQ(result1.y, 3.0f);

	auto result2 = dv1 + 1.0;
	EXPECT_DOUBLE_EQ(result2.x, 2.0);
	EXPECT_DOUBLE_EQ(result2.y, 3.0);

	auto result3 = ldv1 + 1.0;
	EXPECT_NEAR(result3.x, 2.0, 1e-5);
	EXPECT_NEAR(result3.y, 3.0, 1e-5);
}

TEST_F(Vector2DNoSimdTest, HandlesScalerSubtraction)
{
	auto result1 = v1 - 1.0f;
	EXPECT_FLOAT_EQ(result1.x, 0.0f);
	EXPECT_FLOAT_EQ(result1.y, 1.0f);

	auto result2 = dv1 - 1.0;
	EXPECT_DOUBLE_EQ(result2.x, 0.0);
	EXPECT_DOUBLE_EQ(result2.y, 1.0);

	auto result3 = ldv1 - 1.0;
	EXPECT_NEAR(result3.x, 0.0, 1e-5);
	EXPECT_NEAR(result3.y, 1.0, 1e-5);
}

TEST_F(Vector2DNoSimdTest, HandlesScalerMultiplication)
{
	auto result1 = v1 * 2.0f;
	EXPECT_FLOAT_EQ(result1.x, 2.0f);
	EXPECT_FLOAT_EQ(result1.y, 4.0f);

	auto result2 = dv1 * 2.0;
	EXPECT_DOUBLE_EQ(result2.x, 2.0);
	EXPECT_DOUBLE_EQ(result2.y, 4.0);

	auto result3 = ldv1 * 2.0;
	EXPECT_NEAR(result3.x, 2.0, 1e-5);
	EXPECT_NEAR(result3.y, 4.0, 1e-5);
}

TEST_F(Vector2DNoSimdTest, HandlesScalerDivision)
{
	auto result1 = v1 / 2.0f;
	EXPECT_FLOAT_EQ(result1.x, 0.5f);
	EXPECT_FLOAT_EQ(result1.y, 1.0f);

	auto result2 = dv1 / 2.0;
	EXPECT_DOUBLE_EQ(result2.x, 0.5);
	EXPECT_DOUBLE_EQ(result2.y, 1.0);

	auto result3 = ldv1 / 2.0;
	EXPECT_NEAR(result3.x, 0.5, 1e-5);
	EXPECT_NEAR(result3.y, 1.0, 1e-5);
}

TEST_F(Vector2DNoSimdTest, HandlesVectorAddition)
{
	auto result1 = v1 + v2;
	EXPECT_FLOAT_EQ(result1.x, 4.0f);
	EXPECT_FLOAT_EQ(result1.y, 6.0f);

	auto result2 = dv1 + dv2;
	EXPECT_DOUBLE_EQ(result2.x, 4.0);
	EXPECT_DOUBLE_EQ(result2.y, 6.0);

	auto result3 = ldv1 + ldv2;
	EXPECT_NEAR(result3.x, 4.0, 1e-5);
	EXPECT_NEAR(result3.y, 6.0, 1e-5);
}

TEST_F(Vector2DNoSimdTest, HandlesVectorSubtraction)
{
	auto result1 = v1 - v2;
	EXPECT_FLOAT_EQ(result1.x, -2.0f);
	EXPECT_FLOAT_EQ(result1.y, -2.0f);

	auto result2 = dv1 - dv2;
	EXPECT_DOUBLE_EQ(result2.x, -2.0);
	EXPECT_DOUBLE_EQ(result2.y, -2.0);

	auto result3 = ldv1 - ldv2;
	EXPECT_NEAR(result3.x, -2.0, 1e-5);
	EXPECT_NEAR(result3.y, -2.0, 1e-5);
}

TEST_F(Vector2DNoSimdTest, HandlesVectorMultiplication)
{
	auto result1 = v1 * v2;
	EXPECT_FLOAT_EQ(result1.x, 3.0f);
	EXPECT_FLOAT_EQ(result1.y, 8.0f);

	auto result2 = dv1 * dv2;
	EXPECT_DOUBLE_EQ(result2.x, 3.0);
	EXPECT_DOUBLE_EQ(result2.y, 8.0);

	auto result3 = ldv1 * ldv2;
	EXPECT_NEAR(result3.x, 3.0, 1e-5);
	EXPECT_NEAR(result3.y, 8.0, 1e-5);
}

TEST_F(Vector2DNoSimdTest, HandlesVectorDivision)
{
	auto result1 = v1 / v2;
	EXPECT_FLOAT_EQ(result1.x, 1.0f / 3.0f);
	EXPECT_FLOAT_EQ(result1.y, 2.0f / 4.0f);

	auto result2 = dv1 / dv2;
	EXPECT_DOUBLE_EQ(result2.x, 1.0 / 3.0);
	EXPECT_DOUBLE_EQ(result2.y, 2.0 / 4.0);

	auto result3 = ldv1 / ldv2;
	EXPECT_NEAR(result3.x, 1.0 / 3.0, 1e-5);
	EXPECT_NEAR(result3.y, 2.0 / 4.0, 1e-5);
}

TEST_F(Vector2DNoSimdTest, HandlesVectorAdditionAssignment)
{
	auto result1 = v1;
	result1 += v2;
	EXPECT_FLOAT_EQ(result1.x, 4.0f);
	EXPECT_FLOAT_EQ(result1.y, 6.0f);

	auto result2 = dv1;
	result2 += dv2;
	EXPECT_DOUBLE_EQ(result2.x, 4.0);
	EXPECT_DOUBLE_EQ(result2.y, 6.0);

	auto result3 = ldv1;
	result3 += ldv2;
	EXPECT_NEAR(result3.x, 4.0, 1e-5);
	EXPECT_NEAR(result3.y, 6.0, 1e-5);
}

TEST_F(Vector2DNoSimdTest, HandlesVectorSubtractionAssignment)
{
	auto result1 = v1;
	result1 -= v2;
	EXPECT_FLOAT_EQ(result1.x, -2.0f);
	EXPECT_FLOAT_EQ(result1.y, -2.0f);

	auto result2 = dv1;
	result2 -= dv2;
	EXPECT_DOUBLE_EQ(result2.x, -2.0);
	EXPECT_DOUBLE_EQ(result2.y, -2.0);

	auto result3 = ldv1;
	result3 -= ldv2;
	EXPECT_NEAR(result3.x, -2.0, 1e-5);
	EXPECT_NEAR(result3.y, -2.0, 1e-5);
}

TEST_F(Vector2DNoSimdTest, HandlesVectorMultiplicationAssignment)
{
	auto result1 = v1;
	result1 *= v2;
	EXPECT_FLOAT_EQ(result1.x, 3.0f);
	EXPECT_FLOAT_EQ(result1.y, 8.0f);

	auto result2 = dv1;
	result2 *= dv2;
	EXPECT_DOUBLE_EQ(result2.x, 3.0);
	EXPECT_DOUBLE_EQ(result2.y, 8.0);

	auto result3 = ldv1;
	result3 *= ldv2;
	EXPECT_NEAR(result3.x, 3.0, 1e-5);
	EXPECT_NEAR(result3.y, 8.0, 1e-5);
}

TEST_F(Vector2DNoSimdTest, HandlesVectorDivisionAssignment)
{
	auto result1 = v1;
	result1 /= v2;
	EXPECT_FLOAT_EQ(result1.x, 1.0f / 3.0f);
	EXPECT_FLOAT_EQ(result1.y, 2.0f / 4.0f);

	auto result2 = dv1;
	result2 /= dv2;
	EXPECT_DOUBLE_EQ(result2.x, 1.0 / 3.0);
	EXPECT_DOUBLE_EQ(result2.y, 2.0 / 4.0);

	auto result3 = ldv1;
	result3 /= ldv2;
	EXPECT_NEAR(result3.x, 1.0 / 3.0, 1e-5);
	EXPECT_NEAR(result3.y, 2.0 / 4.0, 1e-5);
}

TEST_F(Vector2DNoSimdTest, HandlesDotProduct)
{
	auto result1 = v1.Dot(v2);
	EXPECT_NEAR(result1, 11.0f, 1e-5); // 1 * 3 + 2 * 4

	auto result2 = dv1.Dot(dv2);
	EXPECT_NEAR(result2, 11.0, 1e-5);

	auto result3 = ldv1.Dot(ldv2);
	EXPECT_NEAR(result3, 11.0, 1e-5);
}

TEST_F(Vector2DNoSimdTest, HandlesCrossProduct)
{
	auto result1 = v1.Cross(v2);
	EXPECT_FLOAT_EQ(result1, -2.0f); // 1 * 4 - 2 * 3

	auto result2 = dv1.Cross(dv2);
	EXPECT_DOUBLE_EQ(result2, -2.0);

	auto result3 = ldv1.Cross(ldv2);
	EXPECT_NEAR(result3, -2.0, 1e-5);
}

class Vector3DNoSimdTest : public ::testing::Test {
protected:
	float3 v1, v2, zeroVector;
	double3 dv1, dv2, dzeroVector;
	ldouble3 ldv1, ldv2, ldzeroVector;

	void SetUp() override {
		v1 = float3(1.0f, 2.0f, 3.0f);
		v2 = float3(4.0f, 5.0f, 6.0f);
		zeroVector = float3(0.0f, 0.0f, 0.0f);

		dv1 = double3(1.0, 2.0, 3.0);
		dv2 = double3(4.0, 5.0, 6.0);
		dzeroVector = double3(0.0, 0.0, 0.0);

		ldv1 = ldouble3(1.0, 2.0, 3.0);
		ldv2 = ldouble3(4.0, 5.0, 6.0);
		ldzeroVector = ldouble3(0.0, 0.0, 0.0);
	}

	static bool IsZeroVector(const float3& vec) {
		return vec.x == 0.0f && vec.y == 0.0f && vec.z == 0.0f;
	}

	static bool IsZeroVector(const double3& vec) {
		return vec.x == 0.0 && vec.y == 0.0 && vec.z == 0.0;
	}

	static bool IsZeroVector(const ldouble3& vec) {
		return vec.x == 0.0 && vec.y == 0.0 && vec.z == 0.0;
	}
};

// Test for division by zero
TEST_F(Vector3DNoSimdTest, HandlesDivisionByZero) {
	auto result1 = v1 / 0.0f;
	EXPECT_TRUE(IsZeroVector(result1));

	auto result2 = dv1 / 0.0;
	EXPECT_TRUE(IsZeroVector(result2));
}

// Test for normalization
TEST_F(Vector3DNoSimdTest, HandlesNormalization) {
	auto normalizedVec1 = v1.Normalized();
	if (!IsZeroVector(v1)) {
		float magnitude = normalizedVec1.Magnitude();
		EXPECT_NEAR(magnitude, 1.0f, 1e-6f);
	}
	else {
		EXPECT_TRUE(IsZeroVector(normalizedVec1));
	}

	auto normalizedVec2 = dv1.Normalized();
	if (!IsZeroVector(dv1)) {
		double magnitude = normalizedVec2.Magnitude();
		EXPECT_NEAR(magnitude, 1.0, 1e-6);
	}
	else {
		EXPECT_TRUE(IsZeroVector(normalizedVec2));
	}

	auto normalizedVec3 = ldv1.Normalized();
	if (!IsZeroVector(ldv1)) {
		long double magnitude = normalizedVec3.Magnitude();
		EXPECT_NEAR(magnitude, 1.0, 1e-6);
	}
	else {
		EXPECT_TRUE(IsZeroVector(normalizedVec3));
	}
}

TEST_F(Vector3DNoSimdTest, HandlesScalerAddition)
{
	auto result1 = v1 + 1.0f;
	EXPECT_FLOAT_EQ(result1.x, 2.0f);
	EXPECT_FLOAT_EQ(result1.y, 3.0f);
	EXPECT_FLOAT_EQ(result1.z, 4.0f);

	auto result2 = dv1 + 1.0;
	EXPECT_DOUBLE_EQ(result2.x, 2.0);
	EXPECT_DOUBLE_EQ(result2.y, 3.0);
	EXPECT_DOUBLE_EQ(result2.z, 4.0);

	auto result3 = ldv1 + 1.0;
	EXPECT_NEAR(result3.x, 2.0, 1e-5);
	EXPECT_NEAR(result3.y, 3.0, 1e-5);
	EXPECT_NEAR(result3.z, 4.0, 1e-5);
}

TEST_F(Vector3DNoSimdTest, HandlesScalerSubtraction)
{
	auto result = v1 - 1.0f;
	EXPECT_FLOAT_EQ(result.x, 0.0f);
	EXPECT_FLOAT_EQ(result.y, 1.0f);
	EXPECT_FLOAT_EQ(result.z, 2.0f);

	auto result2 = dv1 - 1.0;
	EXPECT_DOUBLE_EQ(result2.x, 0.0);
	EXPECT_DOUBLE_EQ(result2.y, 1.0);
	EXPECT_DOUBLE_EQ(result2.z, 2.0);

	auto result3 = ldv1 - 1.0;
	EXPECT_NEAR(result3.x, 0.0, 1e-5);
	EXPECT_NEAR(result3.y, 1.0, 1e-5);
	EXPECT_NEAR(result3.z, 2.0, 1e-5);
}

TEST_F(Vector3DNoSimdTest, HandlesScalerMultiplication)
{
	auto result1 = v1 * 2.0f;
	EXPECT_FLOAT_EQ(result1.x, 2.0f);
	EXPECT_FLOAT_EQ(result1.y, 4.0f);
	EXPECT_FLOAT_EQ(result1.z, 6.0f);

	auto result2 = dv1 * 2.0;
	EXPECT_DOUBLE_EQ(result2.x, 2.0);
	EXPECT_DOUBLE_EQ(result2.y, 4.0);
	EXPECT_DOUBLE_EQ(result2.z, 6.0);

	auto result3 = ldv1 * 2.0;
	EXPECT_NEAR(result3.x, 2.0, 1e-5);
	EXPECT_NEAR(result3.y, 4.0, 1e-5);
	EXPECT_NEAR(result3.z, 6.0, 1e-5);
}

TEST_F(Vector3DNoSimdTest, HandlesScalerDivision)
{
	auto result1 = v1 / 2.0f;
	EXPECT_FLOAT_EQ(result1.x, 0.5f);
	EXPECT_FLOAT_EQ(result1.y, 1.0f);
	EXPECT_FLOAT_EQ(result1.z, 1.5f);

	auto result2 = dv1 / 2.0;
	EXPECT_DOUBLE_EQ(result2.x, 0.5);
	EXPECT_DOUBLE_EQ(result2.y, 1.0);
	EXPECT_DOUBLE_EQ(result2.z, 1.5);

	auto result3 = ldv1 / 2.0;
	EXPECT_NEAR(result3.x, 0.5, 1e-5);
	EXPECT_NEAR(result3.y, 1.0, 1e-5);
	EXPECT_NEAR(result3.z, 1.5, 1e-5);
}

TEST_F(Vector3DNoSimdTest, HandlesVectorAddition)
{
	auto result1 = v1 + v2;
	EXPECT_FLOAT_EQ(result1.x, 5.0f);
	EXPECT_FLOAT_EQ(result1.y, 7.0f);
	EXPECT_FLOAT_EQ(result1.z, 9.0f);

	auto result2 = dv1 + dv2;
	EXPECT_DOUBLE_EQ(result2.x, 5.0);
	EXPECT_DOUBLE_EQ(result2.y, 7.0);
	EXPECT_DOUBLE_EQ(result2.z, 9.0);

	auto result3 = ldv1 + ldv2;
	EXPECT_NEAR(result3.x, 5.0, 1e-5);
	EXPECT_NEAR(result3.y, 7.0, 1e-5);
	EXPECT_NEAR(result3.z, 9.0, 1e-5);
}

TEST_F(Vector3DNoSimdTest, HandlesVectorSubtraction)
{
	auto result1 = v1 - v2;
	EXPECT_FLOAT_EQ(result1.x, -3.0f);
	EXPECT_FLOAT_EQ(result1.y, -3.0f);
	EXPECT_FLOAT_EQ(result1.z, -3.0f);

	auto result2 = dv1 - dv2;
	EXPECT_DOUBLE_EQ(result2.x, -3.0);
	EXPECT_DOUBLE_EQ(result2.y, -3.0);
	EXPECT_DOUBLE_EQ(result2.z, -3.0);

	auto result3 = ldv1 - ldv2;
	EXPECT_NEAR(result3.x, -3.0, 1e-5);
	EXPECT_NEAR(result3.y, -3.0, 1e-5);
	EXPECT_NEAR(result3.z, -3.0, 1e-5);
}

TEST_F(Vector3DNoSimdTest, HandlesVectorMultiplication)
{
	auto result1 = v1 * v2;
	EXPECT_FLOAT_EQ(result1.x, 4.0f);
	EXPECT_FLOAT_EQ(result1.y, 10.0f);
	EXPECT_FLOAT_EQ(result1.z, 18.0f);

	auto result2 = dv1 * dv2;
	EXPECT_DOUBLE_EQ(result2.x, 4.0);
	EXPECT_DOUBLE_EQ(result2.y, 10.0);
	EXPECT_DOUBLE_EQ(result2.z, 18.0);

	auto result3 = ldv1 * ldv2;
	EXPECT_NEAR(result3.x, 4.0, 1e-5);
	EXPECT_NEAR(result3.y, 10.0, 1e-5);
	EXPECT_NEAR(result3.z, 18.0, 1e-5);
}

TEST_F(Vector3DNoSimdTest, HandlesVectorDivision)
{
	auto result1 = v1 / v2;
	EXPECT_FLOAT_EQ(result1.x, 1.0f / 4.0f);
	EXPECT_FLOAT_EQ(result1.y, 2.0f / 5.0f);
	EXPECT_FLOAT_EQ(result1.z, 3.0f / 6.0f);

	auto result2 = dv1 / dv2;
	EXPECT_DOUBLE_EQ(result2.x, 1.0 / 4.0);
	EXPECT_DOUBLE_EQ(result2.y, 2.0 / 5.0);
	EXPECT_DOUBLE_EQ(result2.z, 3.0 / 6.0);

	auto result3 = ldv1 / ldv2;
	EXPECT_NEAR(result3.x, 1.0 / 4.0, 1e-5);
	EXPECT_NEAR(result3.y, 2.0 / 5.0, 1e-5);
	EXPECT_NEAR(result3.z, 3.0 / 6.0, 1e-5);
}

TEST_F(Vector3DNoSimdTest, HandlesVectorAdditionAssignment)
{
	auto result = v1;
	result += v2;
	EXPECT_FLOAT_EQ(result.x, 5.0f);
	EXPECT_FLOAT_EQ(result.y, 7.0f);
	EXPECT_FLOAT_EQ(result.z, 9.0f);

	auto result2 = dv1;
	result2 += dv2;
	EXPECT_DOUBLE_EQ(result2.x, 5.0);
	EXPECT_DOUBLE_EQ(result2.y, 7.0);
	EXPECT_DOUBLE_EQ(result2.z, 9.0);

	auto result3 = ldv1;
	result3 += ldv2;
	EXPECT_NEAR(result3.x, 5.0, 1e-5);
	EXPECT_NEAR(result3.y, 7.0, 1e-5);
	EXPECT_NEAR(result3.z, 9.0, 1e-5);
}

TEST_F(Vector3DNoSimdTest, HandlesVectorSubtractionAssignment)
{
	auto result1 = v1;
	result1 -= v2;
	EXPECT_FLOAT_EQ(result1.x, -3.0f);
	EXPECT_FLOAT_EQ(result1.y, -3.0f);
	EXPECT_FLOAT_EQ(result1.z, -3.0f);

	auto result2 = dv1;
	result2 -= dv2;
	EXPECT_DOUBLE_EQ(result2.x, -3.0);
	EXPECT_DOUBLE_EQ(result2.y, -3.0);
	EXPECT_DOUBLE_EQ(result2.z, -3.0);

	auto result3 = ldv1;
	result3 -= ldv2;
	EXPECT_NEAR(result3.x, -3.0, 1e-5);
	EXPECT_NEAR(result3.y, -3.0, 1e-5);
	EXPECT_NEAR(result3.z, -3.0, 1e-5);
}

TEST_F(Vector3DNoSimdTest, HandlesVectorMultiplicationAssignment)
{
	auto result1 = v1;
	result1 *= v2;
	EXPECT_FLOAT_EQ(result1.x, 4.0f);
	EXPECT_FLOAT_EQ(result1.y, 10.0f);
	EXPECT_FLOAT_EQ(result1.z, 18.0f);

	auto result2 = dv1;
	result2 *= dv2;
	EXPECT_DOUBLE_EQ(result2.x, 4.0);
	EXPECT_DOUBLE_EQ(result2.y, 10.0);
	EXPECT_DOUBLE_EQ(result2.z, 18.0);

	auto result3 = ldv1;
	result3 *= ldv2;
	EXPECT_NEAR(result3.x, 4.0, 1e-5);
	EXPECT_NEAR(result3.y, 10.0, 1e-5);
	EXPECT_NEAR(result3.z, 18.0, 1e-5);
}

TEST_F(Vector3DNoSimdTest, HandlesVectorDivisionAssignment)
{
	auto result1 = v1;
	result1 /= v2;
	EXPECT_FLOAT_EQ(result1.x, 1.0f / 4.0f);
	EXPECT_FLOAT_EQ(result1.y, 2.0f / 5.0f);
	EXPECT_FLOAT_EQ(result1.z, 3.0f / 6.0f);

	auto result2 = dv1;
	result2 /= dv2;
	EXPECT_DOUBLE_EQ(result2.x, 1.0 / 4.0);
	EXPECT_DOUBLE_EQ(result2.y, 2.0 / 5.0);
	EXPECT_DOUBLE_EQ(result2.z, 3.0 / 6.0);

	auto result3 = ldv1;
	result3 /= ldv2;
	EXPECT_NEAR(result3.x, 1.0 / 4.0, 1e-5);
	EXPECT_NEAR(result3.y, 2.0 / 5.0, 1e-5);
	EXPECT_NEAR(result3.z, 3.0 / 6.0, 1e-5);
}

TEST_F(Vector3DNoSimdTest, HandlesDotProduct)
{
	auto result1 = v1.Dot(v2);
	EXPECT_NEAR(result1, 32.0f, 1e-5); // 1 * 4 + 2 * 5 + 3 * 6

	auto result2 = dv1.Dot(dv2);
	EXPECT_NEAR(result2, 32.0, 1e-5);

	auto result3 = ldv1.Dot(ldv2);
	EXPECT_NEAR(result3, 32.0, 1e-5);
}

TEST_F(Vector3DNoSimdTest, HandlesCrossProduct)
{
	auto result = v1.Cross(v2);
	EXPECT_FLOAT_EQ(result.x, -3.0f);
	EXPECT_FLOAT_EQ(result.y, 6.0f);
	EXPECT_FLOAT_EQ(result.z, -3.0f);

	auto result2 = dv1.Cross(dv2);
	EXPECT_DOUBLE_EQ(result2.x, -3.0);
	EXPECT_DOUBLE_EQ(result2.y, 6.0);
	EXPECT_DOUBLE_EQ(result2.z, -3.0);

	auto result3 = ldv1.Cross(ldv2);
	EXPECT_NEAR(result3.x, -3.0, 1e-5);
	EXPECT_NEAR(result3.y, 6.0, 1e-5);
	EXPECT_NEAR(result3.z, -3.0, 1e-5);
}

class Vector4DNoSimdTest : public ::testing::Test {
protected:
	float4 v1, v2, zeroVector;
	double4 dv1, dv2, dzeroVector;
	ldouble4 ldv1, ldv2, ldzeroVector;

	void SetUp() override {
		v1 = float4(1.0f, 2.0f, 3.0f, 4.0f);
		v2 = float4(5.0f, 6.0f, 7.0f, 8.0f);
		zeroVector = float4(0.0f, 0.0f, 0.0f, 0.0f);

		dv1 = double4(1.0, 2.0, 3.0, 4.0);
		dv2 = double4(5.0, 6.0, 7.0, 8.0);
		dzeroVector = double4(0.0, 0.0, 0.0, 0.0);

		ldv1 = ldouble4(1.0, 2.0, 3.0, 4.0);
		ldv2 = ldouble4(5.0, 6.0, 7.0, 8.0);
		ldzeroVector = ldouble4(0.0, 0.0, 0.0, 0.0);
	}

	static bool IsZeroVector(const float4& vec) {
		return vec.x == 0.0f && vec.y == 0.0f && vec.z == 0.0f && vec.w == 0.0f;
	}

	static bool IsZeroVector(const double4& vec) {
		return vec.x == 0.0 && vec.y == 0.0 && vec.z == 0.0 && vec.w == 0.0f;
	}

	static bool IsZeroVector(const ldouble4& vec) {
		return vec.x == 0.0 && vec.y == 0.0 && vec.z == 0.0 && vec.w == 0.0f;
	}
};

// Test for division by zero
TEST_F(Vector4DNoSimdTest, HandlesDivisionByZero) {
	auto result1 = v1 / 0.0f;
	EXPECT_TRUE(IsZeroVector(result1));

	auto result2 = dv1 / 0.0;
	EXPECT_TRUE(IsZeroVector(result2));
}

// Test for normalization
TEST_F(Vector4DNoSimdTest, HandlesNormalization) {
	auto normalizedVec1 = v1.Normalized();
	if (!IsZeroVector(v1)) {
		float magnitude = normalizedVec1.Magnitude();
		EXPECT_NEAR(magnitude, 1.0f, 1e-6f);
	}
	else {
		EXPECT_TRUE(IsZeroVector(normalizedVec1));
	}

	auto normalizedVec2 = dv1.Normalized();
	if (!IsZeroVector(dv1)) {
		double magnitude = normalizedVec2.Magnitude();
		EXPECT_NEAR(magnitude, 1.0, 1e-6);
	}
	else {
		EXPECT_TRUE(IsZeroVector(normalizedVec2));
	}

	auto normalizedVec3 = ldv1.Normalized();
	if (!IsZeroVector(ldv1)) {
		long double magnitude = normalizedVec3.Magnitude();
		EXPECT_NEAR(magnitude, 1.0, 1e-6);
	}
	else {
		EXPECT_TRUE(IsZeroVector(normalizedVec3));
	}
}

TEST_F(Vector4DNoSimdTest, HandlesScalerAddition)
{
	auto result1 = v1 + 1.0f;
	EXPECT_FLOAT_EQ(result1.x, 2.0f);
	EXPECT_FLOAT_EQ(result1.y, 3.0f);
	EXPECT_FLOAT_EQ(result1.z, 4.0f);
	EXPECT_FLOAT_EQ(result1.w, 5.0f);

	auto result2 = dv1 + 1.0;
	EXPECT_DOUBLE_EQ(result2.x, 2.0);
	EXPECT_DOUBLE_EQ(result2.y, 3.0);
	EXPECT_DOUBLE_EQ(result2.z, 4.0);
	EXPECT_DOUBLE_EQ(result2.w, 5.0);

	auto result3 = ldv1 + 1.0;
	EXPECT_NEAR(result3.x, 2.0, 1e-5);
	EXPECT_NEAR(result3.y, 3.0, 1e-5);
	EXPECT_NEAR(result3.z, 4.0, 1e-5);
	EXPECT_NEAR(result3.w, 5.0, 1e-5);
}

TEST_F(Vector4DNoSimdTest, HandlesScalerSubtraction)
{
	auto result = v1 - 1.0f;
	EXPECT_FLOAT_EQ(result.x, 0.0f);
	EXPECT_FLOAT_EQ(result.y, 1.0f);
	EXPECT_FLOAT_EQ(result.z, 2.0f);
	EXPECT_FLOAT_EQ(result.w, 3.0f);

	auto result2 = dv1 - 1.0;
	EXPECT_DOUBLE_EQ(result2.x, 0.0);
	EXPECT_DOUBLE_EQ(result2.y, 1.0);
	EXPECT_DOUBLE_EQ(result2.z, 2.0);
	EXPECT_DOUBLE_EQ(result2.w, 3.0);

	auto result3 = ldv1 - 1.0;
	EXPECT_NEAR(result3.x, 0.0, 1e-5);
	EXPECT_NEAR(result3.y, 1.0, 1e-5);
	EXPECT_NEAR(result3.z, 2.0, 1e-5);
	EXPECT_NEAR(result3.w, 3.0, 1e-5);
}

TEST_F(Vector4DNoSimdTest, HandlesScalerMultiplication)
{
	auto result1 = v1 * 2.0f;
	EXPECT_FLOAT_EQ(result1.x, 2.0f);
	EXPECT_FLOAT_EQ(result1.y, 4.0f);
	EXPECT_FLOAT_EQ(result1.z, 6.0f);
	EXPECT_FLOAT_EQ(result1.w, 8.0f);

	auto result2 = dv1 * 2.0;
	EXPECT_DOUBLE_EQ(result2.x, 2.0);
	EXPECT_DOUBLE_EQ(result2.y, 4.0);
	EXPECT_DOUBLE_EQ(result2.z, 6.0);
	EXPECT_DOUBLE_EQ(result2.w, 8.0);

	auto result3 = ldv1 * 2.0;
	EXPECT_NEAR(result3.x, 2.0, 1e-5);
	EXPECT_NEAR(result3.y, 4.0, 1e-5);
	EXPECT_NEAR(result3.z, 6.0, 1e-5);
	EXPECT_NEAR(result3.w, 8.0, 1e-5);
}

TEST_F(Vector4DNoSimdTest, HandlesScalerDivision)
{
	auto result1 = v1 / 2.0f;
	EXPECT_FLOAT_EQ(result1.x, 0.5f);
	EXPECT_FLOAT_EQ(result1.y, 1.0f);
	EXPECT_FLOAT_EQ(result1.z, 1.5f);
	EXPECT_FLOAT_EQ(result1.w, 2.0f);

	auto result2 = dv1 / 2.0;
	EXPECT_DOUBLE_EQ(result2.x, 0.5);
	EXPECT_DOUBLE_EQ(result2.y, 1.0);
	EXPECT_DOUBLE_EQ(result2.z, 1.5);
	EXPECT_DOUBLE_EQ(result2.w, 2.0);

	auto result3 = ldv1 / 2.0;
	EXPECT_NEAR(result3.x, 0.5, 1e-5);
	EXPECT_NEAR(result3.y, 1.0, 1e-5);
	EXPECT_NEAR(result3.z, 1.5, 1e-5);
	EXPECT_NEAR(result3.w, 2.0, 1e-5);
}

TEST_F(Vector4DNoSimdTest, HandlesVectorAddition)
{
	auto result1 = v1 + v2;
	EXPECT_FLOAT_EQ(result1.x, 6.0f);
	EXPECT_FLOAT_EQ(result1.y, 8.0f);
	EXPECT_FLOAT_EQ(result1.z, 10.0f);
	EXPECT_FLOAT_EQ(result1.w, 12.0f);

	auto result2 = dv1 + dv2;
	EXPECT_DOUBLE_EQ(result2.x, 6.0);
	EXPECT_DOUBLE_EQ(result2.y, 8.0);
	EXPECT_DOUBLE_EQ(result2.z, 10.0);
	EXPECT_DOUBLE_EQ(result2.w, 12.0);

	auto result3 = ldv1 + ldv2;
	EXPECT_NEAR(result3.x, 6.0, 1e-5);
	EXPECT_NEAR(result3.y, 8.0, 1e-5);
	EXPECT_NEAR(result3.z, 10.0, 1e-5);
	EXPECT_NEAR(result3.w, 12.0, 1e-5);

}

TEST_F(Vector4DNoSimdTest, HandlesVectorSubtraction)
{
	auto result1 = v1 - v2;
	EXPECT_FLOAT_EQ(result1.x, -4.0f);
	EXPECT_FLOAT_EQ(result1.y, -4.0f);
	EXPECT_FLOAT_EQ(result1.z, -4.0f);
	EXPECT_FLOAT_EQ(result1.w, -4.0f);

	auto result2 = dv1 - dv2;
	EXPECT_DOUBLE_EQ(result2.x, -4.0);
	EXPECT_DOUBLE_EQ(result2.y, -4.0);
	EXPECT_DOUBLE_EQ(result2.z, -4.0);
	EXPECT_DOUBLE_EQ(result2.w, -4.0);

	auto result3 = ldv1 - ldv2;
	EXPECT_NEAR(result3.x, -4.0, 1e-5);
	EXPECT_NEAR(result3.y, -4.0, 1e-5);
	EXPECT_NEAR(result3.z, -4.0, 1e-5);
	EXPECT_NEAR(result3.w, -4.0, 1e-5);
}

TEST_F(Vector4DNoSimdTest, HandlesVectorMultiplication)
{
	auto result1 = v1 * v2;
	EXPECT_FLOAT_EQ(result1.x, 5.0f);
	EXPECT_FLOAT_EQ(result1.y, 12.0f);
	EXPECT_FLOAT_EQ(result1.z, 21.0f);
	EXPECT_FLOAT_EQ(result1.w, 32.0f);

	auto result2 = dv1 * dv2;
	EXPECT_DOUBLE_EQ(result2.x, 5.0);
	EXPECT_DOUBLE_EQ(result2.y, 12.0);
	EXPECT_DOUBLE_EQ(result2.z, 21.0);
	EXPECT_DOUBLE_EQ(result2.w, 32.0);

	auto result3 = ldv1 * ldv2;
	EXPECT_NEAR(result3.x, 5.0, 1e-5);
	EXPECT_NEAR(result3.y, 12.0, 1e-5);
	EXPECT_NEAR(result3.z, 21.0, 1e-5);
	EXPECT_NEAR(result3.w, 32.0, 1e-5);
}

TEST_F(Vector4DNoSimdTest, HandlesVectorDivision)
{
	auto result1 = v1 / v2;
	EXPECT_FLOAT_EQ(result1.x, 1.0f / 5.0f);
	EXPECT_FLOAT_EQ(result1.y, 2.0f / 6.0f);
	EXPECT_FLOAT_EQ(result1.z, 3.0f / 7.0f);
	EXPECT_FLOAT_EQ(result1.w, 4.0f / 8.0f);

	auto result2 = dv1 / dv2;
	EXPECT_DOUBLE_EQ(result2.x, 1.0 / 5.0);
	EXPECT_DOUBLE_EQ(result2.y, 2.0 / 6.0);
	EXPECT_DOUBLE_EQ(result2.z, 3.0 / 7.0);
	EXPECT_DOUBLE_EQ(result2.w, 4.0 / 8.0);

	auto result3 = ldv1 / ldv2;
	EXPECT_NEAR(result3.x, 1.0 / 5.0, 1e-5);
	EXPECT_NEAR(result3.y, 2.0 / 6.0, 1e-5);
	EXPECT_NEAR(result3.z, 3.0 / 7.0, 1e-5);
	EXPECT_NEAR(result3.w, 4.0 / 8.0, 1e-5);
}

TEST_F(Vector4DNoSimdTest, HandlesVectorAdditionAssignment)
{
	auto result = v1;
	result += v2;
	EXPECT_FLOAT_EQ(result.x, 6.0f);
	EXPECT_FLOAT_EQ(result.y, 8.0f);
	EXPECT_FLOAT_EQ(result.z, 10.0f);
	EXPECT_FLOAT_EQ(result.w, 12.0f);

	auto result2 = dv1;
	result2 += dv2;
	EXPECT_DOUBLE_EQ(result2.x, 6.0);
	EXPECT_DOUBLE_EQ(result2.y, 8.0);
	EXPECT_DOUBLE_EQ(result2.z, 10.0);
	EXPECT_DOUBLE_EQ(result2.w, 12.0);

	auto result3 = ldv1;
	result3 += ldv2;
	EXPECT_NEAR(result3.x, 6.0, 1e-5);
	EXPECT_NEAR(result3.y, 8.0, 1e-5);
	EXPECT_NEAR(result3.z, 10.0, 1e-5);
	EXPECT_NEAR(result3.w, 12.0, 1e-5);
}

TEST_F(Vector4DNoSimdTest, HandlesVectorSubtractionAssignment)
{
	auto result1 = v1;
	result1 -= v2;
	EXPECT_FLOAT_EQ(result1.x, -4.0f);
	EXPECT_FLOAT_EQ(result1.y, -4.0f);
	EXPECT_FLOAT_EQ(result1.z, -4.0f);
	EXPECT_FLOAT_EQ(result1.w, -4.0f);

	auto result2 = dv1;
	result2 -= dv2;
	EXPECT_DOUBLE_EQ(result2.x, -4.0);
	EXPECT_DOUBLE_EQ(result2.y, -4.0);
	EXPECT_DOUBLE_EQ(result2.z, -4.0);
	EXPECT_DOUBLE_EQ(result2.w, -4.0);

	auto result3 = ldv1;
	result3 -= ldv2;
	EXPECT_NEAR(result3.x, -4.0, 1e-5);
	EXPECT_NEAR(result3.y, -4.0, 1e-5);
	EXPECT_NEAR(result3.z, -4.0, 1e-5);
	EXPECT_NEAR(result3.w, -4.0, 1e-5);
}

TEST_F(Vector4DNoSimdTest, HandlesVectorMultiplicationAssignment)
{
	auto result1 = v1;
	result1 *= v2;
	EXPECT_FLOAT_EQ(result1.x, 5.0f);
	EXPECT_FLOAT_EQ(result1.y, 12.0f);
	EXPECT_FLOAT_EQ(result1.z, 21.0f);
	EXPECT_FLOAT_EQ(result1.w, 32.0f);

	auto result2 = dv1;
	result2 *= dv2;
	EXPECT_DOUBLE_EQ(result2.x, 5.0);
	EXPECT_DOUBLE_EQ(result2.y, 12.0);
	EXPECT_DOUBLE_EQ(result2.z, 21.0);
	EXPECT_DOUBLE_EQ(result2.w, 32.0);

	auto result3 = ldv1;
	result3 *= ldv2;
	EXPECT_NEAR(result3.x, 5.0, 1e-5);
	EXPECT_NEAR(result3.y, 12.0, 1e-5);
	EXPECT_NEAR(result3.z, 21.0, 1e-5);
	EXPECT_NEAR(result3.w, 32.0, 1e-5);
}

TEST_F(Vector4DNoSimdTest, HandlesVectorDivisionAssignment)
{
	auto result1 = v1;
	result1 /= v2;
	EXPECT_FLOAT_EQ(result1.x, 1.0f / 5.0f);
	EXPECT_FLOAT_EQ(result1.y, 2.0f / 6.0f);
	EXPECT_FLOAT_EQ(result1.z, 3.0f / 7.0f);
	EXPECT_FLOAT_EQ(result1.w, 4.0f / 8.0f);

	auto result2 = dv1;
	result2 /= dv2;
	EXPECT_DOUBLE_EQ(result2.x, 1.0 / 5.0);
	EXPECT_DOUBLE_EQ(result2.y, 2.0 / 6.0);
	EXPECT_DOUBLE_EQ(result2.z, 3.0 / 7.0);
	EXPECT_DOUBLE_EQ(result2.w, 4.0 / 8.0);

	auto result3 = ldv1;
	result3 /= ldv2;
	EXPECT_NEAR(result3.x, 1.0 / 5.0, 1e-5);
	EXPECT_NEAR(result3.y, 2.0 / 6.0, 1e-5);
	EXPECT_NEAR(result3.z, 3.0 / 7.0, 1e-5);
	EXPECT_NEAR(result3.w, 4.0 / 8.0, 1e-5);
}

TEST_F(Vector4DNoSimdTest, HandlesDotProduct)
{
	auto result1 = v1.Dot(v2);
	EXPECT_NEAR(result1, 70.0f, 1e-5); // 1 * 5 + 2 * 6 + 3 * 7 + 4 * 8

	auto result2 = dv1.Dot(dv2);
	EXPECT_NEAR(result2, 70.0, 1e-5);

	auto result3 = ldv1.Dot(ldv2);
	EXPECT_NEAR(result3, 70.0, 1e-5);
}

TEST_F(Vector4DNoSimdTest, HandlesCrossProduct)
{
	auto result = v1.Cross3D(v2); // Only defined for 3D vectors
	EXPECT_FLOAT_EQ(result.x, -4.0f);
	EXPECT_FLOAT_EQ(result.y, 8.0f);
	EXPECT_FLOAT_EQ(result.z, -4.0f);

	auto result2 = dv1.Cross3D(dv2);
	EXPECT_DOUBLE_EQ(result2.x, -4.0);
	EXPECT_DOUBLE_EQ(result2.y, 8.0);
	EXPECT_DOUBLE_EQ(result2.z, -4.0);

	auto result3 = ldv1.Cross3D(ldv2);
	EXPECT_NEAR(result3.x, -4.0, 1e-5);
	EXPECT_NEAR(result3.y, 8.0, 1e-5);
	EXPECT_NEAR(result3.z, -4.0, 1e-5);
}
