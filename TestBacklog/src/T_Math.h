#ifndef T_MATH_H
#define T_MATH_H

#include "gtest/gtest.h"
#include <Vector2.h>
#include <Vector3.h>
#include <Circle.h>

class T_Math : public ::testing::Test
{
protected:
	T_Math(){
	}
	virtual ~T_Math(){
	}
	virtual void SetUp(){
	}
	virtual void TearDown(){
	}
};

TEST(Math, Vector2)
{
	Vector2 v1(1, 2);
	Vector2 v2(3, 4);

	ASSERT_TRUE(v1 != v2);
	ASSERT_FALSE(v1 == v2);
	v1 += v2;
	ASSERT_TRUE(v1 == Vector2(4, 6));
	v1 -= v2;
	ASSERT_TRUE(v1 == Vector2(1, 2));
	v1 = v1 + v2;
	ASSERT_TRUE(v1 == Vector2(4, 6));
	v1 = v1 - v2;
	ASSERT_TRUE(v1 == Vector2(1, 2));
	v1 *= 2;
	ASSERT_TRUE(v1 == Vector2(2, 4));
	v1 = v1 * 2;
	ASSERT_TRUE(v1 == Vector2(4, 8));
	v1 /= 2;
	ASSERT_TRUE(v1 == Vector2(2, 4));
	v1 = v1 / 2;
	ASSERT_TRUE(v1 == Vector2(1, 2));
	float dot = v1.dot(v2);
	float cross = v1.cross(v2);
	ASSERT_TRUE(dot == 11);
	ASSERT_TRUE(cross == -2);
	ASSERT_TRUE(v2.length() == 5);
	ASSERT_TRUE(v2.lengthSquared() == 25);
}
TEST(Math, Vector3)
{
	Vector3 v1(1, 2, 3);
	Vector3 v2(4, 5, 6);

	ASSERT_TRUE(v1 != v2);
	ASSERT_FALSE(v1 == v2);
	v1 += v2;
	ASSERT_TRUE(v1 == Vector3(5, 7, 9));
	v1 -= v2;
	ASSERT_TRUE(v1 == Vector3(1, 2, 3));
	v1 = v1 + v2;
	ASSERT_TRUE(v1 == Vector3(5, 7, 9));
	v1 = v1 - v2;
	ASSERT_TRUE(v1 == Vector3(1, 2, 3));
	v1 *= 2;
	ASSERT_TRUE(v1 == Vector3(2, 4, 6));
	v1 = v1 * 2;
	ASSERT_TRUE(v1 == Vector3(4, 8, 12));
	v1 /= 2;
	ASSERT_TRUE(v1 == Vector3(2, 4, 6));
	v1 = v1 / 2;
	ASSERT_TRUE(v1 == Vector3(1, 2, 3));
	float dot = v1.dot(v2);
	Vector3 cross = v1.cross(v2);
	ASSERT_TRUE(dot == 32);
	ASSERT_TRUE(cross == Vector3(-3, 6, -3));
	ASSERT_TRUE(v1.length() == sqrt(14.0f));
	ASSERT_TRUE(v1.lengthSquared() == 14);
}
TEST(Math, CircleCollision)
{
	Circle c1(Vector2(0, 0), 2);
	Circle c2(Vector2(2, 3), 3);

	ASSERT_TRUE(c1.collidesWith(c2));
	c1.c = Vector2(-2, -3);
	ASSERT_FALSE(c1.collidesWith(c2));
}
#endif




//Template