#ifndef TESTGLYPHMAP_H
#define TESTGLYPHMAP_H

#include "Test.h"
#include <GlyphMap.h>

class Test_GlyphMap: public Test
{
public:
	Test_GlyphMap(): Test("GLYPHMAP_(ABC123)")
	{
	}
	void setup()
	{
		GlyphMap glyphMap("ABC123", "dummy", 8, 8);

		m_entries.push_back(TestData("TotalWidthInPixels",
			glyphMap.getMaxBitmapWidth() == 6 * 8));

		m_entries.push_back(TestData("GetCharRect_char(A)",
			glyphMap.getCharRect('A').x == 0 &&
			glyphMap.getCharRect('A').y == 0 &&
			glyphMap.getCharRect('A').width == 8 &&
			glyphMap.getCharRect('A').height == 8));

		m_entries.push_back(TestData("GetCharRect_char(3)",
			glyphMap.getCharRect('3').x == 5 * 8 &&
			glyphMap.getCharRect('3').y == 0 &&
			glyphMap.getCharRect('3').width == 8 &&
			glyphMap.getCharRect('3').height == 8));

		m_entries.push_back(TestData("getPath",
			glyphMap.getPath() == "dummy"));
	}

};

#endif