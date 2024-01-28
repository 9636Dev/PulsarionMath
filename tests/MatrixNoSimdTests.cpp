#include <gtest/gtest.h>
#define PULSARION_MATH_DISABLE_SIMD
#include <PulsarionMath/Math.hpp>

using namespace Pulsarion;

class Matrix4x4NoSimdTest : public ::testing::Test
{
protected:
	Mat4 m1;
	Mat4 m2;
	Mat4 mIdentity;

	Mat4d d1;
	Mat4d d2;
	Mat4d dIdentity;

	Mat4ld ld1;
	Mat4ld ld2;
	Mat4ld ldIdentity;

	void SetUp() override
	{
		// m1 is incremental to 16, and m2 is decremental to 16 from 32
		// Input is transposed, because our matrix is column major

		m1 = {
			1.0f, 2.0f, 3.0f, 4.0f,
			5.0f, 6.0f, 7.0f, 8.0f,
			9.0f, 10.0f, 11.0f, 12.0f,
			13.0f, 14.0f, 15.0f, 16.0f
		};
		m1.Transpose();

		m2 = {
			32.0f, 31.0f, 30.0f, 29.0f,
			28.0f, 27.0f, 26.0f, 25.0f,
			24.0f, 23.0f, 22.0f, 21.0f,
			20.0f, 19.0f, 18.0f, 17.0f
		};
		m2.Transpose();

		d1 = {
			1.0, 2.0, 3.0, 4.0,
			5.0, 6.0, 7.0, 8.0,
			9.0, 10.0, 11.0, 12.0,
			13.0, 14.0, 15.0, 16.0
		};
		d1.Transpose();

		d2 = {
			32.0, 31.0, 30.0, 29.0,
			28.0, 27.0, 26.0, 25.0,
			24.0, 23.0, 22.0, 21.0,
			20.0, 19.0, 18.0, 17.0
		};
		d2.Transpose();

		ld1 = {
			1.0, 2.0, 3.0, 4.0,
			5.0, 6.0, 7.0, 8.0,
			9.0, 10.0, 11.0, 12.0,
			13.0, 14.0, 15.0, 16.0
		};
		ld1.Transpose();

		ld2 = {
			32.0, 31.0, 30.0, 29.0,
			28.0, 27.0, 26.0, 25.0,
			24.0, 23.0, 22.0, 21.0,
			20.0, 19.0, 18.0, 17.0
		};
		ld2.Transpose();
	}
};

