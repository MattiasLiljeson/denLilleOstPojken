#ifndef VECTOR2_H
#define VECTOR2_H

struct fVector2
{
	float x;
	float y;

	fVector2()
	{
		x = y = 0;
	}
	fVector2(float p_x, float p_y)
	{
		x = p_x;
		y = p_y;
	}
	fVector2& operator+(const fVector2& p_other)
	{
		x += p_other.x;
		y += p_other.y;
		return (*this);
	}
	fVector2& operator-(const fVector2& p_other)
	{
		x -= p_other.x;
		y -= p_other.y;
		return (*this);
	}
	fVector2& operator*(const float& p_factor)
	{
		x *= p_factor;
		y *= p_factor;
		return (*this);
	}
	fVector2& operator/(const float& p_factor)
	{
		x /= p_factor;
		y /= p_factor;
		return (*this);
	}
	fVector2& operator+=(const fVector2& p_other)
	{
		x += p_other.x;
		y += p_other.y;
		return (*this);
	}
	fVector2& operator-=(const fVector2& p_other)
	{
		x -= p_other.x;
		y -= p_other.y;
		return (*this);
	}
	fVector2& operator *=(const float& p_factor)
	{
		x *= p_factor;
		y *= p_factor;
		return (*this);
	}
	fVector2& operator /=(const float& p_factor)
	{
		x /= p_factor;
		y /= p_factor;
		return (*this);
	}
	bool operator==(const fVector2& p_other)
	{
		return x == p_other.x && y == p_other.y; 
	}
	bool operator!=(const fVector2& p_other)
	{
		return x != p_other.x || y != p_other.y; 
	}
	float dot(fVector2 p_other)
	{
		return x * p_other.x + y * p_other.y;
	}
	float cross(fVector2 p_other)
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