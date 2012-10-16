#include "MenuItem.h"

void MenuItem::updateText()
{
	if(m_text != NULL)
	{
		m_text->setOrigin( 
			m_basePosition.x + m_offset.x,
			m_basePosition.y + m_offset.y);
	}
}

void MenuItem::updateSprite()
{
	if(m_spriteInfo != NULL)
	{
		m_spriteInfo->transformInfo.translation[TransformInfo::X] =
			m_basePosition.x + m_offset.x;
		m_spriteInfo->transformInfo.translation[TransformInfo::Y] =
			m_basePosition.y + m_offset.y;
	}
}


MenuItem::MenuItem(SpriteInfo* p_spriteInfo, TextArea* p_text, GlyphMap* p_font, fVector2 p_basePosition )
	: GameObject(p_spriteInfo)
{
	m_font = p_font;
	m_text = p_text;

	setBasePosition( p_basePosition.x, p_basePosition.y );
}

MenuItem::~MenuItem()
{
	delete m_font;
	delete m_text;
}

void MenuItem::update( float p_deltaTime, InputInfo p_inputInfo )
{
}

TextArea* MenuItem::getTextArea()
{
	return m_text;
}

void MenuItem::setOffset( float p_x, float p_y )
{
	m_offset.x = p_x;
	m_offset.y = p_y;
	updateSprite();
	updateText();
	
}

void MenuItem::setBasePosition(float p_x, float p_y )
{
	m_basePosition.x = p_x;
	m_basePosition.y = p_y;
	updateSprite();
	updateText();
}