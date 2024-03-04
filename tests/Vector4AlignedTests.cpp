#include <gtest/gtest.h>

#include "PulsarionMath/Vector.hpp"

using namespace Pulsarion::Math;

TEST(Vector4AlignedTests, DefaultConstructor)
{
    Vector<4, float, Qualifier::Aligned> v;
    EXPECT_FLOAT_EQ(0.0f, v.x());
    EXPECT_FLOAT_EQ(0.0f, v.y());
    EXPECT_FLOAT_EQ(0.0f, v.z());
    EXPECT_FLOAT_EQ(0.0f, v.w());
}

TEST(Vector4AlignedTests, ConstructorWithValues)
{
    Vector<4, float, Qualifier::Aligned> v(1.0f, 2.0f, 3.0f, 4.0f);
    EXPECT_FLOAT_EQ(1.0f, v.x());
    EXPECT_FLOAT_EQ(2.0f, v.y());
    EXPECT_FLOAT_EQ(3.0f, v.z());
    EXPECT_FLOAT_EQ(4.0f, v.w());
}

TEST(Vector4AlignedTests, ConstructorWithScalar)
{
    Vector<4, float, Qualifier::Aligned> v(1.0f);
    EXPECT_FLOAT_EQ(1.0f, v.x());
    EXPECT_FLOAT_EQ(1.0f, v.y());
    EXPECT_FLOAT_EQ(1.0f, v.z());
    EXPECT_FLOAT_EQ(1.0f, v.w());
}

TEST(Vector4AlignedTests, CopyConstructor)
{
    Vector<4, float, Qualifier::Aligned> v1(1.0f, 2.0f, 3.0f, 4.0f);
    Vector<4, float, Qualifier::Aligned> v2(v1);
    EXPECT_FLOAT_EQ(1.0f, v2.x());
    EXPECT_FLOAT_EQ(2.0f, v2.y());
    EXPECT_FLOAT_EQ(3.0f, v2.z());
    EXPECT_FLOAT_EQ(4.0f, v2.w());
}

TEST(Vector4AlignedTests, CopyAssignment)
{
    Vector<4, float, Qualifier::Aligned> v1(1.0f, 2.0f, 3.0f, 4.0f);
    Vector<4, float, Qualifier::Aligned> v2;
    v2 = v1;
    EXPECT_FLOAT_EQ(1.0f, v2.x());
    EXPECT_FLOAT_EQ(2.0f, v2.y());
    EXPECT_FLOAT_EQ(3.0f, v2.z());
    EXPECT_FLOAT_EQ(4.0f, v2.w());
}

TEST(Vector4AlignedTests, MoveConstructor)
{
    Vector<4, float, Qualifier::Aligned> v1(1.0f, 2.0f, 3.0f, 4.0f);
    // NOLINTNEXTLINE(performance-move-const-arg)
    Vector<4, float, Qualifier::Aligned> v2(std::move(v1));
    EXPECT_FLOAT_EQ(1.0f, v2.x());
    EXPECT_FLOAT_EQ(2.0f, v2.y());
    EXPECT_FLOAT_EQ(3.0f, v2.z());
    EXPECT_FLOAT_EQ(4.0f, v2.w());
}

TEST(Vector4AlignedTests, MoveAssignment)
{
    Vector<4, float, Qualifier::Aligned> v1(1.0f, 2.0f, 3.0f, 4.0f);
    Vector<4, float, Qualifier::Aligned> v2;
    // NOLINTNEXTLINE(performance-move-const-arg)
    v2 = std::move(v1);
    EXPECT_FLOAT_EQ(1.0f, v2.x());
    EXPECT_FLOAT_EQ(2.0f, v2.y());
    EXPECT_FLOAT_EQ(3.0f, v2.z());
    EXPECT_FLOAT_EQ(4.0f, v2.w());
}

TEST(Vector4AlignedTests, AccessOperator)
{
    Vector<4, float, Qualifier::Aligned> v(1.0f, 2.0f, 3.0f, 4.0f);
    EXPECT_FLOAT_EQ(1.0f, v[0]);
    EXPECT_FLOAT_EQ(2.0f, v[1]);
    EXPECT_FLOAT_EQ(3.0f, v[2]);
    EXPECT_FLOAT_EQ(4.0f, v[3]);
}

TEST(Vector4AlignedTests, AccessOperatorConst)
{
    const Vector<4, float, Qualifier::Aligned> v(1.0f, 2.0f, 3.0f, 4.0f);
    EXPECT_FLOAT_EQ(1.0f, v[0]);
    EXPECT_FLOAT_EQ(2.0f, v[1]);
    EXPECT_FLOAT_EQ(3.0f, v[2]);
    EXPECT_FLOAT_EQ(4.0f, v[3]);
}

