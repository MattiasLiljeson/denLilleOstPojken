#include "MenuItem.h"

int MenuItem::updateText()
{
	if(m_text != NULL)
	{
		m_text->setOrigin( m_basePosition + m_textOffset );
		return GAME_OK;
	}
	return GAME_FAIL;
}

int MenuItem::updateSprite()
{
	if(m_spriteInfo != NULL)
	{
		m_spriteInfo->transformInfo.translation[TransformInfo::X] =
			m_basePosition.x;
		m_spriteInfo->transformInfo.translation[TransformInfo::Y] =
			m_basePosition.y;

		return GAME_OK;
	}
	else
		return GAME_FAIL;
}


MenuItem::MenuItem(SpriteInfo* p_spriteInfo, TextArea* p_text, GlyphMap* p_font,
	fVector2 p_basePosition, fVector2 p_textOffset )
	: GameObject(p_spriteInfo)
{
	m_font = p_font;
	m_text = p_text;

	setBasePosition( p_basePosition.x, p_basePosition.y );
	setTextOffset( p_textOffset.x, p_textOffset.y );
}

MenuItem::~MenuItem()
{
	delete m_font;
	m_font = NULL;
	delete m_text;
	m_text = NULL;
}

void MenuItem::update( float p_deltaTime, InputInfo p_inputInfo )
{
}

TextArea* MenuItem::getTextArea()
{
	return m_text;
}

int MenuItem::setTextOffset( float p_x, float p_y )
{
	m_textOffset.x = p_x;
	m_textOffset.y = p_y;
	
	updateSprite();
	if (updateText() == GAME_OK)
		return GAME_OK;

	return GAME_FAIL;
	
}

int MenuItem::setBasePosition( float p_x, float p_y )
{
	m_basePosition.x = p_x;
	m_basePosition.y = p_y;
	
	if( updateSprite() == GAME_OK && updateText() == GAME_OK )
			return GAME_OK;
	return GAME_FAIL;
}

void MenuItem::setVisible( bool p_visible )
{
	if(m_spriteInfo != NULL)
		m_spriteInfo->visible = p_visible;
	if(m_text != NULL)
		m_text->setVisible( p_visible );
}

void MenuItem::setSelectable( bool p_selectable )
{
	m_selectable = p_selectable;
}

bool MenuItem::isSelectable()
{
	return m_selectable;
}
