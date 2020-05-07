#include "MapMng.h"
#include "Graphic/ImageMng.h"
#include "DxLib.h"
#include "Scene/SceneMng.h"

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

bool MapMng::MapUpdate(void)
{
	std::ifstream ifs("mapdata/map.csv");
	std::string line;

	int y = 0;
	int x = 0;

	while (std::getline(ifs, line))
	{
		std::vector<std::string> save = split(line, ',');

		x = 0;
		for (int i = 0;i < save.size();i++)
		{
			GameMap[y][x] = stoi(save.at(i));
			x++;
		}
		y++;
	}

	HitMapUpdate();		// 当たり判定
	BlockLayer();		// ブロック描画の更新

	return true;
}

void MapMng::HitMapUpdate(void)
{
	int tmpMap;
	for (int y = 0;y < MapChipY;y++)
	{
		for (int x = 0; x < MapChipX;x++)
		{
			tmpMap = GameMap[y][x];
			if (tmpMap >= 0 && tmpMap <= 23)
			{
				HitMap[y][x] = 1;
			}
		}
	}
	// 背景と合わせるために一時的に書いているだけ
	for (int x = 0; x < MapChipX; x++)
	{
		HitMap[82][x] = 1;
	}
}

void MapMng::MapDraw(void)
{
	BlockDraw();
	BackGround();
}

void MapMng::BlockDraw()
{
	lpImageMng.AddDraw({ _layer[LAYER::BLOCK],GameMapSize.x/2,GameMapSize.y/2,0.0,LAYER::BLOCK,0 });
}

void MapMng::BackGround(void)
{
	// 描画用データ　画像ID, 座標x, y, 角度, レイヤー, zオーダー
	lpImageMng.AddDraw({ lpImageMng.getImage("メイン背景")[0],GameMapSize.x / 2,GameMapSize.y / 2,0.0,LAYER::BG,0 });

	layerPosX = lpSceneMng.GetcPos().x + (500 - lpSceneMng.GetcPos().x) / 2;
	lpImageMng.AddDraw({ _layer0,GameMapSize.x / 2,GameMapSize.y / 2 ,0.0,LAYER::BG,2 });
	lpImageMng.AddDraw({ _layer1,GameMapSize.x / 2,GameMapSize.y / 2 ,0.0,LAYER::BG,1 });
	lpImageMng.AddDraw({ _layer2,layerPosX,GameMapSize.y / 2 ,0.0,LAYER::BG,0 });
}

void MapMng::BlockLayer(void)
{
	SetDrawScreen(_layer[LAYER::BLOCK]);
	ClsDrawScreen();

	for (int y = 0;y < MapChipY;y++)
	{
		for (int x = 0; x < MapChipX;x++)
		{
			if (GameMap[y][x] != -1)
			{
				DrawRotaGraph(x*16+(CHIP_SIZE/2), y*16, 1.0, 0, lpImageMng.getImage("Block")[GameMap[y][x]], true);
			}
		}
	}
}

void MapMng::SetBgLayer(int bgNo)
{
	int bgX = 928;
	int bgY = 777;
	
	std::string no;

	SetDrawScreen(_layer2);
	ClsDrawScreen();

	SetDrawScreen(_layer1);
	ClsDrawScreen();

	SetDrawScreen(_layer0);
	ClsDrawScreen();
	
	switch(bgNo)
	{
		case 1:
			for (int i = 0; i < 4; i++)
			{
				SetDrawScreen(_layer2);
				for (int j = 6; j >= 6; j--)
				{
					no = std::to_string(j);
					DrawRotaGraph(bgX * i, GameMapSize.y - (bgY / 2) - MapOffSetY, 1.0, 0.0, lpImageMng.getImage(no)[0], true, false);
				}
				SetDrawScreen(_layer1);
				for (int j = 5; j >= 1; j--)
				{
					no = std::to_string(j);
					DrawRotaGraph(bgX * i, GameMapSize.y - (bgY / 2) - MapOffSetY, 1.0, 0.0, lpImageMng.getImage(no)[0], true, false);
				}
				SetDrawScreen(_layer0);
				for (int j = 1; j >= 0; j--)
				{
					no = std::to_string(j);
					DrawRotaGraph(bgX * i, GameMapSize.y - (bgY / 2) - MapOffSetY, 1.0, 0.0, lpImageMng.getImage(no)[0], true, false);
				}
			}
			break;
		default:
			break;
	}
}

MapMng::MapMng():
	GameMapSize{2560,1440}
{
	SetDrawBright(255,255,255);
	for (int y = 0;y < MapChipY;y++)
	{
		for (int x = 0;x < MapChipX;x++)
		{
			GameMap[y][x] = 0;
			HitMap[y][x] = 0;
		}
	}

	lpImageMng.getImage("image/background/main_back.png", "メイン背景");

	lpImageMng.getImage("image/background/layer_0000.png", "0");
	lpImageMng.getImage("image/background/layer_0001.png", "1");
	lpImageMng.getImage("image/background/layer_0002.png", "2");
	lpImageMng.getImage("image/background/layer_0003.png", "3");
	lpImageMng.getImage("image/background/layer_0004.png", "4");
	lpImageMng.getImage("image/background/layer_0005.png", "5");
	lpImageMng.getImage("image/background/layer_0006.png", "6");

	lpImageMng.getImage("image/back/block/For/Tileset.png", "Block",16,16,10,6);

	_layer[LAYER::BLOCK] = MakeScreen(GameMapSize.x, GameMapSize.y, true);

	_layer0 = MakeScreen(GameMapSize.x, GameMapSize.y, true);
	_layer1 = MakeScreen(GameMapSize.x, GameMapSize.y, true);
	_layer2 = MakeScreen(GameMapSize.x, GameMapSize.y, true);

	SetBgLayer(1);

	layerPosX = 0;

	MapUpdate();
	BlockLayer();
	SetDrawBright(0,0,0);
}

MapMng::~MapMng()
{

}

bool MapMng::getHitMap(const Vector2& pos)
{
	Vector2 chip = pos / CHIP_SIZE;

	if (chip.x < 0 || chip.x >= MapChipX || chip.y < 0 || chip.y >= MapChipY)
	{
		return true;
	}

	return (HitMap[chip.y][chip.x] == 1);
}