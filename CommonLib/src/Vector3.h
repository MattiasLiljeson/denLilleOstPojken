#ifndef VECTOR3_H
#define VECTOR3_H

struct Vector3
{
	float x;
	float y;
	float z;

	Vector3()
	{
		x = y = z = 0;
	}
	Vector3(float p_x, float p_y, float p_z)
	{
		x = p_x;
		y = p_y;
		z = p_z;
	}
	Vector3& operator+(const Vector3& p_other)
	{
		x += p_other.x;
		y += p_other.y;
		z += p_other.z;
		return (*this);
	}
	Vector3& operator-(const Vector3& p_other)
	{
		x -= p_other.x;
		y -= p_other.y;
		z -= p_other.z;
		return (*this);
	}
	Vector3& operator*(const float& p_factor)
	{
		x *= p_factor;
		y *= p_factor;
		z *= p_factor;
		return (*this);
	}
	Vector3& operator/(const float& p_factor)
	{
		x /= p_factor;
		y /= p_factor;
		z /= p_factor;
		return (*this);
	}
	Vector3& operator+=(const Vector3& p_other)
	{
		x += p_other.x;
		y += p_other.y;
		z += p_other.z;
		return (*this);
	}
	Vector3& operator-=(const Vector3& p_other)
	{
		x -= p_other.x;
		y -= p_other.y;
		z -= p_other.z;
		return (*this);
	}
	Vector3& operator *=(const float& p_factor)
	{
		x *= p_factor;
		y *= p_factor;
		z *= p_factor;
		return (*this);
	}
	Vector3& operator /=(const float& p_factor)
	{
		x /= p_factor;
		y /= p_factor;
		z /= p_factor;
		return (*this);
	}
	bool operator==(const Vector3& p_other)
	{
		return x == p_other.x && y == p_other.y && z == p_other.z; 
	}
	bool operator!=(const Vector3& p_other)
	{
		return x != p_other.x || y != p_other.y || z != p_other.z; 
	}
	float dot(Vector3 p_other)
	{
		return x * p_other.x + y * p_other.y + z * p_other.z;
	}
	Vector3 cross(Vector3 p_other)
	{
		float cx = y * p_other.z - z * p_other.y;
		float cy = z * p_other.x - x * p_other.z;
		float cz = x * p_other.y - y * p_other.x;
		return Vector3(cx, cy, cz);
	}
	float length()
	{
		return sqrt(x*x + y*y + z*z);
	}
	float lengthSquared()
	{
		return x*x+y*y+z*z;
	}
};

#endif