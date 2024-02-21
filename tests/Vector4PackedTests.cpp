#include <gtest/gtest.h>

#include "PulsarionMath/Vector.hpp"

using namespace Pulsarion::Math;

TEST(Vector4PackedTests, DefaultConstructor)
{
    Vector<4, float, Qualifier::Packed> v;
    EXPECT_FLOAT_EQ(0.0f, v.x());
    EXPECT_FLOAT_EQ(0.0f, v.y());
    EXPECT_FLOAT_EQ(0.0f, v.z());
    EXPECT_FLOAT_EQ(0.0f, v.w());
}

TEST(Vector4PackedTests, ConstructorWithValues)
{
    Vector<4, float, Qualifier::Packed> v(1.0f, 2.0f, 3.0f, 4.0f);
    EXPECT_FLOAT_EQ(1.0f, v.x());
    EXPECT_FLOAT_EQ(2.0f, v.y());
    EXPECT_FLOAT_EQ(3.0f, v.z());
    EXPECT_FLOAT_EQ(4.0f, v.w());
}

TEST(Vector4PackedTests, ConstructorWithScalar)
{
    Vector<4, float, Qualifier::Packed> v(1.0f);
    EXPECT_FLOAT_EQ(1.0f, v.x());
    EXPECT_FLOAT_EQ(1.0f, v.y());
    EXPECT_FLOAT_EQ(1.0f, v.z());
    EXPECT_FLOAT_EQ(1.0f, v.w());
}

TEST(Vector4PackedTests, CopyConstructor)
{
    Vector<4, float, Qualifier::Packed> v1(1.0f, 2.0f, 3.0f, 4.0f);
    Vector<4, float, Qualifier::Packed> v2(v1);
    EXPECT_FLOAT_EQ(1.0f, v2.x());
    EXPECT_FLOAT_EQ(2.0f, v2.y());
    EXPECT_FLOAT_EQ(3.0f, v2.z());
    EXPECT_FLOAT_EQ(4.0f, v2.w());
}

TEST(Vector4PackedTests, CopyAssignment)
{
    Vector<4, float, Qualifier::Packed> v1(1.0f, 2.0f, 3.0f, 4.0f);
    Vector<4, float, Qualifier::Packed> v2;
    v2 = v1;
    EXPECT_FLOAT_EQ(1.0f, v2.x());
    EXPECT_FLOAT_EQ(2.0f, v2.y());
    EXPECT_FLOAT_EQ(3.0f, v2.z());
    EXPECT_FLOAT_EQ(4.0f, v2.w());
}

TEST(Vector4PackedTests, MoveConstructor)
{
    Vector<4, float, Qualifier::Packed> v1(1.0f, 2.0f, 3.0f, 4.0f);
    // NOLINTNEXTLINE(performance-move-const-arg)
    Vector<4, float, Qualifier::Packed> v2(std::move(v1));
    EXPECT_FLOAT_EQ(1.0f, v2.x());
    EXPECT_FLOAT_EQ(2.0f, v2.y());
    EXPECT_FLOAT_EQ(3.0f, v2.z());
    EXPECT_FLOAT_EQ(4.0f, v2.w());
}

TEST(Vector4PackedTests, MoveAssignment)
{
    Vector<4, float, Qualifier::Packed> v1(1.0f, 2.0f, 3.0f, 4.0f);
    Vector<4, float, Qualifier::Packed> v2;
    // NOLINTNEXTLINE(performance-move-const-arg)
    v2 = std::move(v1);
    EXPECT_FLOAT_EQ(1.0f, v2.x());
    EXPECT_FLOAT_EQ(2.0f, v2.y());
    EXPECT_FLOAT_EQ(3.0f, v2.z());
    EXPECT_FLOAT_EQ(4.0f, v2.w());
}

TEST(Vector4PackedTests, AccessOperator)
{
    Vector<4, float, Qualifier::Packed> v(1.0f, 2.0f, 3.0f, 4.0f);
    EXPECT_FLOAT_EQ(1.0f, v[0]);
    EXPECT_FLOAT_EQ(2.0f, v[1]);
    EXPECT_FLOAT_EQ(3.0f, v[2]);
    EXPECT_FLOAT_EQ(4.0f, v[3]);
}

TEST(Vector4PackedTests, AccessOperatorConst)
{
    const Vector<4, float, Qualifier::Packed> v(1.0f, 2.0f, 3.0f, 4.0f);
    EXPECT_FLOAT_EQ(1.0f, v[0]);
    EXPECT_FLOAT_EQ(2.0f, v[1]);
    EXPECT_FLOAT_EQ(3.0f, v[2]);
    EXPECT_FLOAT_EQ(4.0f, v[3]);
}