TEST(Vector4AlignedTests, UnaryPlusOperator)
{
    Vector<4, float, Qualifier::Aligned> v1(1.0f, 2.0f, 3.0f, 4.0f);
    Vector<4, float, Qualifier::Aligned> v2 = +v1;
    EXPECT_FLOAT_EQ(1.0f, v2.x());
    EXPECT_FLOAT_EQ(2.0f, v2.y());
    EXPECT_FLOAT_EQ(3.0f, v2.z());
    EXPECT_FLOAT_EQ(4.0f, v2.w());
}

TEST(Vector4AlignedTests, UnaryMinusOperator)
{
    Vector<4, float, Qualifier::Aligned> v1(1.0f, 2.0f, 3.0f, 4.0f);
    Vector<4, float, Qualifier::Aligned> v2 = -v1;
    EXPECT_FLOAT_EQ(-1.0f, v2.x());
    EXPECT_FLOAT_EQ(-2.0f, v2.y());
    EXPECT_FLOAT_EQ(-3.0f, v2.z());
    EXPECT_FLOAT_EQ(-4.0f, v2.w());
}

TEST(Vector4AlignedTests, AdditionOperator)
{
    Vector<4, float, Qualifier::Aligned> v1(1.0f, 2.0f, 3.0f, 4.0f);
    Vector<4, float, Qualifier::Aligned> v2(5.0f, 6.0f, 7.0f, 8.0f);
    Vector<4, float, Qualifier::Aligned> v3 = v1 + v2;
    EXPECT_FLOAT_EQ(6.0f, v3.x());
    EXPECT_FLOAT_EQ(8.0f, v3.y());
    EXPECT_FLOAT_EQ(10.0f, v3.z());
    EXPECT_FLOAT_EQ(12.0f, v3.w());
}

TEST(Vector4AlignedTests, AdditionAssignmentOperator)
{
    Vector<4, float, Qualifier::Aligned> v1(1.0f, 2.0f, 3.0f, 4.0f);
    Vector<4, float, Qualifier::Aligned> v2(5.0f, 6.0f, 7.0f, 8.0f);
    v1 += v2;
    EXPECT_FLOAT_EQ(6.0f, v1.x());
    EXPECT_FLOAT_EQ(8.0f, v1.y());
    EXPECT_FLOAT_EQ(10.0f, v1.z());
    EXPECT_FLOAT_EQ(12.0f, v1.w());
}

TEST(Vector4AlignedTests, SubtractionOperator)
{
    Vector<4, float, Qualifier::Aligned> v1(5.0f, 6.0f, 7.0f, 8.0f);
    Vector<4, float, Qualifier::Aligned> v2(1.0f, 2.0f, 3.0f, 4.0f);
    Vector<4, float, Qualifier::Aligned> v3 = v1 - v2;
    EXPECT_FLOAT_EQ(4.0f, v3.x());
    EXPECT_FLOAT_EQ(4.0f, v3.y());
    EXPECT_FLOAT_EQ(4.0f, v3.z());
    EXPECT_FLOAT_EQ(4.0f, v3.w());
}

TEST(Vector4AlignedTests, SubtractionAssignmentOperator)
{
    Vector<4, float, Qualifier::Aligned> v1(5.0f, 6.0f, 7.0f, 8.0f);
    Vector<4, float, Qualifier::Aligned> v2(1.0f, 2.0f, 3.0f, 4.0f);
    v1 -= v2;
    EXPECT_FLOAT_EQ(4.0f, v1.x());
    EXPECT_FLOAT_EQ(4.0f, v1.y());
    EXPECT_FLOAT_EQ(4.0f, v1.z());
    EXPECT_FLOAT_EQ(4.0f, v1.w());
}

TEST(Vector4AlignedTests, MultiplicationOperator)
{
    Vector<4, float, Qualifier::Aligned> v1(1.0f, 2.0f, 3.0f, 4.0f);
    Vector<4, float, Qualifier::Aligned> v2(5.0f, 6.0f, 7.0f, 8.0f);
    Vector<4, float, Qualifier::Aligned> v3 = v1 * v2;
    EXPECT_FLOAT_EQ(5.0f, v3.x());
    EXPECT_FLOAT_EQ(12.0f, v3.y());
    EXPECT_FLOAT_EQ(21.0f, v3.z());
    EXPECT_FLOAT_EQ(32.0f, v3.w());
}

TEST(Vector4AlignedTests, MultiplicationAssignmentOperator)
{
    Vector<4, float, Qualifier::Aligned> v1(1.0f, 2.0f, 3.0f, 4.0f);
    Vector<4, float, Qualifier::Aligned> v2(5.0f, 6.0f, 7.0f, 8.0f);
    v1 *= v2;
    EXPECT_FLOAT_EQ(5.0f, v1.x());
    EXPECT_FLOAT_EQ(12.0f, v1.y());
    EXPECT_FLOAT_EQ(21.0f, v1.z());
    EXPECT_FLOAT_EQ(32.0f, v1.w());
}