TEST_F(Matrix4x4NoSimdTest, HandlesIdentity)
{
	EXPECT_FLOAT_EQ(mIdentity.data[0], 1.0f);
	EXPECT_FLOAT_EQ(mIdentity.data[1], 0.0f);
	EXPECT_FLOAT_EQ(mIdentity.data[2], 0.0f);
	EXPECT_FLOAT_EQ(mIdentity.data[3], 0.0f);
	EXPECT_FLOAT_EQ(mIdentity.data[4], 0.0f);
	EXPECT_FLOAT_EQ(mIdentity.data[5], 1.0f);
	EXPECT_FLOAT_EQ(mIdentity.data[6], 0.0f);
	EXPECT_FLOAT_EQ(mIdentity.data[7], 0.0f);
	EXPECT_FLOAT_EQ(mIdentity.data[8], 0.0f);
	EXPECT_FLOAT_EQ(mIdentity.data[9], 0.0f);
	EXPECT_FLOAT_EQ(mIdentity.data[10], 1.0f);
	EXPECT_FLOAT_EQ(mIdentity.data[11], 0.0f);
	EXPECT_FLOAT_EQ(mIdentity.data[12], 0.0f);
	EXPECT_FLOAT_EQ(mIdentity.data[13], 0.0f);
	EXPECT_FLOAT_EQ(mIdentity.data[14], 0.0f);
	EXPECT_FLOAT_EQ(mIdentity.data[15], 1.0f);

	// Double
	EXPECT_FLOAT_EQ(dIdentity.data[0], 1.0);
	EXPECT_FLOAT_EQ(dIdentity.data[1], 0.0);
	EXPECT_FLOAT_EQ(dIdentity.data[2], 0.0);
	EXPECT_FLOAT_EQ(dIdentity.data[3], 0.0);
	EXPECT_FLOAT_EQ(dIdentity.data[4], 0.0);
	EXPECT_FLOAT_EQ(dIdentity.data[5], 1.0);
	EXPECT_FLOAT_EQ(dIdentity.data[6], 0.0);
	EXPECT_FLOAT_EQ(dIdentity.data[7], 0.0);
	EXPECT_FLOAT_EQ(dIdentity.data[8], 0.0);
	EXPECT_FLOAT_EQ(dIdentity.data[9], 0.0);
	EXPECT_FLOAT_EQ(dIdentity.data[10], 1.0);
	EXPECT_FLOAT_EQ(dIdentity.data[11], 0.0);
	EXPECT_FLOAT_EQ(dIdentity.data[12], 0.0);
	EXPECT_FLOAT_EQ(dIdentity.data[13], 0.0);
	EXPECT_FLOAT_EQ(dIdentity.data[14], 0.0);
	EXPECT_FLOAT_EQ(dIdentity.data[15], 1.0);

	EXPECT_FLOAT_EQ(ldIdentity.data[0], 1.0);
	EXPECT_FLOAT_EQ(ldIdentity.data[1], 0.0);
	EXPECT_FLOAT_EQ(ldIdentity.data[2], 0.0);
	EXPECT_FLOAT_EQ(ldIdentity.data[3], 0.0);
	EXPECT_FLOAT_EQ(ldIdentity.data[4], 0.0);
	EXPECT_FLOAT_EQ(ldIdentity.data[5], 1.0);
	EXPECT_FLOAT_EQ(ldIdentity.data[6], 0.0);
	EXPECT_FLOAT_EQ(ldIdentity.data[7], 0.0);
	EXPECT_FLOAT_EQ(ldIdentity.data[8], 0.0);
	EXPECT_FLOAT_EQ(ldIdentity.data[9], 0.0);
	EXPECT_FLOAT_EQ(ldIdentity.data[10], 1.0);
	EXPECT_FLOAT_EQ(ldIdentity.data[11], 0.0);
	EXPECT_FLOAT_EQ(ldIdentity.data[12], 0.0);
	EXPECT_FLOAT_EQ(ldIdentity.data[13], 0.0);
	EXPECT_FLOAT_EQ(ldIdentity.data[14], 0.0);
	EXPECT_FLOAT_EQ(ldIdentity.data[15], 1.0);
}

