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
#define MapOffSetY 16 * 5
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
	bool getHitMap(const Vector2& pos);
	std::map<LAYER, int> _layer;
	const Vector2Template<int> GameMapSize;	// ゲーム画面のマップの大きさ
	std::vector<std::string> Split(std::string str, char del);

	int HitMap[MapChipY][MapChipX];		// 当たり判定Map
private:
	int GameMap[MapChipY][MapChipX];	// Y1440/16,X(2560/16)+壁2マス

	void SetBgLayer(int bgNo);		// 
	int _layer0;
	int _layer1;
	int _layer2;
	int layerPosX;
	
	static MapMng *sInstance;
	MapMng();
	~MapMng();
};

