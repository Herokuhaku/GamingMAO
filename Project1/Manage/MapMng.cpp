#include <DxLib.h>
#include "MapMng.h"
#include "../Graphic/ImageMng.h"
#include "../Scene/SceneMng.h"
#include "KeyMng.h"
#include "../Object/Enemy/EnemyMng.h"
#include "../Object/camera.h"

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

MapData MapMng::GetMapIndex(int no)
{
	if (mapindex.find(no) == mapindex.end())
	{
		char text[256];
		char mk = ',';
		int cnt;
		std::string twork[static_cast<int>(MAP_DATA::MAX)];

		do {
			cnt = 0;
			for (int i = 0; i < static_cast<int>(MAP_DATA::MAX); i++)
			{
				twork[i].erase(twork[i].begin(), twork[i].end());
			}
			fgets(text, 256, indexFp);
			for (int i = 0; i < 256 && text[i] != NULL; i++)
			{
				if (text[i] != ',')
				{
					twork[cnt] += text[i];
				}
				else
				{
					cnt++;
					if (cnt >= static_cast<int>(MAP_DATA::MAX))
					{
						// error
						exit(1);
					}
				}
			}
			// 読み込むデータが正しいという前提で作ってある
			try
			{
			mapindex[std::stoi(twork[static_cast<int>(MAP_DATA::NO)])] = {
							std::stoi(twork[static_cast<int>(MAP_DATA::NO)]),
							twork[static_cast<int>(MAP_DATA::MAPLINK)],
							std::stoi(twork[static_cast<int>(MAP_DATA::LAYER)]),
							std::stoi(twork[static_cast<int>(MAP_DATA::BACK)]),
							std::stoi(twork[static_cast<int>(MAP_DATA::FRONT)]),
							std::stoi(twork[static_cast<int>(MAP_DATA::BRANCH)]),
							std::stoi(twork[static_cast<int>(MAP_DATA::FPOSX)]),
							std::stoi(twork[static_cast<int>(MAP_DATA::FPOSY)]),
							std::stoi(twork[static_cast<int>(MAP_DATA::BPOSX)]),
							std::stoi(twork[static_cast<int>(MAP_DATA::BPOSY)]),
							std::stoi(twork[static_cast<int>(MAP_DATA::bPOSX)]),
							std::stoi(twork[static_cast<int>(MAP_DATA::bPOSY)]) };
			} 
			catch(...)
			{
				exit(1);
			}

		} while (no != std::stoi(twork[static_cast<int>(MAP_DATA::NO)]));
	}
	return mapindex[no];
}

int MapMng::GetFrontPosX(int no)
{
	return std::get<static_cast<int>(MAP_DATA::FPOSX)>(GetMapIndex(no));
}

int MapMng::GetFrontPosY(int no)
{
	return std::get<static_cast<int>(MAP_DATA::FPOSY)>(GetMapIndex(no));
}

int MapMng::GetBackPosX(int no)
{
	return std::get<static_cast<int>(MAP_DATA::BPOSX)>(GetMapIndex(no));
}

int MapMng::GetBackPosY(int no)
{
	return std::get<static_cast<int>(MAP_DATA::BPOSY)>(GetMapIndex(no));
}

int MapMng::GetBrancPosX(int no)
{
	return std::get<static_cast<int>(MAP_DATA::bPOSX)>(GetMapIndex(no));
}

int MapMng::GetBrancPosY(int no)
{
	return std::get<static_cast<int>(MAP_DATA::bPOSY)>(GetMapIndex(no));
}

const std::pair<bool, int>* MapMng::GetactiveMap(void) const
{
	return _activeMap;
}

const portal_t * MapMng::GetPortal(void) const
{
	return &test;
}

const portal_t * MapMng::GetPortal2(void) const
{
	return &tp[nowStage.first];
}

