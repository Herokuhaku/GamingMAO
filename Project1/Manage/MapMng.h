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

	// <����,MAP�̊i�[�ꏊ,Layer,�O��MAP,����MAP,������MAP>
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
	int getGameMapM(const Vector2& pos);	// pos�̈ʒu��GameMap��ԋp Member
	std::map<LAYER, int> _layer;
	const Vector2Template<int> GameMapSize;	// �Q�[����ʂ̃}�b�v�̑傫��
	std::vector<std::string> split(std::string str, char del);

	int HitMap[MapChipY][MapChipX];		// �����蔻��Map

	void StageTrans(int no);			// �X�e�[�W�̔ԍ��������ɓ����

	MapData GetMapIndex(int no);
	int GetnowStage(void) {return nowStage;	}

private:
	int GameMap[MapChipY][MapChipX];	// Y1440/16,X(2560/16)+��2�}�X

	void SetBgLayer(int bgNo);		// 
	int _layer0;
	int _layer1;
	int _layer2;
	int layerPosX;
	int _oldLayerNo;
	
	// Map�̈ړ�

	FILE *indexFp;				
	std::string MapID;
	MapData _mapdata;
	std::map<int,MapData> mapindex;

	int nowStage;

	// Map�̈ړ�
	

	static MapMng *sInstance;
	MapMng();
	~MapMng();
};

