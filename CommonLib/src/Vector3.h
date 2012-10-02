#ifndef VECTOR3_H
#define VECTOR3_H

struct fVector3
{
	float x;
	float y;
	float z;

	fVector3()
	{
		x = y = z = 0;
	}
	fVector3(float p_x, float p_y, float p_z)
	{
		x = p_x;
		y = p_y;
		z = p_z;
	}
	fVector3 operator+(const fVector3& p_other)
	{
		float nx = x + p_other.x;
		float ny = y + p_other.y;
		float nz = z + p_other.z;
		return fVector3(nx, ny, nz);
	}
	fVector3 operator-(const fVector3& p_other)
	{
		float nx = x - p_other.x;
		float ny = y - p_other.y;
		float nz = z - p_other.z;
		return fVector3(nx, ny, nz);
	}
	fVector3 operator*(const float& p_factor)
	{
		float nx = x * p_factor;
		float ny = y * p_factor;
		float nz = z * p_factor;
		return fVector3(nx, ny, nz);
	}
	fVector3 operator/(const float& p_factor)
	{
		float nx = x / p_factor;
		float ny = y / p_factor;
		float nz = z / p_factor;
		return fVector3(nx, ny, nz);
	}
	fVector3& operator+=(const fVector3& p_other)
	{
		x += p_other.x;
		y += p_other.y;
		z += p_other.z;
		return (*this);
	}
	fVector3& operator-=(const fVector3& p_other)
	{
		x -= p_other.x;
		y -= p_other.y;
		z -= p_other.z;
		return (*this);
	}
	fVector3& operator *=(const float& p_factor)
	{
		x *= p_factor;
		y *= p_factor;
		z *= p_factor;
		return (*this);
	}
	fVector3& operator /=(const float& p_factor)
	{
		x /= p_factor;
		y /= p_factor;
		z /= p_factor;
		return (*this);
	}
	bool operator==(const fVector3& p_other)
	{
		return x == p_other.x && y == p_other.y && z == p_other.z; 
	}
	bool operator!=(const fVector3& p_other)
	{
		return x != p_other.x || y != p_other.y || z != p_other.z; 
	}
	float dot(fVector3 p_other)
	{
		return x * p_other.x + y * p_other.y + z * p_other.z;
	}
	fVector3 cross(fVector3 p_other)
	{
		float cx = y * p_other.z - z * p_other.y;
		float cy = z * p_other.x - x * p_other.z;
		float cz = x * p_other.y - y * p_other.x;
		return fVector3(cx, cy, cz);
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