void MapMng::StageTrans(int no)
{
	if (no < 1 || no > 4)
	{
		return;
		exit(1);
	}
	_mapdata = GetMapIndex(no);
	MapID = std::get<static_cast<int>(MAP_DATA::MAPLINK)>(_mapdata);

	if (std::get<static_cast<int>(MAP_DATA::BRANCH)>(_mapdata) != 0)
	{
		auto a = GetMapIndex(std::get <static_cast<int>(MAP_DATA::BRANCH)>(_mapdata));
		
		test.stageF = true;
		test.Spos = { std::get<static_cast<int>(MAP_DATA::BPOSX)>(a), std::get<static_cast<int>(MAP_DATA::BPOSY)>(a) - 50 };
	}

	MapUpdate();

	SetCameraEndOffSet();

}

bool MapMng::MapUpdate(void)
{
	bool flag = false;

	int oldStage = nowStage.first;
	nowStage.first = std::get<static_cast<int>(MAP_DATA::NO)>(_mapdata);

	for (int i = 0; i < ACTIVEMAP; i++)
	{
		if (_activeMap[i].second == nowStage.first)
		{
			nowStage.second = i;
			_writNo = i;
			_activeMap[i].first = false;
			flag = true;
			return true;
		}
		if (_activeMap[i].first)
		{
//			if (oldStage != (*lpSceneMng.GetPlObj(TIME::FTR))->getStage() &&
//					oldStage != (*lpSceneMng.GetPlObj(TIME::NOW))->getStage())
			TIME checkTime = lpTimeMng.getTime() == TIME::FTR ? TIME::NOW : TIME::FTR;
			if(oldStage != (*lpSceneMng.GetPlObj(checkTime))->getStage())
			{
				_activeMap[nowStage.second].first = true;
			}
			nowStage.second = i;
			_activeMap[i].first = false;
			_activeMap[i].second = nowStage.first;
			_writNo = i;
			flag = true;
			break;
		}
	}
	
	if (!flag)
	{
		exit(1);
	}

	std::ifstream ifs(MapID.c_str());
	std::string line;

	int y = 0;
	int x = 0;

	tp[nowStage.first].Spos = { 0, 0 };
	tp[nowStage.first].Epos = { 0, 0 };
	tp[nowStage.first].stageF = false;


	while (std::getline(ifs, line))
	{
		std::vector<std::string> save = split(line, ',');

		x = 0;
		int no;
		for (unsigned int i = 0; i < save.size(); i++)
		{
			no = stoi(save.at(i));
			if (no == 26)
			{
				tp[nowStage.first].Spos = { x * 16, y * 16 };
			}
			if (no == 29)
			{
				tp[nowStage.first].Epos = { x * 16, y * 16 };
				tp[nowStage.first].stageF = true;
			}
			GameMap[y][x][_writNo] = no;
			x++;
		}
		y++;
	}

	HitMapUpdate();		// 当たり判定
	BlockLayer();		// ブロック描画の更新
	
	SetBgLayer(nowStage.first);		// レイヤーの更新

	return true;
}

void MapMng::HitMapUpdate(void)
{
	int tmpMap;
	for (int y = 0;y < MapChipY;y++)
	{
		for (int x = 0; x < MapChipX;x++)
		{
			tmpMap = GameMap[y][x][_writNo];
			if (tmpMap >= 0 && tmpMap <= 23)
			{
				HitMap[y][x][_writNo] = 1;
			}
			else
			{
				HitMap[y][x][_writNo] = 0;
			}
		}
	}
	// 背景と合わせるために一時的に書いているだけ
	for (int x = 0; x < MapChipX; x++)
	{
		HitMap[82][x][_writNo] = 1;
	}
}

void MapMng::MapDraw(void)
{
	BlockDraw();
	BackGround();
	PTDraw(&tp[nowStage.first]);
}

