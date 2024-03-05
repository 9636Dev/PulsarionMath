#include <gtest/gtest.h>

#include "PulsarionMath/Matrix.hpp"

using namespace Pulsarion::Math;

TEST(Matrix4x4Tests, DefaultConstructor)
{
    Matrix<4, 4, float> m;
    // Should be an identity matrix
    EXPECT_FLOAT_EQ(1.0f, m.Get(0, 0));
    EXPECT_FLOAT_EQ(0.0f, m.Get(0, 1));
    EXPECT_FLOAT_EQ(0.0f, m.Get(0, 2));
    EXPECT_FLOAT_EQ(0.0f, m.Get(0, 3));
    EXPECT_FLOAT_EQ(0.0f, m.Get(1, 0));
    EXPECT_FLOAT_EQ(1.0f, m.Get(1, 1));
    EXPECT_FLOAT_EQ(0.0f, m.Get(1, 2));
    EXPECT_FLOAT_EQ(0.0f, m.Get(1, 3));
    EXPECT_FLOAT_EQ(0.0f, m.Get(2, 0));
    EXPECT_FLOAT_EQ(0.0f, m.Get(2, 1));
    EXPECT_FLOAT_EQ(1.0f, m.Get(2, 2));
    EXPECT_FLOAT_EQ(0.0f, m.Get(2, 3));
    EXPECT_FLOAT_EQ(0.0f, m.Get(3, 0));
    EXPECT_FLOAT_EQ(0.0f, m.Get(3, 1));
    EXPECT_FLOAT_EQ(0.0f, m.Get(3, 2));
    EXPECT_FLOAT_EQ(1.0f, m.Get(3, 3));
}

TEST(Matrix4x4Tests, Transpose)
{
    Matrix<4, 4, float> m(1.0f, 2.0f, 3.0f, 4.0f,
                         5.0f, 6.0f, 7.0f, 8.0f,
                         9.0f, 10.0f, 11.0f, 12.0f,
                         13.0f, 14.0f, 15.0f, 16.0f);
    m.TransposeInPlace();
    EXPECT_FLOAT_EQ(1.0f, m.Get(0, 0));
    EXPECT_FLOAT_EQ(5.0f, m.Get(0, 1));
    EXPECT_FLOAT_EQ(9.0f, m.Get(0, 2));
    EXPECT_FLOAT_EQ(13.0f, m.Get(0, 3));
    EXPECT_FLOAT_EQ(2.0f, m.Get(1, 0));
    EXPECT_FLOAT_EQ(6.0f, m.Get(1, 1));
    EXPECT_FLOAT_EQ(10.0f, m.Get(1, 2));
    EXPECT_FLOAT_EQ(14.0f, m.Get(1, 3));
    EXPECT_FLOAT_EQ(3.0f, m.Get(2, 0));
    EXPECT_FLOAT_EQ(7.0f, m.Get(2, 1));
    EXPECT_FLOAT_EQ(11.0f, m.Get(2, 2));
    EXPECT_FLOAT_EQ(15.0f, m.Get(2, 3));
    EXPECT_FLOAT_EQ(4.0f, m.Get(3, 0));
    EXPECT_FLOAT_EQ(8.0f, m.Get(3, 1));
    EXPECT_FLOAT_EQ(12.0f, m.Get(3, 2));
    EXPECT_FLOAT_EQ(16.0f, m.Get(3, 3));
}

TEST(Matrix4x4Tests, MatrixMultiply)
{
    Matrix<4, 4, float> m1(1.0f, 2.0f, 3.0f, 4.0f,
                          5.0f, 6.0f, 7.0f, 8.0f,
                          9.0f, 10.0f, 11.0f, 12.0f,
                          13.0f, 14.0f, 15.0f, 16.0f);
    Matrix<4, 4, float> m2(1.0f, 2.0f, 3.0f, 4.0f,
                          5.0f, 6.0f, 7.0f, 8.0f,
                          9.0f, 10.0f, 11.0f, 12.0f,
                          13.0f, 14.0f, 15.0f, 16.0f);
    Matrix<4, 4, float> result = m1 * m2;

    EXPECT_FLOAT_EQ(90.0f, result.Get(0, 0));
    EXPECT_FLOAT_EQ(100.0f, result.Get(0, 1));
    EXPECT_FLOAT_EQ(110.0f, result.Get(0, 2));
    EXPECT_FLOAT_EQ(120.0f, result.Get(0, 3));
    EXPECT_FLOAT_EQ(202.0f, result.Get(1, 0));
    EXPECT_FLOAT_EQ(228.0f, result.Get(1, 1));
    EXPECT_FLOAT_EQ(254.0f, result.Get(1, 2));
    EXPECT_FLOAT_EQ(280.0f, result.Get(1, 3));
    EXPECT_FLOAT_EQ(314.0f, result.Get(2, 0));
    EXPECT_FLOAT_EQ(356.0f, result.Get(2, 1));
    EXPECT_FLOAT_EQ(398.0f, result.Get(2, 2));
    EXPECT_FLOAT_EQ(440.0f, result.Get(2, 3));
    EXPECT_FLOAT_EQ(426.0f, result.Get(3, 0));
    EXPECT_FLOAT_EQ(484.0f, result.Get(3, 1));
    EXPECT_FLOAT_EQ(542.0f, result.Get(3, 2));
    EXPECT_FLOAT_EQ(600.0f, result.Get(3, 3));
}

TEST(Matrix4x4Tests, VectorMultiply)
{
    Matrix<4, 4, float> m1(1.0f, 2.0f, 3.0f, 4.0f,
                            5.0f, 6.0f, 7.0f, 8.0f,
                            9.0f, 10.0f, 11.0f, 12.0f,
                            13.0f, 14.0f, 15.0f, 16.0f);
    Vector<4, float, Qualifier::Aligned> v(1.0f, 2.0f, 3.0f, 4.0f);

    Vector<4, float, Qualifier::Aligned> result = m1 * v;
    EXPECT_FLOAT_EQ(30.0f, result[0]);
    EXPECT_FLOAT_EQ(70.0f, result[1]);
    EXPECT_FLOAT_EQ(110.0f, result[2]);
    EXPECT_FLOAT_EQ(150.0f, result[3]);
}
