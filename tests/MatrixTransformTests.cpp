#include <gtest/gtest.h>
#include <PulsarionMath/Math.hpp>

using namespace Pulsarion;

class MatrixTransformTest : public ::testing::Test
{
protected:
	Mat4 matrix;
	Vec3 translation;
	Vec3 scale;

	// Two different ways to represent rotation
	float rotationX;
	float rotationY;
	float rotationZ;

	float rotation;
	Vec3 rotationAxis;

	void SetUp() override
	{
		matrix.Identity(); // Reset matrix

		translation = Vec3(1.0f, 2.0f, 3.0f);
		scale = Vec3(4.0f, 5.0f, 6.0f);

		rotationX = 1.0f;
		rotationY = 2.0f;
		rotationZ = 3.0f;

		rotation = Math::Constants<float>::Pi;
		rotationAxis = Vec3(1.0f, 0.0f, 0.0f);
	}
};

TEST_F(MatrixTransformTest, HandlesTranslation)
{
	const auto result = Math::MatrixTranslate(translation, matrix);

	EXPECT_FLOAT_EQ(result.data[0], 1.0f);
	EXPECT_FLOAT_EQ(result.data[1], 0.0f);
	EXPECT_FLOAT_EQ(result.data[2], 0.0f);
	EXPECT_FLOAT_EQ(result.data[3], 0.0f);
	EXPECT_FLOAT_EQ(result.data[4], 0.0f);
	EXPECT_FLOAT_EQ(result.data[5], 1.0f);
	EXPECT_FLOAT_EQ(result.data[6], 0.0f);
	EXPECT_FLOAT_EQ(result.data[7], 0.0f);
	EXPECT_FLOAT_EQ(result.data[8], 0.0f);
	EXPECT_FLOAT_EQ(result.data[9], 0.0f);
	EXPECT_FLOAT_EQ(result.data[10], 1.0f);
	EXPECT_FLOAT_EQ(result.data[11], 0.0f);
	EXPECT_FLOAT_EQ(result.data[12], 1.0f);
	EXPECT_FLOAT_EQ(result.data[13], 2.0f);
	EXPECT_FLOAT_EQ(result.data[14], 3.0f);
	EXPECT_FLOAT_EQ(result.data[15], 1.0f);

	const auto result2 = result * float4(0.0f, 0.0f, 0.0, 1.0f);
	// Should equal the translation, since we're translating the origin
	EXPECT_FLOAT_EQ(result2.x, translation.x);
	EXPECT_FLOAT_EQ(result2.y, translation.y);
	EXPECT_FLOAT_EQ(result2.z, translation.z);
	EXPECT_FLOAT_EQ(result2.w, 1.0f);

	const auto result3 = result * float4(1.0f, 1.0f, 1.0, 1.0f);
	// Should equal the translation + 1, since all three position components are 1
	EXPECT_FLOAT_EQ(result3.x, translation.x + 1.0f);
	EXPECT_FLOAT_EQ(result3.y, translation.y + 1.0f);
	EXPECT_FLOAT_EQ(result3.z, translation.z + 1.0f);
	EXPECT_FLOAT_EQ(result3.w, 1.0f);
}

TEST_F(MatrixTransformTest, HandlesScaling)
{
	const auto result = Math::MatrixScale(scale, matrix);

	EXPECT_FLOAT_EQ(result.data[0], 4.0f);
	EXPECT_FLOAT_EQ(result.data[1], 0.0f);
	EXPECT_FLOAT_EQ(result.data[2], 0.0f);
	EXPECT_FLOAT_EQ(result.data[3], 0.0f);
	EXPECT_FLOAT_EQ(result.data[4], 0.0f);
	EXPECT_FLOAT_EQ(result.data[5], 5.0f);
	EXPECT_FLOAT_EQ(result.data[6], 0.0f);
	EXPECT_FLOAT_EQ(result.data[7], 0.0f);
	EXPECT_FLOAT_EQ(result.data[8], 0.0f);
	EXPECT_FLOAT_EQ(result.data[9], 0.0f);
	EXPECT_FLOAT_EQ(result.data[10], 6.0f);
	EXPECT_FLOAT_EQ(result.data[11], 0.0f);
	EXPECT_FLOAT_EQ(result.data[12], 0.0f);
	EXPECT_FLOAT_EQ(result.data[13], 0.0f);
	EXPECT_FLOAT_EQ(result.data[14], 0.0f);
	EXPECT_FLOAT_EQ(result.data[15], 1.0f);

	const auto result2 = result * float4(0.0f, 0.0f, 0.0, 1.0f);
	// Should equal 0, since we're scaling the origin
	EXPECT_FLOAT_EQ(result2.x, 0.0f);
	EXPECT_FLOAT_EQ(result2.y, 0.0f);
	EXPECT_FLOAT_EQ(result2.z, 0.0f);
	EXPECT_FLOAT_EQ(result2.w, 1.0f);

	const auto result3 = result * float4(1.0f, 1.0f, 1.0, 1.0f);
	// Should equal the scale, since all three position components are 1
	EXPECT_FLOAT_EQ(result3.x, scale.x);
	EXPECT_FLOAT_EQ(result3.y, scale.y);
	EXPECT_FLOAT_EQ(result3.z, scale.z);
	EXPECT_FLOAT_EQ(result3.w, 1.0f);
}