void MapMng::PTDraw(portal_t* test)
{
//---------------------------------------------------------------------------------------------------
	if (!tp[nowStage.first].stageF)
	{
		return;
	}

	bool flag = false;
	//	std::pow(test->Spos.x - lpSceneMng.GetPlPos(lpTimeMng.getTime()).x, 2.0) +
	//	std::pow(test->Spos.y + 50 - lpSceneMng.GetPlPos(lpTimeMng.getTime()).y, 2.0)
	//	<= 40000.0 ? true : false;
	Vector2 pos = { 0,0 };
	if (std::pow(test->Epos.x - lpSceneMng.GetPlPos(lpTimeMng.getTime()).x, 2.0) +
		std::pow(test->Epos.y + 50 - lpSceneMng.GetPlPos(lpTimeMng.getTime()).y, 2.0) <= 20000.0)
	{
		flag = true;
		pos = test->Epos;
	}

	if(		std::pow(test->Spos.x - lpSceneMng.GetPlPos(lpTimeMng.getTime()).x, 2.0) +
				std::pow(test->Spos.y + 50 - lpSceneMng.GetPlPos(lpTimeMng.getTime()).y, 2.0)
				<= 20000.0)
	{
		flag = true;
		pos = test->Spos;
	}


		if (flag)
		{
			test->startF = true;
		}

		if (test->startF)
		{
			lpImageMng.AddDraw({ test->image[test->animKind][test->animFlame],pos.x,pos.y, 3.0, 0.0, LAYER::CHAR, 100, DX_BLENDMODE_NOBLEND, 0 });

			test->icnt++;
			if (test->imagecnt[test->animKind][test->animFlame] < test->icnt)
			{
				test->animFlame++;
				test->icnt = 0;
				if (test->animFlame > 7)
				{
					test->animFlame = 0;
					if (!flag)
					{
						test->animKind++;
						if (test->animKind > 2)
						{
							test->animKind = 0;
							test->startF = false;
						}
					}
					else
					{
						if (test->image[test->animKind][8] == -1)
						{
							test->animKind++;
							if (test->animKind > 2)
							{
								test->animKind = 0;
							}
						}
					}
				}
			}
		}
		else
		{
			test->animFlame = 0;
			test->icnt = 0;
			test->animKind = 0;
		}

//---------------------------------------------------------------------------------------------------
}

void MapMng::BlockDraw()
{
	lpImageMng.AddDraw({ _layer[nowStage.second], GameMapSize.x / 2, GameMapSize.y / 2, 1.0, 0.0, LAYER::BLOCK, 0, DX_BLENDMODE_NOBLEND, 0 });
}

void MapMng::BackGround(void)
{
	// 描画用データ　画像ID, 座標x, y, 角度, レイヤー, zオーダー
	lpImageMng.AddDraw({ lpImageMng.getImage("メイン背景")[0], GameMapSize.x / 2, GameMapSize.y / 2, 1.0, 0.0, LAYER::BG, 0, DX_BLENDMODE_NOBLEND, 0 });

	int layerPosX = static_cast<int>(lpSceneMng.GetcPos().x + ((500 - lpSceneMng.GetcPos().x) / 2));
	int layerPosY = static_cast<int>(GameMapSize.y / 2 - ((1171 - lpSceneMng.GetcPos().y) / 7));

	int layerPosX2 = static_cast<int>(lpSceneMng.GetcPos().x + ((500 - lpSceneMng.GetcPos().x) / 4));
	int layerPosY2 = static_cast<int>(GameMapSize.y / 2 - ((1171 - lpSceneMng.GetcPos().y) / 4));

	lpImageMng.AddDraw({ _layer0, GameMapSize.x / 2, GameMapSize.y / 2, 1.0, 0.0, LAYER::BG, 3, DX_BLENDMODE_NOBLEND, 2 });
	lpImageMng.AddDraw({ _layer1, layerPosX		   , layerPosY		  , 1.0, 0.0, LAYER::BG, 2, DX_BLENDMODE_NOBLEND, 1 });
	lpImageMng.AddDraw({ _layer2, layerPosX2	   , layerPosY2		  , 1.0, 0.0, LAYER::BG, 1, DX_BLENDMODE_NOBLEND, 0 });
}

