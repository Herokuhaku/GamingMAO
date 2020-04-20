#include "MapMng.h"


MapMng* MapMng::sInstance = nullptr;

std::vector<std::string> MapMng::split(std::string str, char delimiter)
{
	std::vector<std::string> result;
	std::string save;

	for (const char i : str)
	{
		if (i == delimiter)
		{
			result.push_back(save);
			save.clear();
		}
		else
		{
			save += i;
		}
	}
	result.push_back(save);

	return result;
}

void MapMng::MapUpdate(void)
{
	std::ifstream ifs("mapdata/map.csv");
	std::string line;

	int y = 0;
	int x = 0;

	while (std::getline(ifs, line))
	{
		std::vector<std::string> save = split(line, ',');

		x = 0;
		for (unsigned int i = 0;i < save.size();i++)
		{
			GameMap[y][x] = stoi(save.at(i));
			x++;
		}
		y++;
	}
}

MapMng::MapMng():
	GameMapSize{2560,1440}
{
	for (int y = 0;y < MapChipY;y++)
	{
		for (int x = 0;x < MapChipX;x++)
		{
			GameMap[y][x] = 0;
		}
	}
	MapUpdate();
}

MapMng::~MapMng()
{

}
