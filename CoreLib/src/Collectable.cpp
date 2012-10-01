#include "Collectable.h"

Collectable::Collectable(): GameObject(NULL, NULL)
{
}
Collectable::Collectable(SpriteInfo* p_spriteInfo): GameObject(p_spriteInfo, NULL)
{
}
Collectable::Collectable(SpriteInfo* p_spriteInfo, GameStats* p_gameStats): GameObject(p_spriteInfo, p_gameStats)
{
}
Collectable::~Collectable()
{
}