void MapMng::BlockLayer(void)
{
	int tmpScreen = GetDrawScreen();
	SetDrawScreen(_layer[_writNo]);
	ClsDrawScreen();

	for (int y = 0;y < MapChipY;y++)
	{
		for (int x = 0; x < MapChipX;x++)
		{
			if (GameMap[y][x][_writNo] != -1)
			{
				int a = static_cast<int>(GameMap[y][x][_writNo]);
				DrawRotaGraph(x*16+(CHIP_SIZE/2), y*16, 1.0, 0, lpImageMng.getImage("Block")[static_cast<int>(GameMap[y][x][_writNo])], true);
			}
		}
	}

	SetDrawScreen(tmpScreen);
}

void MapMng::SetBgLayer(int bgNo)
{
	int layer = std::get<static_cast<int>(MAP_DATA::LAYER)>(_mapdata);
	if(_oldLayerNo == layer)
	{
		return;
	}
	_oldLayerNo = layer;
	int bgX = 928;
	int bgY = 777;
	
	std::string no;

	int tmpScreen = GetDrawScreen();

	SetDrawScreen(_layer2);
	ClsDrawScreen();

	SetDrawScreen(_layer1);
	ClsDrawScreen();

	SetDrawScreen(_layer0);
	ClsDrawScreen();
	
	// 変わるときにデータを消す
	switch(bgNo)
	{
		case 1:
			for (int i = 0; i < 4; i++)
			{
				SetDrawScreen(_layer2);
				for (int j = 8; j >= 7; j--)
				{
					no = std::to_string(j);
					DrawRotaGraph(bgX * i, GameMapSize.y - (bgY / 2) - MapOffSetY, 1.0, 0.0, lpImageMng.getImage(no)[0], true, false);
				}
				SetDrawScreen(_layer1);
				for (int j = 6; j >= 6; j--)
				{
					no = std::to_string(j);
					DrawRotaGraph(bgX * i, GameMapSize.y - (bgY / 2) - MapOffSetY, 1.0, 0.0, lpImageMng.getImage(no)[0], true, false);
				}
				SetDrawScreen(_layer0);
				for (int j = 5; j >= 0; j--)
				{
					no = std::to_string(j);
					DrawRotaGraph(bgX * i, GameMapSize.y - (bgY / 2) - MapOffSetY, 1.0, 0.0, lpImageMng.getImage(no)[0], true, false);
				}
			}
			break;
		default:
			break;
	}

	SetDrawScreen(tmpScreen);
}

bool MapMng::Init(void)
{
	nowStage = { 0,0 };
	_oldLayerNo = 0;

	InitPt();
	InitMap();
	InitEnd();
	return true;
}

void MapMng::InitPt(void)
{
	test.stageF = false;
	test.Spos = { 0,0 };
	test.Epos = { 0,0 };
	test.animFlame = 0;
	test.icnt = 0;
	test.animKind = 0;
	test.startF = false;

	for (int i = 0; i < STAGE_MAX; i++)
	{
		tp[i] = test;
	}
}

void MapMng::InitMap(void)
{
	for (int wNo = 0; wNo < ACTIVEMAP; wNo++)
	{
		for (int y = 0; y < MapChipY; y++)
		{
			for (int x = 0; x < MapChipX; x++)
			{
				GameMap[y][x][wNo] = 0;
				HitMap[y][x][wNo] = 0;
			}
		}
		_activeMap[wNo] = { true,0 };
	}
}

void MapMng::InitEnd(void)
{
	SetDrawBright(255,255,255);
	_mapdata = GetMapIndex(1);
	MapID = std::get<static_cast<int>(MAP_DATA::MAPLINK)>(_mapdata);
	MapUpdate();
	//SetDrawBright(0,0,0);
}

