#include "SoundInfo.h"

SoundInfo::SoundInfo(string p_path)
{
	path = p_path;
	buffer.LoadFromFile(p_path);
}