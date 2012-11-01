#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#include <string>
#include <fstream>
#include "CommonUtility.h"

using namespace std;

class GameSettings
{
public:
	int m_scrResX;
	int m_scrResY;

	int m_scrStartX;
	int m_scrStartY;

	bool m_windowed;

public:
	GameSettings();
	int readSettingsFile( string p_filePath );
};

#endif //GAMESETTINGS_H