void MapMng::SetCameraEndOffSet(void)
{
	Vector2 offset;
	int x1 = 0, x2 = 0;
	for (int i = 0; i < MapChipX; i++)
	{
		if (GameMap[0][i][nowStage.second] == 9)
		{
			x1++;
		}
		else
		{
			break;
		}
	}
	for (int i = MapChipX; i > 0; i--)
	{
		if (GameMap[0][i][nowStage.second] == 9)
		{
			x2++;
		}
		else
		{
			break;
		}
	}

	// 40
	offset = { (x1 + 40) * CHIP_SIZE,lpMapMng.GameMapSize.x - ((x2 + 40) * CHIP_SIZE) };
	lpSceneMng.GetcObj()->SetcEndOffSet(std::move(offset));
}

MapMng::MapMng():
	GameMapSize{2560,1440}
{
	lpImageMng.getImage("image/Purple Portal Sprite Sheet.png", "potal",64,64,8,3);

	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			test.image[j][i] = lpImageMng.getImage("potal")[j * 8 + i];
			test.imagecnt[j][i] = 2 + ( i / 3 );
		}
	}

	test.image[0][8] = -1;
	test.image[1][8] = 0;
	test.image[2][8] = -1;

	for (int i = 0; i < 8; i++)
	{
		test.imagecnt[1][i] = 5;
	}


	lpImageMng.getImage("image/background/main_back.png", "メイン背景");

	lpImageMng.getImage("image/background/layer_0000.png", "0");
	lpImageMng.getImage("image/background/layer_0001.png", "1");
	lpImageMng.getImage("image/background/layer_0002.png", "2");
	lpImageMng.getImage("image/background/layer_0003.png", "3");
	lpImageMng.getImage("image/background/layer_0004.png", "4");
	lpImageMng.getImage("image/background/layer_0005.png", "5");
	lpImageMng.getImage("image/background/layer_0006.png", "6");
	lpImageMng.getImage("image/background/layer_0007.png", "7");
	lpImageMng.getImage("image/background/layer_0008.png", "8");


	lpImageMng.getImage("image/back/block/For/Tileset.png", "Block",16,16,10,6);

	
	for (int i = 0; i < ACTIVEMAP; i++)
	{
		_layer[i] = MakeScreen(GameMapSize.x, GameMapSize.y, true);
	}

	_layer0 = MakeScreen(GameMapSize.x, GameMapSize.y, true);
	_layer1 = MakeScreen(GameMapSize.x, GameMapSize.y, true);
	_layer2 = MakeScreen(GameMapSize.x, GameMapSize.y, true);

	fopen_s(&indexFp,"mapdata/index.txt","r");
	if(indexFp == nullptr)
	{
		return;
	}

	Init();
}

MapMng::~MapMng()
{
		fclose(indexFp);
}

bool MapMng::getHitMap(const Vector2& pos, int stage)
{
	Vector2 chip = pos / CHIP_SIZE;

	if (chip.x < 0 || chip.x >= MapChipX || chip.y < 0 || chip.y >= MapChipY)
	{
		return true;
	}
	for (int i = 0; i < ACTIVEMAP; i++)
	{
		if (_activeMap[i].second == stage)
		{
			return (HitMap[chip.y][chip.x][i] == 1);
		}
	}

	return false;
	exit(1);
	return (HitMap[chip.y][chip.x][stage] == 1);
}

char MapMng::getGameMapM(const Vector2& pos, int stage)
{
	Vector2 chip = pos / CHIP_SIZE;

	if (chip.x < 0 || chip.x >= MapChipX || chip.y < 0 || chip.y >= MapChipY)
	{
		return 0;
	}

	for (int i = 0; i < ACTIVEMAP; i++)
	{
		if (_activeMap[i].second == stage)
		{
			char a = GameMap[chip.y][chip.x][i];

			return GameMap[chip.y][chip.x][i];
		}
	}

	exit(1);
	return GameMap[chip.y][chip.x][stage];
}

