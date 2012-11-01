#ifndef SPRITEINFO_H
#define SPRITEINFO_H

#include <string>
#include "TransformInfo.h"
#include "Rect.h"

using namespace std;

struct SpriteInfo
{
public:
	int				id;
	string			textureFilePath;
	int				textureIndex;
	bool			visible;
	TransformInfo	transformInfo;
	float			bwFraction;
	float			sepiaFraction;
	float			fadeToBlackFraction;

	// The texture rect is specifying x and y-offset,
	// and width and height in pixels. Defaults to the
	// loaded texture width and height when being
	// assigned an id.
	Rect			textureRect;	

	//Color Overlay
	float	overlay[4];
	
	SpriteInfo()
	{
		textureFilePath = "";
		textureIndex = -1;
		visible = true;
		transformInfo.rotation[0] = 0.0f;
		transformInfo.rotation[1] = 0.0f;
		transformInfo.rotation[2] = 0.0f;
		transformInfo.translation[0] = 0.0f;
		transformInfo.translation[1] = 0.0f;
		transformInfo.translation[2] = 0.0f;
		transformInfo.scale[0] = 0.0f;
		transformInfo.scale[1] = 0.0f;
		transformInfo.scale[2] = 0.0f;
		textureRect.width = 0;
		textureRect.height = 0;
		bwFraction = 0;
		sepiaFraction = 0;
		fadeToBlackFraction = 0;
		overlay[0] = overlay[1] = overlay[2] = overlay[3] = 0;
	}

	SpriteInfo( string p_textureFilePath )
	{
		SpriteInfo();
		textureFilePath = p_textureFilePath;
	}

};

#endif