TEST_F(MatrixTransformTest, HandlesRotation)
{
	// X Rotation
	const auto result = Math::MatrixRotateX(rotationX, matrix);

	EXPECT_FLOAT_EQ(result.data[0], 1.0f);
	EXPECT_FLOAT_EQ(result.data[1], 0.0f);
	EXPECT_FLOAT_EQ(result.data[2], 0.0f);
	EXPECT_FLOAT_EQ(result.data[3], 0.0f);
	EXPECT_FLOAT_EQ(result.data[4], 0.0f);
	EXPECT_FLOAT_EQ(result.data[5], Math::Cos(rotationX));
	EXPECT_FLOAT_EQ(result.data[6], Math::Sin(rotationX));
	EXPECT_FLOAT_EQ(result.data[7], 0.0f);
	EXPECT_FLOAT_EQ(result.data[8], 0.0f);
	EXPECT_FLOAT_EQ(result.data[9], -Math::Sin(rotationX));
	EXPECT_FLOAT_EQ(result.data[10], Math::Cos(rotationX));
	EXPECT_FLOAT_EQ(result.data[11], 0.0f);
	EXPECT_FLOAT_EQ(result.data[12], 0.0f);
	EXPECT_FLOAT_EQ(result.data[13], 0.0f);
	EXPECT_FLOAT_EQ(result.data[14], 0.0f);
	EXPECT_FLOAT_EQ(result.data[15], 1.0f);

	const auto result2 = result * float4(0.0f, 0.0f, 0.0, 1.0f);
	// Should equal 0, since we're rotating the origin
	EXPECT_FLOAT_EQ(result2.x, 0.0f);
	EXPECT_FLOAT_EQ(result2.y, 0.0f);
	EXPECT_FLOAT_EQ(result2.z, 0.0f);
	EXPECT_FLOAT_EQ(result2.w, 1.0f);

	const auto result3 = result * float4(1.0f, 1.0f, 1.0, 1.0f);
	EXPECT_FLOAT_EQ(result3.x, 1.0f);
	EXPECT_FLOAT_EQ(result3.y, Math::Cos(rotationX) - Math::Sin(rotationX));
	EXPECT_FLOAT_EQ(result3.z, Math::Sin(rotationX) + Math::Cos(rotationX));
	EXPECT_FLOAT_EQ(result3.w, 1.0f);

	// Y Rotation
	const auto result4 = Math::MatrixRotateY(rotationY, matrix);

	EXPECT_FLOAT_EQ(result4.data[0], Math::Cos(rotationY));
	EXPECT_FLOAT_EQ(result4.data[1], 0.0f);
	EXPECT_FLOAT_EQ(result4.data[2], -Math::Sin(rotationY));
	EXPECT_FLOAT_EQ(result4.data[3], 0.0f);
	EXPECT_FLOAT_EQ(result4.data[4], 0.0f);
	EXPECT_FLOAT_EQ(result4.data[5], 1.0f);
	EXPECT_FLOAT_EQ(result4.data[6], 0.0f);
	EXPECT_FLOAT_EQ(result4.data[7], 0.0f);
	EXPECT_FLOAT_EQ(result4.data[8], Math::Sin(rotationY));
	EXPECT_FLOAT_EQ(result4.data[9], 0.0f);
	EXPECT_FLOAT_EQ(result4.data[10], Math::Cos(rotationY));
	EXPECT_FLOAT_EQ(result4.data[11], 0.0f);
	EXPECT_FLOAT_EQ(result4.data[12], 0.0f);
	EXPECT_FLOAT_EQ(result4.data[13], 0.0f);
	EXPECT_FLOAT_EQ(result4.data[14], 0.0f);
	EXPECT_FLOAT_EQ(result4.data[15], 1.0f);
		
	const auto result5 = result4 * float4(0.0f, 0.0f, 0.0, 1.0f);
	// Should equal 0, since we're rotating the origin
	EXPECT_FLOAT_EQ(result5.x, 0.0f);
	EXPECT_FLOAT_EQ(result5.y, 0.0f);
	EXPECT_FLOAT_EQ(result5.z, 0.0f);
	EXPECT_FLOAT_EQ(result5.w, 1.0f);
	
	const auto result6 = result4 * float4(1.0f, 1.0f, 1.0, 1.0f);
	EXPECT_FLOAT_EQ(result6.x, Math::Cos(rotationY) + Math::Sin(rotationY));
	EXPECT_FLOAT_EQ(result6.y, 1.0f);
	EXPECT_FLOAT_EQ(result6.z, -Math::Sin(rotationY) + Math::Cos(rotationY));
	EXPECT_FLOAT_EQ(result6.w, 1.0f);

	// Z Rotation
	const auto result7 = Math::MatrixRotateZ(rotationZ, matrix);
	
	EXPECT_FLOAT_EQ(result7.data[0], Math::Cos(rotationZ));
	EXPECT_FLOAT_EQ(result7.data[1], Math::Sin(rotationZ));
	EXPECT_FLOAT_EQ(result7.data[2], 0.0f);
	EXPECT_FLOAT_EQ(result7.data[3], 0.0f);
	EXPECT_FLOAT_EQ(result7.data[4], -Math::Sin(rotationZ));
	EXPECT_FLOAT_EQ(result7.data[5], Math::Cos(rotationZ));
	EXPECT_FLOAT_EQ(result7.data[6], 0.0f);
	EXPECT_FLOAT_EQ(result7.data[7], 0.0f);
	EXPECT_FLOAT_EQ(result7.data[8], 0.0f);
	EXPECT_FLOAT_EQ(result7.data[9], 0.0f);
	EXPECT_FLOAT_EQ(result7.data[10], 1.0f);
	EXPECT_FLOAT_EQ(result7.data[11], 0.0f);
	EXPECT_FLOAT_EQ(result7.data[12], 0.0f);
	EXPECT_FLOAT_EQ(result7.data[13], 0.0f);
	EXPECT_FLOAT_EQ(result7.data[14], 0.0f);
	EXPECT_FLOAT_EQ(result7.data[15], 1.0f);

	const auto result8 = result7 * float4(0.0f, 0.0f, 0.0, 1.0f);
	// Should equal 0, since we're rotating the origin
	EXPECT_FLOAT_EQ(result8.x, 0.0f);
	EXPECT_FLOAT_EQ(result8.y, 0.0f);
	EXPECT_FLOAT_EQ(result8.z, 0.0f);
	EXPECT_FLOAT_EQ(result8.w, 1.0f);
		
	const auto result9 = result7 * float4(1.0f, 1.0f, 1.0, 1.0f);
	EXPECT_FLOAT_EQ(result9.x, Math::Cos(rotationZ) - Math::Sin(rotationZ));
	EXPECT_FLOAT_EQ(result9.y, Math::Sin(rotationZ) + Math::Cos(rotationZ));
	EXPECT_FLOAT_EQ(result9.z, 1.0f);
	EXPECT_FLOAT_EQ(result9.w, 1.0f);
}

