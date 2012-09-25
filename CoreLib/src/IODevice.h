#ifndef IODEVICE_H
#define IODEVICE_H

#include <vector>
#include "IOContext.h"
#include "InputInfo.h"
#include "SpriteInfo.h"

using namespace std;

class IODevice
{
private:
	IOContext*			m_context;
	vector<SpriteInfo>	m_spriteInfos;

public:
				IODevice();
				IODevice(IOContext* p_context);
				~IODevice();
	InputInfo	fetchInput();
	void		updateSpriteInfo(int p_spriteId);

	int			draw(float p_dt);
	int			update(float p_dt);
	bool		isRunning();
	SpriteInfo* addSpriteInfo(SpriteInfo p_spriteInfo);
	void		removeSpriteInfo(SpriteInfo p_spriteInfo);


};

#endif