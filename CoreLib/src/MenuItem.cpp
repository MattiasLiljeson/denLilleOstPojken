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


MenuItem::MenuItem(SpriteInfo* p_spriteInfo, TextArea* p_text,
	fVector2 p_basePosition, fVector2 p_textOffset )
	: GameObject(p_spriteInfo)
{
	m_text = p_text;

	setBasePosition( p_basePosition.x, p_basePosition.y );
	setTextOffset( p_textOffset.x, p_textOffset.y );
}

MenuItem::~MenuItem()
{
	delete m_text;
	m_text = NULL;
}

void MenuItem::update( float p_deltaTime, InputInfo p_inputInfo )
{
	if( m_text != NULL )
		m_text->update( p_deltaTime, p_inputInfo );
}

void MenuItem::animateText( float p_freq, float p_amplitude, float p_speed, int p_animIdx )
{
	if( m_text != NULL )
		m_text->animateText( p_freq, p_amplitude, p_speed, p_animIdx);
}

void MenuItem::resetAnimation( int p_idx )
{
	if( m_text != NULL )
		m_text->resetAnimation( p_idx );
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