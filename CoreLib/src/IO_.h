#ifndef IO_H
#define IO_H

#include <vector>
#include "IIOContext.h"
#include "InputInfo.h"
#include "SpriteInfo.h"

using namespace std;

class IO
{
private:
	IIOContext*			m_context;
	vector<SpriteInfo>	m_spriteInfos;

public:
				IO();
				IO(IIOContext* p_context);
				~IO();
	InputInfo	fetchInput();
	void		updateSpriteInfo(int p_spriteId);

	int			draw();
	SpriteInfo* addSpriteInfo(SpriteInfo p_spriteInfo);
	void		removeSpriteInfo(SpriteInfo p_spriteInfo);


};

#endif