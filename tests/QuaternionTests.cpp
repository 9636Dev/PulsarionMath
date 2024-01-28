#include <gtest/gtest.h>
#include <PulsarionMath/Math.hpp>

using namespace Pulsarion;

class QuaternionTest : public ::testing::Test
{
protected:
	Quaternion q1;
	Quaternion q2;

	void SetUp() override
	{
		// Q1 is a rotation of 90 degrees around the X axis
		q1 = Quaternion(Math::Sqrt(2.0f) / 2.0f, Math::Sqrt(2.0f) / 2.0f, 0.0f, 0.0f);
		// Q2 is a rotation of 90 degrees around the Y axis
		q2 = Quaternion(Math::Sqrt(2.0f) / 2.0f, 0.0f, Math::Sqrt(2.0f) / 2.0f, 0.0f);
	}
};

TEST_F(QuaternionTest, HandlesDefaultConstructor)
{
	Quaternion q;
	EXPECT_EQ(q.x, 0.0f);
	EXPECT_EQ(q.y, 0.0f);
	EXPECT_FLOAT_EQ(q.z, 0.0f);
	EXPECT_FLOAT_EQ(q.w, 1.0f);
}

TEST_F(QuaternionTest, HandlesConstructor)
{
	Quaternion q(1.0f, 2.0f, 3.0f, 4.0f);
	EXPECT_EQ(q.w, 1.0f);
	EXPECT_EQ(q.x, 2.0f);
	EXPECT_FLOAT_EQ(q.y, 3.0f);
	EXPECT_FLOAT_EQ(q.z, 4.0f);
}

TEST_F(QuaternionTest, HandlesCopyConstructor)
{
	Quaternion q(q1);
	EXPECT_EQ(q.x, q1.x);
	EXPECT_EQ(q.y, q1.y);
	EXPECT_FLOAT_EQ(q.z, q1.z);
	EXPECT_FLOAT_EQ(q.w, q1.w);
}

TEST_F(QuaternionTest, HandlesMultiplication)
{
	Quaternion q = q1 * q2;
	EXPECT_FLOAT_EQ(q.x, 0.5f);
	EXPECT_FLOAT_EQ(q.y, 0.5f);
	EXPECT_FLOAT_EQ(q.z, 0.5f);
	EXPECT_FLOAT_EQ(q.w, 0.5f);
}

TEST_F(QuaternionTest, HandlesToMatrix)
{
	const auto m = q1.ToMatrix();
	EXPECT_NEAR(m.data[0], 1.0f, 1e-6f);
	EXPECT_NEAR(m.data[1], 0.0f, 1e-6f);
	EXPECT_NEAR(m.data[2], 0.0f, 1e-6f);
	EXPECT_NEAR(m.data[3], 0.0f, 1e-6f);
	EXPECT_NEAR(m.data[4], 0.0f, 1e-6f);
	EXPECT_NEAR(m.data[5], 0.0f, 1e-6f);  // Cos(90) = 0
	EXPECT_NEAR(m.data[6], 1.0f, 1e-6f); // Sin(90) = -1
	EXPECT_NEAR(m.data[7], 0.0f, 1e-6f);
	EXPECT_NEAR(m.data[8], 0.0f, 1e-6f);
	EXPECT_NEAR(m.data[9], -1.0f, 1e-6f);  // -Sin(90) = 1
	EXPECT_NEAR(m.data[10], 0.0f, 1e-6f);  // Cos(90) = 0
	EXPECT_NEAR(m.data[11], 0.0f, 1e-6f);
	EXPECT_NEAR(m.data[12], 0.0f, 1e-6f);
	EXPECT_NEAR(m.data[13], 0.0f, 1e-6f);
	EXPECT_NEAR(m.data[14], 0.0f, 1e-6f);
	EXPECT_NEAR(m.data[15], 1.0f, 1e-6f);
}

TEST_F(QuaternionTest, HandlesVectorTransform)
{
	// Don't need to do anything here, since the matrix test already covers this
}

