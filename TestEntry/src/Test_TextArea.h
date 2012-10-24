#ifndef TEST_TEXTAREA_H
#define TEST_TEXTAREA_H

#include "Test.h"
#include <fVector2.h>
#include <GOFactory.h>
#include <TextArea.h>
#include <GlyphMap.h>

class Test_TextArea: public Test
{
public:
	Test_TextArea(): Test("TextArea")
	{
	}
	void setup()
	{
		GOFactory factory(NULL);
		GlyphMap glyphMap(
			" !¨}_%#'()$+,-./0123456789:{<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZÄÀÁÅçCCCIIiñóöòööAÜUUU;¤",
			"../Textures/bubblemad_32x32.png", 32, 32);

		
		int maxLength = 3;
		float originX = 11;
		float originY = 12;
		TextArea ta(&glyphMap, maxLength, &factory, originX, originY, TextArea::CEN_CENTER, fVector2());

		{
			int setText = ta.setText("test");
			newEntry( TestData( "setText() string too long", setText == GAME_FAIL ) );
			string returnText = ta.getText();
			newEntry( TestData( "getText() string too long", returnText == "tes" ) );
		}

		{
			int setText = ta.setText("te");
			newEntry( TestData( "setText() string fits", setText != GAME_FAIL ) );
			string returnText = ta.getText();
			newEntry( TestData( "getText() string fits", returnText == "te" ) );
		}

		{
			newEntry( TestData( "getMaxLength()", ta.getMaxLength() == maxLength ) );
		}

		{
			newEntry( TestData( "getOriginX() from constructor", ta.getOriginX() == originX ) );
			newEntry( TestData( "getOriginY() from constructor", ta.getOriginY() == originY ) );

			float newOriginX = 13;
			float newOriginY = 14;
			ta.setOrigin( fVector2( newOriginX, newOriginY ));

			float e = 0.01f; // epsilon
			float taOriginX = ta.getOriginX();
			float taOriginY = ta.getOriginY();

			bool xCorrect = taOriginX+e > newOriginX && taOriginX-e < newOriginY;
			bool yCorrect = taOriginY+e > newOriginY && taOriginY-e < newOriginY;
			newEntry( TestData( "getOriginX() from setOrigin()", xCorrect) );
			newEntry( TestData( "getOriginY() from setOrigin()", yCorrect) );
		}
	}
};
#endif // Test_TextArea_h