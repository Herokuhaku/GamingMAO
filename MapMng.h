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

	void MapUpdate(void);
	void MapDraw(void);
	void BackGround(void);

	const Vector2Template<int> GameMapSize;	// �Q�[����ʂ̃}�b�v�̑傫��
	std::vector<std::string> split(std::string str, char del);

private:
	int GameMap[MapChipY][MapChipX];	// Y1440/16,X(2560/16)+��2�}�X
	int HitMap[MapChipY][MapChipX];		// �����蔻��Map

	static MapMng *sInstance;
	MapMng();
	~MapMng();
};

