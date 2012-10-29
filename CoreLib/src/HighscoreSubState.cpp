#include "MenuSubState.h"
#include "HighscoreSubState.h"

HighscoreSubState::HighscoreSubState( MenuSubStateManager* p_manager )
	: MenuSubState( p_manager )
{
	m_texts.resize(HS_NUM_ITEMS);
	m_texts[HS_MAIN] = "GO BACK TO MAIN";

	// More items, Maps, need more space
	m_properties.m_firstItemPos.y += 0.3f;
	//m_itemDistance *= 0.5f;

	readHighScore();
	for( unsigned int i=0; i<m_highscore.size(); i++ )
	{
		stringstream ss;
		ss << m_highscore[i].score;
		m_texts.push_back(ss.str());
	}
}

HighscoreSubState::~HighscoreSubState()
{
	writeHighScore();
}

void HighscoreSubState::readHighScore()
{
	ifstream file;
	file.open("../Highscore/score.txt", ios::in);
	if (file.is_open())
	{
		while (!file.eof())
		{
			HighScoreItem data;
			file >> data.score;
			m_highscore.push_back(data);
		}
		file.close();
	}
	sort(m_highscore.begin(), m_highscore.end());
}

//void HighscoreSubState::updateHighScore()
//{
//	int newScore = m_menuState->getParent()->getCommonResources()->totalScore;
//	if (newScore > 0 && newScore > m_highscore.back().score)
//	{
//		m_highscore.back().score = newScore;
//		for (int i = m_highscore.size()-1; i > 0; i--)
//		{
//			if (m_highscore[i] < m_highscore[i-1])
//			{
//				HighScoreItem temp = m_highscore[i];
//				m_highscore[i] = m_highscore[i-1];
//				m_highscore[i-1] = temp;
//			}
//		}
//	}
//	m_menuState->getParent()->getCommonResources()->totalScore = 0;
//}

void HighscoreSubState::writeHighScore()
{
	ofstream file;
	file.open("../Highscore/score.txt", ios::out);
	if (file.is_open())
	{
		for (int i = 0; i < m_highscore.size(); i++)
		{
			file << m_highscore[i].score;
			file << endl;
		}
		file.close();
	}
}

void HighscoreSubState::selectBtn()
{
	if( m_currItemIdx == HS_MAIN )
	{
		m_manager->reqMenuChange( MenuSubStateManager::MENU_MAIN );
	}
}
