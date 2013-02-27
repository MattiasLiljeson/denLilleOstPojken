#include "SoundInfo.h"
#include "ExecutableDirectoryPath.h"

SoundData::SoundData(string p_path)
{
	path = p_path;
	buffer.LoadFromFile(addExecutableDirectoryPath(p_path.c_str()));
}
SoundData::SoundData()
{
	path = "";
}

SongData::SongData()
{
	path = "";
}
SongData::SongData(string p_path)
{
	path = p_path;
}