TEST_F(Matrix4x4NoSimdTest, HandlesTranspose)
{
	m1.Transpose();
	EXPECT_FLOAT_EQ(m1.data[0], 1.0f);
	EXPECT_FLOAT_EQ(m1.data[1], 5.0f);
	EXPECT_FLOAT_EQ(m1.data[2], 9.0f);
	EXPECT_FLOAT_EQ(m1.data[3], 13.0f);
	EXPECT_FLOAT_EQ(m1.data[4], 2.0f);
	EXPECT_FLOAT_EQ(m1.data[5], 6.0f);
	EXPECT_FLOAT_EQ(m1.data[6], 10.0f);
	EXPECT_FLOAT_EQ(m1.data[7], 14.0f);
	EXPECT_FLOAT_EQ(m1.data[8], 3.0f);
	EXPECT_FLOAT_EQ(m1.data[9], 7.0f);
	EXPECT_FLOAT_EQ(m1.data[10], 11.0f);
	EXPECT_FLOAT_EQ(m1.data[11], 15.0f);
	EXPECT_FLOAT_EQ(m1.data[12], 4.0f);
	EXPECT_FLOAT_EQ(m1.data[13], 8.0f);
	EXPECT_FLOAT_EQ(m1.data[14], 12.0f);
	EXPECT_FLOAT_EQ(m1.data[15], 16.0f);

	d1.Transpose();
	EXPECT_FLOAT_EQ(d1.data[0], 1.0);
	EXPECT_FLOAT_EQ(d1.data[1], 5.0);
	EXPECT_FLOAT_EQ(d1.data[2], 9.0);
	EXPECT_FLOAT_EQ(d1.data[3], 13.0);
	EXPECT_FLOAT_EQ(d1.data[4], 2.0);
	EXPECT_FLOAT_EQ(d1.data[5], 6.0);
	EXPECT_FLOAT_EQ(d1.data[6], 10.0);
	EXPECT_FLOAT_EQ(d1.data[7], 14.0);
	EXPECT_FLOAT_EQ(d1.data[8], 3.0);
	EXPECT_FLOAT_EQ(d1.data[9], 7.0);
	EXPECT_FLOAT_EQ(d1.data[10], 11.0);
	EXPECT_FLOAT_EQ(d1.data[11], 15.0);
	EXPECT_FLOAT_EQ(d1.data[12], 4.0);
	EXPECT_FLOAT_EQ(d1.data[13], 8.0);
	EXPECT_FLOAT_EQ(d1.data[14], 12.0);
	EXPECT_FLOAT_EQ(d1.data[15], 16.0);

	ld1.Transpose();
	EXPECT_EQ(ld1.data[0], 1.0);
	EXPECT_EQ(ld1.data[1], 5.0);
	EXPECT_EQ(ld1.data[2], 9.0);
	EXPECT_EQ(ld1.data[3], 13.0);
	EXPECT_EQ(ld1.data[4], 2.0);
	EXPECT_EQ(ld1.data[5], 6.0);
	EXPECT_EQ(ld1.data[6], 10.0);
	EXPECT_EQ(ld1.data[7], 14.0);
	EXPECT_EQ(ld1.data[8], 3.0);
	EXPECT_EQ(ld1.data[9], 7.0);
	EXPECT_EQ(ld1.data[10], 11.0);
	EXPECT_EQ(ld1.data[11], 15.0);
	EXPECT_EQ(ld1.data[12], 4.0);
	EXPECT_EQ(ld1.data[13], 8.0);
	EXPECT_EQ(ld1.data[14], 12.0);
	EXPECT_EQ(ld1.data[15], 16.0);
}

