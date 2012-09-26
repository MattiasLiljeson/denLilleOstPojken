#include "Avatar.h"

Avatar::Avatar()
{

}

Avatar::Avatar( SpriteInfo* p_spriteInfo )
	: GameObject(p_spriteInfo)
{

}

void Avatar::update( float p_deltaTime, InputInfo p_inputInfo )
{
	if (p_inputInfo.keys[InputInfo::LEFT] == InputInfo::KEYDOWN)
		m_spriteInfo->transformInfo.translation[TransformInfo::X] -= 50 * p_deltaTime;
	else if (p_inputInfo.keys[InputInfo::RIGHT] == InputInfo::KEYDOWN)
		m_spriteInfo->transformInfo.translation[TransformInfo::X] += 50 * p_deltaTime;
	if (p_inputInfo.keys[InputInfo::DOWN] == InputInfo::KEYDOWN)
		m_spriteInfo->transformInfo.translation[TransformInfo::Y] -= 50 * p_deltaTime;
	else if (p_inputInfo.keys[InputInfo::UP] == InputInfo::KEYDOWN)
		m_spriteInfo->transformInfo.translation[TransformInfo::Y] += 50 * p_deltaTime;
}

