#ifndef TESTGLYPHMAP_H
#define TESTGLYPHMAP_H

#include "Test.h"
#include <GlyphMap.h>

class Test_GlyphMap: public Test
{
public:
	Test_GlyphMap(): Test("GLYPHMAP")
	{
	}
	void setup()
	{
		GlyphMap glyphMap("ABC123", "dummy", 8, 8);
		m_entries.push_back(TestData("TotalWidthInPixels",
			glyphMap.getMaxBitmapWidth() == 6 * 8));
	}

};

#endif