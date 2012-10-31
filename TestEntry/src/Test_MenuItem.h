#ifndef TEST_MENUITEM_H
#define TEST_MENUITEM_H

#include "Test.h"

class Test_MenuItem: public Test
{
public:
	Test_MenuItem(): Test("MenuItem tester")
	{
	}
	void setup()
	{
		{
			newSection( "MenuItem with NULLs as args to ctor" );
			MenuItem mi( NULL, NULL, fVector2(), fVector2() );
			newEntry( TestData( "setTextOffset()", mi.setTextOffset( 0.0f, 0.0f ) == GAME_FAIL));
			newEntry( TestData( "setBasePosition()", mi.setBasePosition( 0.0f, 0.0f ) == GAME_FAIL));
		}

		{
			newSection( "Normal MenuItem" );
			SpriteInfo* si = new SpriteInfo;
			GOFactory factory(NULL);
			GlyphMap* gm = new GlyphMap(
			" !¨}_%#'()$+,-./0123456789:{<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZÄÀÁÅçCCCIIiñóöòööAÜUUU;¤",
			"../Textures/bubblemad_32x32.png", 32, 32);
			int maxLength = 3;
			float originX = 11;
			float originY = 12;
			TextArea* ta = new TextArea(gm, maxLength, &factory, originX, originY, TextArea::CEN_CENTER, fVector2());
			MenuItem mi(si, ta, fVector2(), fVector2());

			newEntry( TestData( "setTextOffset()", mi.setTextOffset( 0.0f, 0.0f ) == GAME_OK));
			newEntry( TestData( "setBasePosition()", mi.setBasePosition( 0.0f, 0.0f ) == GAME_OK));

			delete si;
		}
	}
};


#endif