TEST_F(Matrix4x4NoSimdTest, HandlesAddition)
{
	const auto result = m1 + m2;
	EXPECT_FLOAT_EQ(result.data[0], 33.0f);
	EXPECT_FLOAT_EQ(result.data[1], 33.0f);
	EXPECT_FLOAT_EQ(result.data[2], 33.0f);
	EXPECT_FLOAT_EQ(result.data[3], 33.0f);
	EXPECT_FLOAT_EQ(result.data[4], 33.0f);
	EXPECT_FLOAT_EQ(result.data[5], 33.0f);
	EXPECT_FLOAT_EQ(result.data[6], 33.0f);
	EXPECT_FLOAT_EQ(result.data[7], 33.0f);
	EXPECT_FLOAT_EQ(result.data[8], 33.0f);
	EXPECT_FLOAT_EQ(result.data[9], 33.0f);
	EXPECT_FLOAT_EQ(result.data[10], 33.0f);
	EXPECT_FLOAT_EQ(result.data[11], 33.0f);
	EXPECT_FLOAT_EQ(result.data[12], 33.0f);
	EXPECT_FLOAT_EQ(result.data[13], 33.0f);
	EXPECT_FLOAT_EQ(result.data[14], 33.0f);
	EXPECT_FLOAT_EQ(result.data[15], 33.0f);

	const auto result2 = d1 + d2;
	EXPECT_DOUBLE_EQ(result2.data[0], 33.0);
	EXPECT_DOUBLE_EQ(result2.data[1], 33.0);
	EXPECT_DOUBLE_EQ(result2.data[2], 33.0);
	EXPECT_DOUBLE_EQ(result2.data[3], 33.0);
	EXPECT_DOUBLE_EQ(result2.data[4], 33.0);
	EXPECT_DOUBLE_EQ(result2.data[5], 33.0);
	EXPECT_DOUBLE_EQ(result2.data[6], 33.0);
	EXPECT_DOUBLE_EQ(result2.data[7], 33.0);
	EXPECT_DOUBLE_EQ(result2.data[8], 33.0);
	EXPECT_DOUBLE_EQ(result2.data[9], 33.0);
	EXPECT_DOUBLE_EQ(result2.data[10], 33.0);
	EXPECT_DOUBLE_EQ(result2.data[11], 33.0);
	EXPECT_DOUBLE_EQ(result2.data[12], 33.0);
	EXPECT_DOUBLE_EQ(result2.data[13], 33.0);
	EXPECT_DOUBLE_EQ(result2.data[14], 33.0);
	EXPECT_DOUBLE_EQ(result2.data[15], 33.0);

	const auto result3 = ld1 + ld2;
	EXPECT_EQ(result3.data[0], 33.0);
	EXPECT_EQ(result3.data[1], 33.0);
	EXPECT_EQ(result3.data[2], 33.0);
	EXPECT_EQ(result3.data[3], 33.0);
	EXPECT_EQ(result3.data[4], 33.0);
	EXPECT_EQ(result3.data[5], 33.0);
	EXPECT_EQ(result3.data[6], 33.0);
	EXPECT_EQ(result3.data[7], 33.0);
	EXPECT_EQ(result3.data[8], 33.0);
	EXPECT_EQ(result3.data[9], 33.0);
	EXPECT_EQ(result3.data[10], 33.0);
	EXPECT_EQ(result3.data[11], 33.0);
	EXPECT_EQ(result3.data[12], 33.0);
	EXPECT_EQ(result3.data[13], 33.0);
	EXPECT_EQ(result3.data[14], 33.0);
	EXPECT_EQ(result3.data[15], 33.0);
}

