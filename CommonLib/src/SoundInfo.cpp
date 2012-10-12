#include "SoundInfo.h"

SoundData::SoundData(string p_path)
{
	path = p_path;
	buffer.LoadFromFile(p_path);
}
SoundData::SoundData()
{
	path = "";
}