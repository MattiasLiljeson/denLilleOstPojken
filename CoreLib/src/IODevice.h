#ifndef IODEVICE_H
#define IODEVICE_H

#include <vector>
#include "IOContext.h"
#include "InputInfo.h"
#include "SpriteInfo.h"
#include <SoundManager.h>


class SoundManager;

using namespace std;

class IODevice
{
private:
	IOContext*			m_context;
	SoundManager		m_soundManager;
	vector<SpriteInfo*>	m_spriteInfos;

public:
				IODevice();
				IODevice(IOContext* p_context);
				~IODevice();
	InputInfo	fetchInput();
	void		updateSpriteInfo(int p_spriteId);

	int			draw(float p_dt);
	int			update(float p_dt);
	bool		isRunning();

	void		addSpriteInfo( SpriteInfo* p_spriteInfo );
	void		removeSpriteInfo(SpriteInfo* p_spriteInfo);
	void		updateSpriteInfo( SpriteInfo* p_spriteInfo );
	void		clearSpriteInfos();

	void		addSound(SoundInfo* p_soundInfo);

	int			getScreenWidth();
	int			getScreenHeight();
	void		setWindowText(string p_text);

	void		toneSceneBlackAndWhite(float p_fraction);
	void		fadeSceneToBlack(float p_fraction);


};

#endif