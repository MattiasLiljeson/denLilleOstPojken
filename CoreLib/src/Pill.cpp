#include "Pill.h"

Pill::Pill(SpriteInfo* p_spriteInfo, Tile* p_tile): GameObject(p_spriteInfo)
{
	if (p_spriteInfo)
	{
		TilePosition t = p_tile->getTilePosition();
		float w = p_tile->getWidth();
		float h = p_tile->getHeight();
		p_spriteInfo->transformInfo.translation[TransformInfo::X] = t.x * w + w * 0.5f;
		p_spriteInfo->transformInfo.translation[TransformInfo::Y] = t.y * h + h * 0.5f;
		p_spriteInfo->transformInfo.scale[TransformInfo::X] = w * 0.3f;
		p_spriteInfo->transformInfo.scale[TransformInfo::Y] = h * 0.3f;
	}
}