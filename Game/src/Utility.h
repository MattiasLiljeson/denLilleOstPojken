#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <vector>
#include <Windows.h>
#include <WindowsX.h>
#include <D3D11.h>
#include <D3DX11.h>
#include <D3DX10.h>
#include <string>
#include <fstream>
#include <ctime>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <GL\glew.h>
#include <GL\glfw.h>
#include <GL\wglew.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

using namespace std;

typedef D3DXVECTOR2	Vector2;
typedef D3DXVECTOR3 Vector3;
typedef D3DXVECTOR4 Vector4;
//typedef D3DXMATRIX  Matrix;
typedef POINT       Point;
const double PI = D3DX_PI;

struct Matrix: public D3DXMATRIX
{
	Matrix(): D3DXMATRIX()
	{
	}
	Matrix(const float* pf): D3DXMATRIX(pf)
	{
	}
	Matrix(float f11, float f12, float f13, float f14, float f21, float f22, float f23, float f24, float f31, float f32, float f33, float f34, float f41, float f42, float f43, float f44): 
		D3DXMATRIX(f11, f12, f13, f14, f21, f22, f23, f24, f31, f32, f33, f34, f41, f42, f43, f44)
	{
	}
	Vector3 GetLeft()
	{
		return -GetRight();
	}
	Vector3 GetRight()
	{
		return Vector3(_11, _12, _13);
	}
	Vector3 GetDown()
	{
		return -GetUp();
	}
	Vector3 GetUp()
	{
		return Vector3(_21, _22, _23);
	}
	Vector3 GetBackward()
	{
		return -GetForward();
	}
	Vector3 GetForward()
	{
		return Vector3(_31, _32, _33);
	}
	Vector3 GetTranslation()
	{
		return Vector3(_41, _42, _43);
	}
	void SetLeft(Vector3 pLeft)
	{
		SetRight(-pLeft);
	}
	void SetRight(Vector3 pRight)
	{
		m[0][0] = pRight.x;
		m[0][1] = pRight.y;
		m[0][2] = pRight.z;
	}
	void SetDown(Vector3 pDown)
	{
		SetUp(-pDown);
	}
	void SetUp(Vector3 pUp)
	{
		m[1][0] = pUp.x;
		m[1][1] = pUp.y;
		m[1][2] = pUp.z;
	}
	void SetBackward(Vector3 pBackward)
	{
		SetForward(-pBackward);
	}
	void SetForward(Vector3 pForward)
	{
		m[2][0] = pForward.x;
		m[2][1] = pForward.y;
		m[2][2] = pForward.z;
	}
	void SetTranslation(Vector3 pTranslation)
	{
		m[3][0] = pTranslation.x;
		m[3][1] = pTranslation.y;
		m[3][2] = pTranslation.z;
	}
	Matrix Inverse()
	{
		D3DXMATRIX mat(_11, _12, _13, _14, _21, _22, _23, _24, _31, _32, _33, _34, _41, _42, _43, _44);
		D3DXMatrixInverse(&mat, NULL, &mat);
		return Matrix(mat._11, mat._12, mat._13, mat._14, mat._21, mat._22, mat._23, mat._24, mat._31, mat._32, mat._33, mat._34, mat._41, mat._42, mat._43, mat._44);
	}
	Matrix Mul(Matrix pOther)
	{
		D3DXMATRIX mat(_11, _12, _13, _14, _21, _22, _23, _24, _31, _32, _33, _34, _41, _42, _43, _44);
		D3DXMATRIX mat2(pOther._11, pOther._12, pOther._13, pOther._14, pOther._21, pOther._22, pOther._23, pOther._24, pOther._31, pOther._32, pOther._33, pOther._34, pOther._41, pOther._42, pOther._43, pOther._44);
		D3DXMATRIX res = mat * mat2;
		return Matrix(res._11, res._12, res._13, res._14, res._21, res._22, res._23, res._24, res._31, res._32, res._33, res._34, res._41, res._42, res._43, res._44);
	}
};

float	DotProduct(const Vector3& v1, const Vector3& v2);
Vector3 CrossProduct(const Vector3& v1, const Vector3& v2);
float	Length(const Vector3& v);
float	Length(const Vector2& v);
float	LengthSquared(const Vector3& v);
float	LengthSquared(const Vector2& v);
void	Normalize(Vector3& v);
void	Rotate(Vector3& v, float Angle, Vector3 axis);
float	RandomFloat();
float	RandomFloat(float a, float b);
Vector3 RandomUnitVector3();
Vector4	Vec4MatrixMult(Vector4& vec, Matrix mat);
Vector3	Vec3Transform(Vector3& vec, Matrix mat);
Vector3	Vec3TransformNormal(Vector3& vec, Matrix mat);

D3DXMATRIX ToDxMatrix(Matrix pMatrix);
Matrix ToMatrix(D3DXMATRIX pMatrix);

struct SpriteVertex
{
	float x, y, z;
	float s, t;
	float padding[3];

	SpriteVertex(float p_x, float p_y, float p_z, float p_s, float p_t)
	{
		x = p_x;
		y = p_y;
		z = p_z;
		s = p_s;
		t = p_t;
	}
};


enum 
{
	GAME_OK, GAME_FAIL, GAME_OTHER
};

struct InputInfo
{
	enum
	{ 
		KEYUP, KEYDOWN, KEYRELEASED, KEYPRESSED 
	};
	enum
	{
		RIGHT, LEFT, UP, DOWN, SPACE, ESC, NUM_KEYS 
	};
	int keys[NUM_KEYS];
};


#endif