TEST(Vector4AlignedTests, MultiplicationOperatorWithScalar)
{
    Vector<4, float, Qualifier::Aligned> v1(1.0f, 2.0f, 3.0f, 4.0f);
    Vector<4, float, Qualifier::Aligned> v2 = v1 * 2.0f;
    EXPECT_FLOAT_EQ(2.0f, v2.x());
    EXPECT_FLOAT_EQ(4.0f, v2.y());
    EXPECT_FLOAT_EQ(6.0f, v2.z());
    EXPECT_FLOAT_EQ(8.0f, v2.w());
}

TEST(Vector4AlignedTests, MultiplicationOperatorWithScalarOnRightSide)
{
    Vector<4, float, Qualifier::Aligned> v1(1.0f, 2.0f, 3.0f, 4.0f);
    Vector<4, float, Qualifier::Aligned> v2 = 2.0f * v1;
    EXPECT_FLOAT_EQ(2.0f, v2.x());
    EXPECT_FLOAT_EQ(4.0f, v2.y());
    EXPECT_FLOAT_EQ(6.0f, v2.z());
    EXPECT_FLOAT_EQ(8.0f, v2.w());
}

TEST(Vector4AlignedTests, MultiplicationAssignmentOperatorWithScalar)
{
    Vector<4, float, Qualifier::Aligned> v1(1.0f, 2.0f, 3.0f, 4.0f);
    v1 *= 2.0f;
    EXPECT_FLOAT_EQ(2.0f, v1.x());
    EXPECT_FLOAT_EQ(4.0f, v1.y());
    EXPECT_FLOAT_EQ(6.0f, v1.z());
    EXPECT_FLOAT_EQ(8.0f, v1.w());
}

TEST(Vector4AlignedTests, DivisionOperatorWithScalar)
{
    Vector<4, float, Qualifier::Aligned> v1(2.0f, 4.0f, 6.0f, 8.0f);
    Vector<4, float, Qualifier::Aligned> v2 = v1 / 2.0f;
    EXPECT_FLOAT_EQ(1.0f, v2.x());
    EXPECT_FLOAT_EQ(2.0f, v2.y());
    EXPECT_FLOAT_EQ(3.0f, v2.z());
    EXPECT_FLOAT_EQ(4.0f, v2.w());
}

TEST(Vector4AlignedTests, DivisionAssignmentOperatorWithScalar)
{
    Vector<4, float, Qualifier::Aligned> v1(2.0f, 4.0f, 6.0f, 8.0f);
    v1 /= 2.0f;
    EXPECT_FLOAT_EQ(1.0f, v1.x());
    EXPECT_FLOAT_EQ(2.0f, v1.y());
    EXPECT_FLOAT_EQ(3.0f, v1.z());
    EXPECT_FLOAT_EQ(4.0f, v1.w());
}

TEST(Vector4AlignedTests, EqualityOperator)
{
    Vector<4, float, Qualifier::Aligned> v1(1.0f, 2.0f, 3.0f, 4.0f);
    Vector<4, float, Qualifier::Aligned> v2(1.0f, 2.0f, 3.0f, 4.0f);
    Vector<4, float, Qualifier::Aligned> v3(5.0f, 6.0f, 7.0f, 8.0f);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 == v3);
}

TEST(Vector4AlignedTests, InequalityOperator)
{
    Vector<4, float, Qualifier::Aligned> v1(1.0f, 2.0f, 3.0f, 4.0f);
    Vector<4, float, Qualifier::Aligned> v2(1.0f, 2.0f, 3.0f, 4.0f);
    Vector<4, float, Qualifier::Aligned> v3(5.0f, 6.0f, 7.0f, 8.0f);
    EXPECT_FALSE(v1 != v2);
    EXPECT_TRUE(v1 != v3);
}

TEST(Vector4AlignedTests, DotProduct)
{
    Vector<4, float, Qualifier::Aligned> v1(1.0f, 2.0f, 3.0f, 4.0f);
    Vector<4, float, Qualifier::Aligned> v2(5.0f, 6.0f, 7.0f, 8.0f);
    float result = v1.Dot(v2);
    EXPECT_FLOAT_EQ(70.0f, result);
}

TEST(Vector4AlignedTests, LengthSquared)
{
    Vector<4, float, Qualifier::Aligned> v(1.0f, 2.0f, 3.0f, 4.0f);
    float result = v.LengthSquared();
    EXPECT_FLOAT_EQ(30.0f, result);
}
