#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <algorithm>
#include <fstream>
#include <vector>

//#include "StateManager.h"

using namespace std;

struct HighScoreItem
{
	int score;
	bool operator<(const HighScoreItem& p_other)
	{
		return score > p_other.score;
	}
};

class HighScoreFunctions
{
public:
	static const int MAX_NUM_HIGHSCORE_ITEMS = 8; 
	static vector<HighScoreItem> readHighScore()
	{
		vector<HighScoreItem> highscores;
		ifstream file;
		file.open("../Highscore/score.txt", ios::in);
		if (file.is_open())
		{
			while (!file.eof())
			{
				HighScoreItem data;
				file >> data.score;
				highscores.push_back(data);
			}
			file.close();
		}
		sort(highscores.begin(), highscores.end());
		return highscores;
	}

	static void updateHighScore( int p_newTotalScore )
	{
		//int newScore = p_manager->getCommonResources()->totalScore;
		vector<HighScoreItem> highscores = readHighScore();
		if (p_newTotalScore > 0 && p_newTotalScore > highscores.back().score)
		{
			highscores.back().score = p_newTotalScore;
			for (int i = highscores.size()-1; i > 0; i--)
			{
				if (highscores[i] < highscores[i-1])
				{
					HighScoreItem temp = highscores[i];
					highscores[i] = highscores[i-1];
					highscores[i-1] = temp;
				}
			}
		}
		writeHighScore( highscores );
		//p_manager->getCommonResources()->totalScore = 0;
	}

	static void writeHighScore( vector<HighScoreItem> p_highscores )
	{
		ofstream file;
		file.open("../Highscore/score.txt", ios::out);
		if (file.is_open())
		{
			for( unsigned int i = 0; i < p_highscores.size() && i < MAX_NUM_HIGHSCORE_ITEMS; i++)
			{
				file << p_highscores[i].score;
				file << endl;
			}
			file.close();
		}
	}
};


#endif // HIGHSCORE_H