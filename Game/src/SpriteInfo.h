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
	bool			visible;
	TransformInfo	transformInfo;
};

#endif