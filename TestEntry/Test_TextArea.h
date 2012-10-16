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

		TextArea textArea(&glyphMap, 0, &factory, 0, 0, TextArea::CEN_CENTER, fVector2());

		newEntry(TestData(" fla", false));

	}
};
#endif // Test_TextArea_h