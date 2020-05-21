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

	// <自分,MAPの格納場所,Layer,前のMAP,次のMAP,分岐先のMAP,前X座標，Y座標, 後ろX座標，Y座標>
	using MapData = std::tuple<int,std::string,int,int,int,int,int,int,int,int,int,int>;

	enum class MAP_DATA
	{
		NO,
		MAPLINK,
		LAYER,
		BACK,
		FRONT,
		BRANCH,
		FPOSX,
		FPOSY,
		BPOSX,
		BPOSY,
		bPOSX,					// BRANCHのX
		bPOSY,
		MAX
	};

	typedef struct {
		Vector2 pos;
		int image[3][9];
		int imagecnt[3][8];
		int animFlame;
		int icnt;
		int animKind;
		bool startF;
	} portal_t;


class MapMng
{
public:
	static MapMng& GetInstans()
	{
		Create();
		
		return *sInstance;
	}
	static void Create(void)
	{
		if (sInstance == nullptr)
		{
			sInstance = new MapMng();
		}
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
	bool getHitMap(const Vector2& pos, int stage);
	char getGameMapM(const Vector2& pos, int stage);	// posの位置のGameMapを返却 Member

	const Vector2Template<int> GameMapSize;	// ゲーム画面のマップの大きさ

	std::vector<std::string> split(std::string str, char del);

	void StageTrans(int no);			// ステージの番号を引数に入れる

	MapData GetMapIndex(int no);
	int GetnowStage(void) { return nowStage.first; }
	int GetFrontPosX(int no);
	int GetFrontPosY(int no);
	int GetBackPosX(int no);
	int GetBackPosY(int no);
	int GetBrancPosX(int no);
	int GetBrancPosY(int no);

	const std::pair<bool, int> *GetactiveMap(void) const;

#define ACTIVEMAP 4
private:
	int _layer[ACTIVEMAP];
	char GameMap[MapChipY][MapChipX][ACTIVEMAP];	// Y1440/16,X(2560/16)+壁2マス
	char HitMap[MapChipY][MapChipX][ACTIVEMAP];		// 当たり判定Map
	std::pair<bool, int> _activeMap[ACTIVEMAP];		// <保存していいか,stage>    UpdateをするMAP
	int _writNo;									// 書き込んでいい添え字

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

	std::pair<int,int> nowStage;					// <現在のステージ,_activeMap内の現在のステージの添え字>

	// Mapの移動
	portal_t test;
	

	static MapMng *sInstance;
	MapMng();
	~MapMng();
};

