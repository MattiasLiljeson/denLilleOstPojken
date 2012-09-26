#ifndef SPRITEINFO_H
#define SPRITEINFO_H

#include <string>
#include "TransformInfo.h"

using namespace std;

struct SpriteInfo
{
public:
	int				id;
	string			textureFileName;
	int				textureIndex;
	bool			visible;
	TransformInfo	transformInfo;

	SpriteInfo()
	{
		textureFileName = "";
		textureIndex = -1;
		visible = true;
	}
};

#endif