#ifndef IODEVICE_H
#define IODEVICE_H

#include <vector>
#include "IIOContext.h"
#include "InputInfo.h"
#include "SpriteInfo.h"

using namespace std;

class IODevice
{
private:
	IIOContext*			m_context;
	vector<SpriteInfo>	m_spriteInfos;

public:
				IODevice();
				IODevice(IIOContext* p_context);
				~IODevice();
	InputInfo	fetchInput();
	void		updateSpriteInfo(int p_spriteId);

	int			draw();
	SpriteInfo* addSpriteInfo(SpriteInfo p_spriteInfo);
	void		removeSpriteInfo(SpriteInfo p_spriteInfo);


};

#endif