TEST_F(Matrix4x4NoSimdTest, HandlesSubtraction)
{
	const auto result = m1 - m2;
	EXPECT_FLOAT_EQ(result.data[0], -31.0f); // This is wrong, because our matrix is column major
	EXPECT_FLOAT_EQ(result.data[1], -29.0f);
	EXPECT_FLOAT_EQ(result.data[2], -27.0f);
	EXPECT_FLOAT_EQ(result.data[3], -25.0f);
	EXPECT_FLOAT_EQ(result.data[4], -23.0f);
	EXPECT_FLOAT_EQ(result.data[5], -21.0f);
	EXPECT_FLOAT_EQ(result.data[6], -19.0f);
	EXPECT_FLOAT_EQ(result.data[7], -17.0f);
	EXPECT_FLOAT_EQ(result.data[8], -15.0f);
	EXPECT_FLOAT_EQ(result.data[9], -13.0f);
	EXPECT_FLOAT_EQ(result.data[10], -11.0f);
	EXPECT_FLOAT_EQ(result.data[11], -9.0f);
	EXPECT_FLOAT_EQ(result.data[12], -7.0f);
	EXPECT_FLOAT_EQ(result.data[13], -5.0f);
	EXPECT_FLOAT_EQ(result.data[14], -3.0f);
	EXPECT_FLOAT_EQ(result.data[15], -1.0f);

	const auto result2 = d1 - d2;
	EXPECT_DOUBLE_EQ(result2.data[0], -31.0);
	EXPECT_DOUBLE_EQ(result2.data[1], -29.0);
	EXPECT_DOUBLE_EQ(result2.data[2], -27.0);
	EXPECT_DOUBLE_EQ(result2.data[3], -25.0);
	EXPECT_DOUBLE_EQ(result2.data[4], -23.0);
	EXPECT_DOUBLE_EQ(result2.data[5], -21.0);
	EXPECT_DOUBLE_EQ(result2.data[6], -19.0);
	EXPECT_DOUBLE_EQ(result2.data[7], -17.0);
	EXPECT_DOUBLE_EQ(result2.data[8], -15.0);
	EXPECT_DOUBLE_EQ(result2.data[9], -13.0);
	EXPECT_DOUBLE_EQ(result2.data[10], -11.0);
	EXPECT_DOUBLE_EQ(result2.data[11], -9.0);
	EXPECT_DOUBLE_EQ(result2.data[12], -7.0);
	EXPECT_DOUBLE_EQ(result2.data[13], -5.0);
	EXPECT_DOUBLE_EQ(result2.data[14], -3.0);
	EXPECT_DOUBLE_EQ(result2.data[15], -1.0);

	const auto result3 = ld1 - ld2;
	EXPECT_EQ(result3.data[0], -31.0);
	EXPECT_EQ(result3.data[1], -29.0);
	EXPECT_EQ(result3.data[2], -27.0);
	EXPECT_EQ(result3.data[3], -25.0);
	EXPECT_EQ(result3.data[4], -23.0);
	EXPECT_EQ(result3.data[5], -21.0);
	EXPECT_EQ(result3.data[6], -19.0);
	EXPECT_EQ(result3.data[7], -17.0);
	EXPECT_EQ(result3.data[8], -15.0);
	EXPECT_EQ(result3.data[9], -13.0);
	EXPECT_EQ(result3.data[10], -11.0);
	EXPECT_EQ(result3.data[11], -9.0);
	EXPECT_EQ(result3.data[12], -7.0);
	EXPECT_EQ(result3.data[13], -5.0);
	EXPECT_EQ(result3.data[14], -3.0);
	EXPECT_EQ(result3.data[15], -1.0);
}

TEST_F(Matrix4x4NoSimdTest, HandlesScalerMultiplication)
{
	const auto result = m1 * 2.0f;
	EXPECT_FLOAT_EQ(result.data[0], 2.0f);
	EXPECT_FLOAT_EQ(result.data[1], 4.0f);
	EXPECT_FLOAT_EQ(result.data[2], 6.0f);
	EXPECT_FLOAT_EQ(result.data[3], 8.0f);
	EXPECT_FLOAT_EQ(result.data[4], 10.0f);
	EXPECT_FLOAT_EQ(result.data[5], 12.0f);
	EXPECT_FLOAT_EQ(result.data[6], 14.0f);
	EXPECT_FLOAT_EQ(result.data[7], 16.0f);
	EXPECT_FLOAT_EQ(result.data[8], 18.0f);
	EXPECT_FLOAT_EQ(result.data[9], 20.0f);
	EXPECT_FLOAT_EQ(result.data[10], 22.0f);
	EXPECT_FLOAT_EQ(result.data[11], 24.0f);
	EXPECT_FLOAT_EQ(result.data[12], 26.0f);
	EXPECT_FLOAT_EQ(result.data[13], 28.0f);
	EXPECT_FLOAT_EQ(result.data[14], 30.0f);
	EXPECT_FLOAT_EQ(result.data[15], 32.0f);

	const auto result2 = d1 * 2.0;
	EXPECT_DOUBLE_EQ(result2.data[0], 2.0);
	EXPECT_DOUBLE_EQ(result2.data[1], 4.0);
	EXPECT_DOUBLE_EQ(result2.data[2], 6.0);
	EXPECT_DOUBLE_EQ(result2.data[3], 8.0);
	EXPECT_DOUBLE_EQ(result2.data[4], 10.0);
	EXPECT_DOUBLE_EQ(result2.data[5], 12.0);
	EXPECT_DOUBLE_EQ(result2.data[6], 14.0);
	EXPECT_DOUBLE_EQ(result2.data[7], 16.0);
	EXPECT_DOUBLE_EQ(result2.data[8], 18.0);
	EXPECT_DOUBLE_EQ(result2.data[9], 20.0);
	EXPECT_DOUBLE_EQ(result2.data[10], 22.0);
	EXPECT_DOUBLE_EQ(result2.data[11], 24.0);
	EXPECT_DOUBLE_EQ(result2.data[12], 26.0);
	EXPECT_DOUBLE_EQ(result2.data[13], 28.0);
	EXPECT_DOUBLE_EQ(result2.data[14], 30.0);
	EXPECT_DOUBLE_EQ(result2.data[15], 32.0);

	const auto result3 = ld1 * 2.0;
	EXPECT_EQ(result3.data[0], 2.0);
	EXPECT_EQ(result3.data[1], 4.0);
	EXPECT_EQ(result3.data[2], 6.0);
	EXPECT_EQ(result3.data[3], 8.0);
	EXPECT_EQ(result3.data[4], 10.0);
	EXPECT_EQ(result3.data[5], 12.0);
	EXPECT_EQ(result3.data[6], 14.0);
	EXPECT_EQ(result3.data[7], 16.0);
	EXPECT_EQ(result3.data[8], 18.0);
	EXPECT_EQ(result3.data[9], 20.0);
	EXPECT_EQ(result3.data[10], 22.0);
	EXPECT_EQ(result3.data[11], 24.0);
	EXPECT_EQ(result3.data[12], 26.0);
	EXPECT_EQ(result3.data[13], 28.0);
	EXPECT_EQ(result3.data[14], 30.0);
	EXPECT_EQ(result3.data[15], 32.0);
}

