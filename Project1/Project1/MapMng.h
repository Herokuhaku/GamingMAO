#pragma once
#include "common/Vector2.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>


#define lpMapMng MapMng::GetInstans()

#define MapChipY 90
#define MapChipX 160+2

class MapMng
{
public:
	static MapMng& GetInstans()
	{
		if (sInstance == nullptr)
		{
			Create();
		}
		return *sInstance;
	}
	static void Create(void)
	{
		sInstance = new MapMng();
	}

	static void Destroy(void)
	{
		if (sInstance != nullptr)
		{
			delete sInstance;
		}
		sInstance = nullptr;
	}

	const Vector2Template<int> GameMapSize;	// ゲーム画面のマップの大きさ
	std::vector<std::string> split(std::string str, char del);

	void MapUpdate(void);

	int GameMap[MapChipY][MapChipX];	// Y1440/16,X(2560/16)+壁2マス
private:
	static MapMng *sInstance;
	MapMng();
	~MapMng();
};

