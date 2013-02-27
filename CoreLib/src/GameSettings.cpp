#include "GameSettings.h"
#include "ExecutableDirectoryPath.h"
#include <iostream>

GameSettings::GameSettings()
{
	m_scrResX = 1280;
	m_scrResX = 720;

	m_scrStartX = 0;
	m_scrStartY = 0;

	m_windowed = true;
}

int GameSettings::readSettingsFile( string p_filePath )
{
	ifstream file( addExecutableDirectoryPath(p_filePath.c_str()).c_str(), ios::in );
	string temp;
	if( file.good() )
	{
		file>>temp;
		file>>m_scrResX;
		file>>temp;
		file>>m_scrResY;

		file>>temp;
		file>>m_windowed;

		file>>temp;
		file>>m_scrStartX;
		file>>temp;
		file>>m_scrStartY;

		return GAME_OK;
	} else {
        std::cout << "Could not open settings file for reading";
    }
	return GAME_FAIL;
}