TEST_F(Matrix4x4NoSimdTest, HandlesMatrixMultiplication)
{
	const auto result1 = mIdentity * m1;
	EXPECT_FLOAT_EQ(result1.data[0], 1.0f);
	EXPECT_FLOAT_EQ(result1.data[1], 2.0f);
	EXPECT_FLOAT_EQ(result1.data[2], 3.0f);
	EXPECT_FLOAT_EQ(result1.data[3], 4.0f);
	EXPECT_FLOAT_EQ(result1.data[4], 5.0f);
	EXPECT_FLOAT_EQ(result1.data[5], 6.0f);
	EXPECT_FLOAT_EQ(result1.data[6], 7.0f);
	EXPECT_FLOAT_EQ(result1.data[7], 8.0f);
	EXPECT_FLOAT_EQ(result1.data[8], 9.0f);
	EXPECT_FLOAT_EQ(result1.data[9], 10.0f);
	EXPECT_FLOAT_EQ(result1.data[10], 11.0f);
	EXPECT_FLOAT_EQ(result1.data[11], 12.0f);
	EXPECT_FLOAT_EQ(result1.data[12], 13.0f);
	EXPECT_FLOAT_EQ(result1.data[13], 14.0f);
	EXPECT_FLOAT_EQ(result1.data[14], 15.0f);
	EXPECT_FLOAT_EQ(result1.data[15], 16.0f);

	const auto result2 = m1 * m2;
	EXPECT_FLOAT_EQ(result2.data[0], 834.0f);
	EXPECT_FLOAT_EQ(result2.data[1], 956.0f);
	EXPECT_FLOAT_EQ(result2.data[2], 1078.0f);
	EXPECT_FLOAT_EQ(result2.data[3], 1200.0f);
	EXPECT_FLOAT_EQ(result2.data[4], 722.0f);
	EXPECT_FLOAT_EQ(result2.data[5], 828.0f);
	EXPECT_FLOAT_EQ(result2.data[6], 934.0f);
	EXPECT_FLOAT_EQ(result2.data[7], 1040.0f);
	EXPECT_FLOAT_EQ(result2.data[8], 610.0f);
	EXPECT_FLOAT_EQ(result2.data[9], 700.0f);
	EXPECT_FLOAT_EQ(result2.data[10], 790.0f);
	EXPECT_FLOAT_EQ(result2.data[11], 880.0f);
	EXPECT_FLOAT_EQ(result2.data[12], 498.0f);
	EXPECT_FLOAT_EQ(result2.data[13], 572.0f);
	EXPECT_FLOAT_EQ(result2.data[14], 646.0f);
	EXPECT_FLOAT_EQ(result2.data[15], 720.0f);

	const auto result3 = m2 * m1;
	EXPECT_FLOAT_EQ(result3.data[0], 240.0f);
	EXPECT_FLOAT_EQ(result3.data[1], 230.0f);
	EXPECT_FLOAT_EQ(result3.data[2], 220.0f);
	EXPECT_FLOAT_EQ(result3.data[3], 210.0f);
	EXPECT_FLOAT_EQ(result3.data[4], 656.0f);
	EXPECT_FLOAT_EQ(result3.data[5], 630.0f);
	EXPECT_FLOAT_EQ(result3.data[6], 604.0f);
	EXPECT_FLOAT_EQ(result3.data[7], 578.0f);
	EXPECT_FLOAT_EQ(result3.data[8], 1072.0f);
	EXPECT_FLOAT_EQ(result3.data[9], 1030.0f);
	EXPECT_FLOAT_EQ(result3.data[10], 988.0f);
	EXPECT_FLOAT_EQ(result3.data[11], 946.0f);
	EXPECT_FLOAT_EQ(result3.data[12], 1488.0f);
	EXPECT_FLOAT_EQ(result3.data[13], 1430.0f);
	EXPECT_FLOAT_EQ(result3.data[14], 1372.0f);
	EXPECT_FLOAT_EQ(result3.data[15], 1314.0f);

	const auto result4 = d1 * d2;
	EXPECT_DOUBLE_EQ(result4.data[0], 834.0);
	EXPECT_DOUBLE_EQ(result4.data[1], 956.0);
	EXPECT_DOUBLE_EQ(result4.data[2], 1078.0);
	EXPECT_DOUBLE_EQ(result4.data[3], 1200.0);
	EXPECT_DOUBLE_EQ(result4.data[4], 722.0);
	EXPECT_DOUBLE_EQ(result4.data[5], 828.0);
	EXPECT_DOUBLE_EQ(result4.data[6], 934.0);
	EXPECT_DOUBLE_EQ(result4.data[7], 1040.0);
	EXPECT_DOUBLE_EQ(result4.data[8], 610.0);
	EXPECT_DOUBLE_EQ(result4.data[9], 700.0);
	EXPECT_DOUBLE_EQ(result4.data[10], 790.0);
	EXPECT_DOUBLE_EQ(result4.data[11], 880.0);
	EXPECT_DOUBLE_EQ(result4.data[12], 498.0);
	EXPECT_DOUBLE_EQ(result4.data[13], 572.0);
	EXPECT_DOUBLE_EQ(result4.data[14], 646.0);
	EXPECT_DOUBLE_EQ(result4.data[15], 720.0);

	const auto result5 = d2 * d1;
	EXPECT_DOUBLE_EQ(result5.data[0], 240.0);
	EXPECT_DOUBLE_EQ(result5.data[1], 230.0);
	EXPECT_DOUBLE_EQ(result5.data[2], 220.0);
	EXPECT_DOUBLE_EQ(result5.data[3], 210.0);
	EXPECT_DOUBLE_EQ(result5.data[4], 656.0);
	EXPECT_DOUBLE_EQ(result5.data[5], 630.0);
	EXPECT_DOUBLE_EQ(result5.data[6], 604.0);
	EXPECT_DOUBLE_EQ(result5.data[7], 578.0);
	EXPECT_DOUBLE_EQ(result5.data[8], 1072.0);
	EXPECT_DOUBLE_EQ(result5.data[9], 1030.0);
	EXPECT_DOUBLE_EQ(result5.data[10], 988.0);
	EXPECT_DOUBLE_EQ(result5.data[11], 946.0);
	EXPECT_DOUBLE_EQ(result5.data[12], 1488.0);
	EXPECT_DOUBLE_EQ(result5.data[13], 1430.0);
	EXPECT_DOUBLE_EQ(result5.data[14], 1372.0);
	EXPECT_DOUBLE_EQ(result5.data[15], 1314.0);

	const auto result6 = ld1 * ld2;
	EXPECT_EQ(result6.data[0], 834.0);
	EXPECT_EQ(result6.data[1], 956.0);
	EXPECT_EQ(result6.data[2], 1078.0);
	EXPECT_EQ(result6.data[3], 1200.0);
	EXPECT_EQ(result6.data[4], 722.0);
	EXPECT_EQ(result6.data[5], 828.0);
	EXPECT_EQ(result6.data[6], 934.0);
	EXPECT_EQ(result6.data[7], 1040.0);
	EXPECT_EQ(result6.data[8], 610.0);
	EXPECT_EQ(result6.data[9], 700.0);
	EXPECT_EQ(result6.data[10], 790.0);
	EXPECT_EQ(result6.data[11], 880.0);
	EXPECT_EQ(result6.data[12], 498.0);
	EXPECT_EQ(result6.data[13], 572.0);
	EXPECT_EQ(result6.data[14], 646.0);
	EXPECT_EQ(result6.data[15], 720.0);

	const auto result7 = ld2 * ld1;
	EXPECT_EQ(result7.data[0], 240.0);
	EXPECT_EQ(result7.data[1], 230.0);
	EXPECT_EQ(result7.data[2], 220.0);
	EXPECT_EQ(result7.data[3], 210.0);
	EXPECT_EQ(result7.data[4], 656.0);
	EXPECT_EQ(result7.data[5], 630.0);
	EXPECT_EQ(result7.data[6], 604.0);
	EXPECT_EQ(result7.data[7], 578.0);
	EXPECT_EQ(result7.data[8], 1072.0);
	EXPECT_EQ(result7.data[9], 1030.0);
	EXPECT_EQ(result7.data[10], 988.0);
	EXPECT_EQ(result7.data[11], 946.0);
	EXPECT_EQ(result7.data[12], 1488.0);
	EXPECT_EQ(result7.data[13], 1430.0);
	EXPECT_EQ(result7.data[14], 1372.0);
	EXPECT_EQ(result7.data[15], 1314.0);
}

TEST_F(Matrix4x4NoSimdTest, HandlesVectorMultiplication)
{
	const auto result1 = m1 * Vec4(1.0f, 2.0f, 3.0f, 4.0f);
	EXPECT_FLOAT_EQ(result1.x, 90.0f);
	EXPECT_FLOAT_EQ(result1.y, 100.0f);
	EXPECT_FLOAT_EQ(result1.z, 110.0f);
	EXPECT_FLOAT_EQ(result1.w, 120.0f);

	const auto result2 = d1 * Vec4d(1.0, 2.0, 3.0, 4.0);
	EXPECT_DOUBLE_EQ(result2.x, 90.0);
	EXPECT_DOUBLE_EQ(result2.y, 100.0);
	EXPECT_DOUBLE_EQ(result2.z, 110.0);
	EXPECT_DOUBLE_EQ(result2.w, 120.0);

	const auto result3 = ld1 * Vec4ld(1.0, 2.0, 3.0, 4.0);
	EXPECT_EQ(result3.x, 90.0);
	EXPECT_EQ(result3.y, 100.0);
	EXPECT_EQ(result3.z, 110.0);
	EXPECT_EQ(result3.w, 120.0);
}
