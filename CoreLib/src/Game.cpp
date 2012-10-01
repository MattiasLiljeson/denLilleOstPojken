#include "Game.h"
#include "Avatar.h"
#include <ctime>

Game::Game()
{
}


Game::Game(Timer* p_timer, IOContext* p_context)
{
	srand(time(NULL));
	m_timer		= p_timer;
	m_running	= false;
	m_tileMap	= 0;
	m_mapParser = new LoadMap();

	if (p_context)
		m_io = new IODevice(p_context);
	else
		m_io = 0;
}

Game::~Game()
{
	for (int i = m_gameObjects.size() - 1; i >= 0; i--)
	{
		GameObject* gameObject = m_gameObjects.at(i);
		m_gameObjects.pop_back();
		delete gameObject;
	}
	if (m_io)
		delete m_io;
	if (m_tileMap)
		delete[] m_tileMap;
	if (m_mapParser)
		delete m_mapParser;
}

int Game::run()
{
	if (!m_timer || !m_io)
		return 1;

	m_running = true;
	m_timer->start();


	/*mgr			= new StateManager();
	curr		= mgr->getCurrentState();
	inGame		= mgr->getInGameState();
	menu		= mgr->getMenuState();
	outerState	= new InGameState(mgr);

	ASSERT_TRUE(curr);
	ASSERT_TRUE(inGame);
	ASSERT_TRUE(menu);
	ASSERT_TRUE(menu == curr || inGame == curr);

	mgr->requestStateChange(menu);
	mgr->update(0);
	
	ASSERT_TRUE(menu == mgr->getCurrentState());

	mgr->requestStateChange(inGame);

	ASSERT_FALSE(inGame == mgr->getCurrentState());
	ASSERT_TRUE(inGame == mgr->getDesiredState());

	mgr->update(0);
	ASSERT_TRUE(inGame == mgr->getCurrentState());
	mgr->update(0);
	ASSERT_TRUE(inGame == mgr->getCurrentState());*/
	/* Ugli code */
	SpriteInfo spriteInfo;
	spriteInfo.transformInfo.translation[TransformInfo::X] = 300;
	spriteInfo.transformInfo.translation[TransformInfo::Y] = 300;
	spriteInfo.transformInfo.scale[TransformInfo::X] = 100;
	spriteInfo.transformInfo.scale[TransformInfo::Y] = 100;

	GameObject* avatar = new Avatar(m_io->addSpriteInfo(spriteInfo));

	m_gameObjects.push_back(avatar);

	spriteInfo.textureFileName = "..\\Textures\\pacman-1974.png";
	spriteInfo.transformInfo.translation[TransformInfo::X] = 200;
	spriteInfo.transformInfo.translation[TransformInfo::Y] = 500;
	spriteInfo.transformInfo.scale[TransformInfo::X] = 50;
	spriteInfo.transformInfo.scale[TransformInfo::Y] = 50;
	
	m_io->addSpriteInfo(spriteInfo);

	/*int arr[] = 
				{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
				 1, 2, 2, 2, 2, 2, 2, 2, 2, 1,
				 1, 2, 1, 2, 1, 1, 2, 1, 2, 1, 
				 1, 2, 2, 2, 2, 2, 2, 2, 2, 1,
				 1, 2, 1, 2, 1, 1, 2, 1, 2, 1, 
				 1, 2, 1, 2, 2, 2, 2, 1, 2, 1,
				 1, 2, 1, 1, 2, 1, 1, 1, 2, 1, 
				 1, 2, 1, 1, 2, 1, 1, 1, 2, 1,
				 1, 2, 2, 2, 2, 2, 2, 3, 2, 1, 
				 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
				 */

	vector<int> data = m_mapParser->parseMap("..\\Maps\\test_map.txt");

	TileType* types = new TileType[100];
	for (int i = 0; i < 100; i++)
	{
		if (data[i] == TileType::WALL_CENTER)
			types[i] = TileType::WALL_CENTER;
		
		else if(data[i] == TileType::PILL)
			types[i] = TileType::PILL;
		
		else if(data[i] == TileType::AVATAR_SPAWN)
			types[i] = TileType::AVATAR_SPAWN;

		else if(data[i] == TileType::MONSTER_SPAWN)
			types[i] = TileType::MONSTER_SPAWN;
		else
			types[i] = TileType::EMPTY;
	}
	m_tileMap = new Tilemap(10, 10, types, m_io);
	delete types;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (data[i*10+j] == 2)
				m_pills.push_back(Pill(m_io->addSpriteInfo(), m_tileMap->getTile(TilePosition(j, i))));
			if (arr[i*10+j] == 3)
				m_monsters.push_back(Monster(m_tileMap->getTile(TilePosition(j, i)), m_tileMap, m_io->addSpriteInfo()));
		}
	}
	/* End ugli code */
	int i = 0;

	while (m_running)
	{
		m_timer->tick();
		
		InputInfo input = m_io->fetchInput();

		update( (float)m_timer->getDeltaTime(), input );
		m_io->update(m_timer->getDeltaTime());
		m_io->draw(m_timer->getDeltaTime());

		if( input.keys[InputInfo::ESC] == InputInfo::KEYDOWN || !m_io->isRunning())
		{
			m_running = false;
		}

	}

	return 0;
}

int Game::update(float p_deltaTime, InputInfo p_inputInfo)
{
	for (unsigned int index = 0; index < m_gameObjects.size(); index++)
	{
		m_gameObjects[index]->update(p_deltaTime, p_inputInfo);
	}
	for (unsigned int index = 0; index < m_monsters.size(); index++)
	{
		m_monsters[index].update(p_deltaTime, p_inputInfo);
	}
	return 0;
}