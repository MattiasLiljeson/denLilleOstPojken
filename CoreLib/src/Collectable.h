#ifndef COLLECTABLE_H
#define COLLECTABLE_H

#include "GameObject.h"

// container representation for animation
class CollectableContainer
{
private:
	SpriteInfo* m_container;
	SpriteInfo* m_containerShadow;
	TransformInfo m_origin;
	float m_elapsedTime;
	float m_outroTime;
	bool m_done;
public:
	CollectableContainer(SpriteInfo* p_container,SpriteInfo* p_containerShadow)
	{
		if(p_container != NULL) 
		{
			m_origin = p_container->transformInfo;
			m_elapsedTime=m_origin.translation[TransformInfo::X] + m_origin.translation[TransformInfo::Y];
		}
		m_outroTime=0.0f;
		m_container = p_container;
		m_containerShadow = p_containerShadow;
		m_done=false;
	}

	void playOutro(float p_dt)
	{
		if (!m_done)
		{
			if (m_outroTime<1.0f)
			{
				m_outroTime+=p_dt;
				m_container->transformInfo.translation[TransformInfo::Y] += m_outroTime*p_dt*2000.0f;
				m_container->transformInfo.scale[TransformInfo::Y] = m_origin.scale[TransformInfo::Y]*(1.0f+m_outroTime);
				m_containerShadow->transformInfo.scale[TransformInfo::X] = m_origin.scale[TransformInfo::X]*(1.0f-m_outroTime);
				m_containerShadow->transformInfo.scale[TransformInfo::Y] = m_origin.scale[TransformInfo::Y]*(1.0f-m_outroTime);
			}
			else
			{
				m_container->visible = false;
				m_containerShadow->visible = false;
				m_done=true;
			}
		}

	}

	void update(float p_dt)
	{
		m_elapsedTime+=p_dt;
		m_container->transformInfo.scale[TransformInfo::Y] = m_origin.scale[TransformInfo::Y]+(1.0f+sin(m_elapsedTime*2.0f))*4.0f;
		m_container->transformInfo.scale[TransformInfo::X] = m_origin.scale[TransformInfo::X]+(1.0f+sin(m_elapsedTime*4.0f))*4.0f;
		m_container->transformInfo.translation[TransformInfo::Y] = m_origin.translation[TransformInfo::Y]-2.0f+sin(m_elapsedTime*2.8f)*2.0f;
		m_containerShadow->transformInfo.scale[TransformInfo::X] = m_origin.scale[TransformInfo::X]+1.0f+sin(m_elapsedTime*2.8f)*3.0f;
	}
};


class Collectable: public GameObject
{
private:
	void InitTransformOrigin();
protected:
	bool m_consumed;
	float m_elapsedTime;
	CollectableContainer* m_container;
	TransformInfo m_origin;
public:
	Collectable();
	Collectable(SpriteInfo* p_spriteInfo);
	Collectable(SpriteInfo* p_spriteInfo, GameStats* p_gameStats);
	Collectable(SpriteInfo* p_spriteInfo, GameStats* p_gameStats, CollectableContainer* p_container);
	virtual ~Collectable();

	virtual void consume() = 0;
	virtual bool isConsumed();
	virtual void update(float p_deltaTime, InputInfo p_inputInfo);
	virtual void activate();
};

#endif