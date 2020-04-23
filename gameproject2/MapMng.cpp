#include "MapMng.h"
#include "Graphic/ImageMng.h"
#include "DxLib.h"

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

	//BlockLayer();

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
			if (tmpMap != -1 || tmpMap >= 0 && tmpMap <= 23)
			{
				HitMap[y][x] = 1;
			}
		}
	}
}

void MapMng::MapDraw(void)
{
	BackGround();
	BlockDraw();
}

void MapMng::BlockDraw()
{
	lpImageMng.AddDraw({ _layer[LAYER::BLOCK], 160 * 16 / 2, 90 * 16 / 2, 0.0, LAYER::BLOCK,0 });
}

void MapMng::BackGround(void)
{
	// 描画用データ　画像ID, 座標x, y, 角度, レイヤー, zオーダー
	std::string no;
	lpImageMng.AddDraw({ lpImageMng.getImage("メイン背景")[0],GameMapSize.x / 4,GameMapSize.y / 4,0.0,LAYER::BG,0 });
	for (int i = 6;i >= 0;i--)
	{
		no = std::to_string(i);
		lpImageMng.AddDraw({ lpImageMng.getImage(no)[0],GameMapSize.x / 4,GameMapSize.y / 4,0.0,LAYER::BG,i });
	}

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
				DrawRotaGraph(x*16, y*16, 1.0, 0, lpImageMng.getImage("Block")[GameMap[y][x]], true);
			}
		}
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
			HitMap[y][x] = 0;
		}
	}

	lpImageMng.getImage("image/background/main_back.png", "メイン背景");

	lpImageMng.getImage("image/background/layer_0000.png", "6");
	lpImageMng.getImage("image/background/layer_0001.png", "5");
	lpImageMng.getImage("image/background/layer_0002.png", "4");
	lpImageMng.getImage("image/background/layer_0003.png", "3");
	lpImageMng.getImage("image/background/layer_0004.png", "2");
	lpImageMng.getImage("image/background/layer_0005.png", "1");
	lpImageMng.getImage("image/background/layer_0006.png", "0");

	lpImageMng.getImage("image/back/block/For/Tileset.png", "Block",16,16,10,6);

	_layer[LAYER::BLOCK] = MakeScreen(GameMapSize.x, GameMapSize.y, true);

	MapUpdate();
	BlockLayer();
}

MapMng::~MapMng()
{

}
