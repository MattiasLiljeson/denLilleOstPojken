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