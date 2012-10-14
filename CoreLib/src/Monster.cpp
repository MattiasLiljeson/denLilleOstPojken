#include "Monster.h"

Monster::Monster(SpriteInfo* p_spriteInfo, Tile* p_tile, Tilemap* p_map): GameObject(p_spriteInfo)
{
	dt = 0;
	m_currentTile = m_nextTile = p_tile;
	m_map = p_map;
	m_dead = false;
	m_ai = NULL;

	m_nextTile = m_currentTile;
}

Monster::~Monster()
{
	if(m_ai)
		delete m_ai;
}
void Monster::update(float p_deltaTime, InputInfo p_inputInfo)
{
	if (!m_dead)
	{
		if (m_ai)
			m_ai->update(p_deltaTime);

		dt += p_deltaTime * 6;
		while (dt > 1)
		{
			dt -= 1;
			if (m_currentTile)
			{
				m_currentTile = m_nextTile;
				if (m_path.size() > 0)
				{
					if (m_path.back()->isFree())
					{
						m_nextTile = m_path.back();
						m_path.pop_back();
					}
					else
					{
						m_path.clear();
					}
				}
				else
				{
					m_ai->findTarget();

					if(m_path.size() == 0)
					{
						Tile* t;
						do
						{
							int rndX = rand() % m_map->getWidth();
							int rndY = rand() % m_map->getHeight();
							t = m_map->getTile(TilePosition(rndX, rndY));					
						} while (!t->isFree());

						FindPath(m_currentTile, t);
					}
				}
			}
		}

		if (m_spriteInfo)
		{
			TilePosition tp1 = m_currentTile->getTilePosition();
			TilePosition tp2 = m_nextTile->getTilePosition();
			float pX = tp1.x * (1-dt) + tp2.x * dt; 
			float pY = tp1.y * (1-dt) + tp2.y * dt;  

			float w = m_currentTile->getWidth();
			float h = m_currentTile->getHeight();
			m_spriteInfo->transformInfo.translation[TransformInfo::X] = pX * w + w * 0.5f;
			m_spriteInfo->transformInfo.translation[TransformInfo::Y] = pY * h + h * 0.5f;
		}
	}
}
Tile* Monster::getCurrentTile()
{
	return m_currentTile;
}
void Monster::FindPath(Tile* p_start, Tile* p_goal)
{
	Tile* toCheck[4];

	vector<AstarItem> queue;
	vector<AstarItem> visited;

	AstarItem first;
	first.toStart = 0;
	TilePosition startdif = p_goal->getTilePosition() - p_start->getTilePosition();
	first.toGoal = abs(startdif.x) + abs(startdif.y);
	first.tile = p_start;
	first.parent = NULL;
	queue.push_back(first);
	while (queue.size() > 0 && queue.back().tile != p_goal)
	{
		visited.push_back(queue.back());
		TilePosition p = queue.back().tile->getTilePosition();
		queue.pop_back();
		toCheck[0] = m_map->getTile(p + TilePosition(0, 1));
		toCheck[1] = m_map->getTile(p + TilePosition(0, -1));
		toCheck[2] = m_map->getTile(p + TilePosition(1, 0));
		toCheck[3] = m_map->getTile(p + TilePosition(-1, 0));
		for (int i = 0; i < 4; i++)
		{
			if (toCheck[i])
			{
				bool skip = !toCheck[i]->isFree();
				for (unsigned int j = 0; j < visited.size(); j++)
				{
					if (visited[j].tile == toCheck[i])
						skip = true;
				}
				if (!skip)
				{
					int toStart = visited.back().toStart+1;
					TilePosition dif = p_goal->getTilePosition() - toCheck[i]->getTilePosition();
					int toGoal = abs(dif.x) + abs(dif.y);
					UpdateQueue(toCheck[i], visited.size()-1, toStart, toGoal, queue);
				}
			}
		}
	}
	
	if (queue.size() == 0)
		return;

	m_path.clear();
	m_path.push_back(queue.back().tile);
	int parent = queue.back().parent;
	while (m_path.back() != p_start)
	{
		AstarItem asi = visited[parent];
		m_path.push_back(asi.tile);
		parent = asi.parent;
	}

	return;
}
int	Monster::UpdateQueue(Tile* p_tile, int p_parent, int p_toStart, int p_toGoal, vector<AstarItem>& p_queue)
{
	int index = FindTile(p_tile, p_queue);
	if (index >= 0 && p_queue[index].distance() > p_toStart + p_toGoal)
	{
		p_queue[index].toStart = p_toStart;
		p_queue[index].toGoal = p_toGoal;
		p_queue[index].parent = p_parent;
		while (index < (int)(p_queue.size()-1) && p_queue[index].distance() < p_queue[index+1].distance())
		{
			AstarItem temp = p_queue[index];
			p_queue[index] = p_queue[index+1];
			p_queue[index+1] = temp;
			index++;
		}
	}
	else
	{
		AstarItem star;
		star.toStart = p_toStart;
		star.toGoal = p_toGoal;
		star.tile = p_tile;
		star.parent = p_parent;
		p_queue.push_back(star);
		index = p_queue.size() - 1;
		while (index > 0 && p_queue[index].distance() > p_queue[index-1].distance())
		{
			AstarItem temp = p_queue[index];
			p_queue[index] = p_queue[index-1];
			p_queue[index-1] = temp;
			index--;
		}
	}
	return 0;
}
int	Monster::FindTile(Tile* p_tile, vector<AstarItem>& p_queue)
{
	for (unsigned int i = 0; i < p_queue.size(); i++)
	{
		if (p_queue[i].tile == p_tile)
			return i;
	}
	return -1;
}
void Monster::kill()
{
	m_dead = true;
	if (m_spriteInfo)
		m_spriteInfo->visible = false;
}
bool Monster::isDead()
{
	return m_dead;
}

void Monster::addMonsterAI(Avatar* p_avatar, GameStats* p_gameStats, Tilemap* p_tilemap)
{
	m_ai = new AI(this,p_avatar,p_gameStats,p_tilemap);
}