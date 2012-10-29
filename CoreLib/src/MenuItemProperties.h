#ifndef MENUITEMPROPERTIES_H
#define MENUITEMPROPERTIES_H

struct MenuItemProperties
{
	fVector3 m_firstItemPos;
	fVector2 m_itemSize;
	fVector2 m_itemTextOffset;
	fVector2 m_itemFontSize;
	float m_itemDistance;
	string m_itemBackgroundTexturePath;

	MenuItemProperties()
	{
		//std values
		float fw = 1.0f/1920.0f;
		float fh = 1.0f/1080.0f;

		m_firstItemPos	= fVector3( 0.5f, 0.7f, 0.9f );
		m_itemSize		= fVector2( fh*600.0f, fh*64.0f );
		m_itemTextOffset= fVector2( 0.0f, 0.0f );
		m_itemFontSize	= fVector2( fw*32, fh*32 );
		m_itemDistance	= 100*fh;
		m_itemBackgroundTexturePath = "";
	}
};
#endif // MENUITEMPROPERTIES_H