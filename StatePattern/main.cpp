#include "Game.h"
#include <Windows.h>
#include <vector>

HANDLE hConsole;

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

struct Circle
{
	Vector2 c;
	float	r;
	
	Circle(Vector2 p_c, float p_r)
	{
		c = p_c;
		r = p_r;
	}

	bool collidesWith(Circle p_other)
	{
		Vector2 diff = c - p_other.c;
		float distSqr = diff.lengthSquared();
		float totalR = r+p_other.r;
		if (distSqr < totalR * totalR)
			return true;
		return false;
	}
};

bool testVector2()
{
	vector<bool> results;
	Vector2 v1(10, 5);
	Vector2 v2(1, 2);
	Vector2 v3(4, 3);

	v1 += v2;
	results.push_back(v1 == Vector2(11, 7));

	v1 -= v2;
	results.push_back(v1 == Vector2(10, 5));

	v1 = v1 + v2;
	results.push_back(v1 == Vector2(11, 7));

	v1 = v1 - v2;
	results.push_back(v1 == Vector2(10, 5));

	v1 *= 10;
	results.push_back(v1 == Vector2(100, 50));

	v1 /= 10;
	results.push_back(v1 == Vector2(10, 5));

	v1 = v1 / 10;
	results.push_back(v1 == Vector2(1, 0.5f));

	v1 = v1 * 10;
	results.push_back(v1 == Vector2(10, 5));

	float dot = v1.dot(v2);
	results.push_back(dot == 20);

	float cross = v1.cross(v2);
	results.push_back(cross == 15);

	float l = v3.length();
	results.push_back(l == 5);

	l = v2.lengthSquared();
	results.push_back(l == 5);

	for (int i = 0; i < results.size(); i++)
	{
		SetConsoleTextAttribute(hConsole, 7);
		cout << "Test " << i + 1 << ": ";
		if (results[i])
		{
			SetConsoleTextAttribute(hConsole, 10);
			cout << "Succeeded" << endl;
		}
		else
		{
			SetConsoleTextAttribute(hConsole, 4);
			cout << "Failed" << endl;
		}
	}
	return 0;
}

bool testVector3()
{
	vector<bool> results;
	Vector3 v1(4, 3, 1);
	Vector3 v2(1, 2, 3);

	v1 += v2;
	results.push_back(v1 == Vector3(5, 5, 4));

	v1 -= v2;
	results.push_back(v1 == Vector3(4, 3, 1));

	v1 = v1 + v2;
	results.push_back(v1 == Vector3(5, 5, 4));

	v1 = v1 - v2;
	results.push_back(v1 == Vector3(4, 3, 1));

	v1 *= 10;
	results.push_back(v1 == Vector3(40, 30, 10));

	v1 /= 10;
	results.push_back(v1 == Vector3(4, 3, 1));

	v1 = v1 / 10;
	results.push_back(v1 == Vector3(0.4f, 0.3f, 0.1f));

	v1 = v1 * 10;
	results.push_back(v1 == Vector3(4, 3, 1));

	float dot = v1.dot(v2);
	results.push_back(dot == 13);

	Vector3 cross = v1.cross(v2);
	results.push_back(cross == Vector3(7, -11, 5));

	float l = v1.length();
	results.push_back(l == sqrt(26.0f));

	l = v1.lengthSquared();
	results.push_back(l == 26);

	for (int i = 0; i < results.size(); i++)
	{
		SetConsoleTextAttribute(hConsole, 7);
		cout << "Test " << i + 1 << ": ";
		if (results[i])
		{
			SetConsoleTextAttribute(hConsole, 10);
			cout << "Succeeded" << endl;
		}
		else
		{
			SetConsoleTextAttribute(hConsole, 4);
			cout << "Failed" << endl;
		}
	}
	return 0;
}

int main()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	testVector3();
	Circle c1(Vector2(-1.9f, 0), 3);
	Circle c2(Vector2(3, 0), 2);

	return c1.collidesWith(c2);
}