TEST_F(MatrixTransformTest, HandlesAxisRotation)
{
	const auto result = Math::MatrixRotate(rotation, rotationAxis, matrix);

	// Rotation of 'rotation' radians around the X axis
	EXPECT_FLOAT_EQ(result.data[0], 1.0f);
	EXPECT_FLOAT_EQ(result.data[1], 0.0f);
	EXPECT_FLOAT_EQ(result.data[2], 0.0f);
	EXPECT_FLOAT_EQ(result.data[3], 0.0f);
	EXPECT_FLOAT_EQ(result.data[4], 0.0f);
	EXPECT_FLOAT_EQ(result.data[5], Math::Cos(rotation));
	EXPECT_FLOAT_EQ(result.data[6], Math::Sin(rotation));
	EXPECT_FLOAT_EQ(result.data[7], 0.0f);
	EXPECT_FLOAT_EQ(result.data[8], 0.0f);
	EXPECT_FLOAT_EQ(result.data[9], -Math::Sin(rotation));
	EXPECT_FLOAT_EQ(result.data[10], Math::Cos(rotation));
	EXPECT_FLOAT_EQ(result.data[11], 0.0f);
	EXPECT_FLOAT_EQ(result.data[12], 0.0f);
	EXPECT_FLOAT_EQ(result.data[13], 0.0f);
	EXPECT_FLOAT_EQ(result.data[14], 0.0f);
	EXPECT_FLOAT_EQ(result.data[15], 1.0f);

	const auto result2 = result * float4(0.0f, 0.0f, 0.0, 1.0f);
	// Should equal 0, since we're rotating the origin
	EXPECT_FLOAT_EQ(result2.x, 0.0f);
	EXPECT_FLOAT_EQ(result2.y, 0.0f);
	EXPECT_FLOAT_EQ(result2.z, 0.0f);
	EXPECT_FLOAT_EQ(result2.w, 1.0f);

	const auto result3 = result * float4(1.0f, 1.0f, 1.0, 1.0f);
	EXPECT_FLOAT_EQ(result3.x, 1.0f);
	EXPECT_FLOAT_EQ(result3.y, Math::Cos(rotation) - Math::Sin(rotation));
	EXPECT_FLOAT_EQ(result3.z, Math::Sin(rotation) + Math::Cos(rotation));
	EXPECT_FLOAT_EQ(result3.w, 1.0f);
}

