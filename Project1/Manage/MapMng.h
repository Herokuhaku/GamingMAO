#pragma once
#include "../common/Vector2.h"
#include "../Graphic/LAYER.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <tuple>
#include <string>


#define lpMapMng MapMng::GetInstans()

#define MapChipY 90
#define MapChipX 160+2
#define MapOffSetY 16 * 5
#define CHIP_SIZE 16

	// <自分,MAPの格納場所,Layer,前のMAP,次のMAP,分岐先のMAP>
	using MapData = std::tuple<int,std::string,int,int,int,int>;

	enum class MAP_DATA
	{
		NO,
		MAPLINK,
		LAYER,
		BACK,
		NEXT,
		BRANCH,
		MAX
	};

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
	int getGameMapM(const Vector2& pos);	// posの位置のGameMapを返却 Member
	std::map<LAYER, int> _layer;
	const Vector2Template<int> GameMapSize;	// ゲーム画面のマップの大きさ
	std::vector<std::string> split(std::string str, char del);

	int HitMap[MapChipY][MapChipX];		// 当たり判定Map

	void StageTrans(int no);			// ステージの番号を引数に入れる

	MapData GetMapIndex(int no);
	int GetnowStage(void) {return nowStage;	}

private:
	int GameMap[MapChipY][MapChipX];	// Y1440/16,X(2560/16)+壁2マス

	void SetBgLayer(int bgNo);		// 
	int _layer0;
	int _layer1;
	int _layer2;
	int layerPosX;
	int _oldLayerNo;
	
	// Mapの移動

	FILE *indexFp;				
	std::string MapID;
	MapData _mapdata;
	std::map<int,MapData> mapindex;

	int nowStage;

	// Mapの移動
	

	static MapMng *sInstance;
	MapMng();
	~MapMng();
};

