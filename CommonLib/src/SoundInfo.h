#include <SFML\Audio.hpp>
#include <string>

using namespace std;

struct SoundInfo
{
	sf::SoundBuffer buffer;
	string path;
	SoundInfo(string p_path);
};