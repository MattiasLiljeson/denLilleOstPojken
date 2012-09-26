#ifndef VECTOR2_H
#define VECTOR2_H

struct Vector2
{
	float x;
	float y;

	Vector2()
	{
		x = y = 0;
	}
	Vector2(float p_x, float p_y)
	{
		x = p_x;
		y = p_y;
	}
	Vector2& operator+(const Vector2& p_other)
	{
		x += p_other.x;
		y += p_other.y;
		return (*this);
	}
	Vector2& operator-(const Vector2& p_other)
	{
		x -= p_other.x;
		y -= p_other.y;
		return (*this);
	}
	Vector2& operator*(const float& p_factor)
	{
		x *= p_factor;
		y *= p_factor;
		return (*this);
	}
	Vector2& operator/(const float& p_factor)
	{
		x /= p_factor;
		y /= p_factor;
		return (*this);
	}
	Vector2& operator+=(const Vector2& p_other)
	{
		x += p_other.x;
		y += p_other.y;
		return (*this);
	}
	Vector2& operator-=(const Vector2& p_other)
	{
		x -= p_other.x;
		y -= p_other.y;
		return (*this);
	}
	Vector2& operator *=(const float& p_factor)
	{
		x *= p_factor;
		y *= p_factor;
		return (*this);
	}
	Vector2& operator /=(const float& p_factor)
	{
		x /= p_factor;
		y /= p_factor;
		return (*this);
	}
	bool operator==(const Vector2& p_other)
	{
		return x == p_other.x && y == p_other.y; 
	}
	bool operator!=(const Vector2& p_other)
	{
		return x != p_other.x || y != p_other.y; 
	}
	float dot(Vector2 p_other)
	{
		return x * p_other.x + y * p_other.y;
	}
	float cross(Vector2 p_other)
	{
		return x * p_other.y - p_other.x * y;
	}
	float length()
	{
		return sqrt(x*x + y*y);
	}
	float lengthSquared()
	{
		return x*x+y*y;
	}
};

#endif