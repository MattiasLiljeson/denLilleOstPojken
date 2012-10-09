#include "MenuItem.h"

MenuItem::MenuItem(IODevice* p_io, string p_texturePath)
{
	if(p_io)
	{
		m_spriteInfo = new SpriteInfo();
		m_spriteInfo->transformInfo.translation[TransformInfo::X] = 400;
		m_spriteInfo->transformInfo.translation[TransformInfo::Y] = 400;
		m_spriteInfo->transformInfo.translation[TransformInfo::Z] = 0.99f;
		m_spriteInfo->transformInfo.scale[TransformInfo::X] = 800.0f;
		m_spriteInfo->transformInfo.scale[TransformInfo::Y] = 350.0f;
		m_spriteInfo->textureFilePath = p_texturePath;
		p_io->addSpriteInfo(m_spriteInfo);
	}
}

MenuItem::~MenuItem()
{
}

void MenuItem::update(float p_deltaTime, InputInfo p_inputInfo)
{
}