TEST_F(MatrixTransformTest, HandlesCompositeTransform)
{
	// Transform by translation, then rotation, then scale

	const auto translationMatrix = Math::MatrixTranslate(translation, matrix);
	const auto rotationMatrix = Math::MatrixRotate(rotation, rotationAxis, matrix);
	const auto scaleMatrix = Math::MatrixScale(scale, matrix);

	const auto result = translationMatrix * rotationMatrix * scaleMatrix;
	auto result2 = Math::MatrixTranslate(translation, matrix);
	result2 = Math::MatrixRotate(rotation, rotationAxis, result2);
	result2 = Math::MatrixScale(scale, result2);

	EXPECT_FLOAT_EQ(result.data[0], result2.data[0]);
	EXPECT_FLOAT_EQ(result.data[1], result2.data[1]);
	EXPECT_FLOAT_EQ(result.data[2], result2.data[2]);
	EXPECT_FLOAT_EQ(result.data[3], result2.data[3]);
	EXPECT_FLOAT_EQ(result.data[4], result2.data[4]);
	EXPECT_FLOAT_EQ(result.data[5], result2.data[5]);
	EXPECT_FLOAT_EQ(result.data[6], result2.data[6]);
	EXPECT_FLOAT_EQ(result.data[7], result2.data[7]);
	EXPECT_FLOAT_EQ(result.data[8], result2.data[8]);
	EXPECT_FLOAT_EQ(result.data[9], result2.data[9]);
	EXPECT_FLOAT_EQ(result.data[10], result2.data[10]);
	EXPECT_FLOAT_EQ(result.data[11], result2.data[11]);
	EXPECT_FLOAT_EQ(result.data[12], result2.data[12]);
	EXPECT_FLOAT_EQ(result.data[13], result2.data[13]);
	EXPECT_FLOAT_EQ(result.data[14], result2.data[14]);
	EXPECT_FLOAT_EQ(result.data[15], result2.data[15]);

	const auto result3 = result * float4(0.0f, 0.0f, 0.0, 1.0f);
	// Should equal translation, since we're transforming the origin
	EXPECT_FLOAT_EQ(result3.x, translation.x);
	EXPECT_FLOAT_EQ(result3.y, translation.y);
	EXPECT_FLOAT_EQ(result3.z, translation.z);
	EXPECT_FLOAT_EQ(result3.w, 1.0f);

	const auto result4 = result * float4(1.0f, 1.0f, 1.0, 1.0f);
	EXPECT_FLOAT_EQ(result4.x, scale.x + translation.x);
	EXPECT_FLOAT_EQ(result4.y, scale.y * (Math::Cos(rotation) - Math::Sin(rotation)) + translation.y);
	EXPECT_FLOAT_EQ(result4.z, scale.z * (Math::Sin(rotation) + Math::Cos(rotation)) + translation.z);
	EXPECT_FLOAT_EQ(result4.w, 1.0f);
}
