#pragma once
#include "common/Vector2.h"
#include "Graphic/LAYER.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>


#define lpMapMng MapMng::GetInstans()

#define MapChipY 90
#define MapChipX 160+2

#define CHIP_SIZE 16

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

	bool MapUpdate(void);
	void HitMapUpdate(void);
	void MapDraw(void);
	void BlockDraw();
	void BackGround(void);
	void BlockLayer(void);
	std::map<LAYER, int> _layer;
	const Vector2Template<int> GameMapSize;	// ゲーム画面のマップの大きさ
	std::vector<std::string> split(std::string str, char del);

	bool getHitMap(const Vector2& pos);

private:
	int GameMap[MapChipY][MapChipX];	// Y1440/16,X(2560/16)+壁2マス
	int HitMap[MapChipY][MapChipX];		// 当たり判定Map


	
	static MapMng *sInstance;
	MapMng();
	~MapMng();
};

