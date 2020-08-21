#include <algorithm>
#include <string>
#include "ImageMng.h"
#include "../Scene/SceneMng.h"
#include "../Object/Enemy/EnemyMng.h"
#include "EffekseerMng.h"
#include "../Manage/MapMng.h"

#define SCREEN_SIZE_X lpSceneMng.ScreenSize.x
#define SCREEN_SIZE_Y lpSceneMng.ScreenSize.y

ImageMng* ImageMng::sInstance = nullptr;


void ImageMng::setEffect(const std::string & key, EffectData& data)
{
	_effectMap.try_emplace(key, std::move(data));
}

const std::vector<int>& ImageMng::getImage(const std::string& key)
{
	return getImage(key,key);
}

const std::vector<int>& ImageMng::getImage(const std::string& filename, const std::string& key)
{
	if (_imageMap.find(key) == _imageMap.end())
	{
		_imageMap[key].resize(1);
		_imageMap[key][0] = (key, LoadGraph(filename.c_str(), true));
	}

	return _imageMap[key];
}

const std::vector<int>& ImageMng::getImage(const std::string& filename, const std::string& key, int size_x, int size_y, int cnt_x, int cnt_y)
{
	if (_imageMap.find(key) == _imageMap.end())
	{
		_imageMap[key].resize(cnt_x * cnt_y);
		LoadDivGraph(filename.c_str(), cnt_x * cnt_y, cnt_x, cnt_y, size_x, size_y, &_imageMap[key][0], true);
	}
	return _imageMap[key];
}

void ImageMng::Draw(void)
{
	UpdateEffect();
	// レイヤーとzオーダーでソート
	std::sort(_drawList[0].begin(), _drawList[0].end(), [](DrawData i,DrawData j) {
		return (std::tie(std::get<static_cast<int>(DrawElm::LAYER)>(i), std::get<static_cast<int>(DrawElm::ZORDER)>(i)) <
			std::tie(std::get<static_cast<int>(DrawElm::LAYER)>(j), std::get<static_cast<int>(DrawElm::ZORDER)>(j)));
	});

	std::sort(_drawList[1].begin(), _drawList[1].end(), [](DrawData i,DrawData j) {
		return (std::tie(std::get<static_cast<int>(DrawElm::LAYER)>(i), std::get<static_cast<int>(DrawElm::ZORDER)>(i)) <
			std::tie(std::get<static_cast<int>(DrawElm::LAYER)>(j), std::get<static_cast<int>(DrawElm::ZORDER)>(j)));
	});

	SetDrawScreen(_workLayer);
	ClsDrawScreen();

	if (lpTimeMng.getTime() == TIME::FTR)
	{
		SetDrawScreen(_tmpWorkLayer);
		ClsDrawScreen();
	}

	for (const auto& data : _drawList[0])
	{
		int id, x, y, blend, prm;
		double exRate, rad;
		LAYER layer;

		std::tie(id, x, y, exRate, rad, layer, std::ignore, blend, prm) = data;

		if (blend != _oldBlend.first || prm != _oldBlend.second)
		{
			SetDrawBlendMode(blend, prm);
			_oldBlend = { blend, prm };
		}

		DrawRotaGraph(x, y, exRate, rad, id, true);
	}

	
	SetDrawScreen(_screen);
	ClsDrawScreen();

	int x, y;
	x = static_cast<int>(lpSceneMng.GetcPos().x - (SCREEN_SIZE_X / 2));
	y = static_cast<int>(lpSceneMng.GetcPos().y - (SCREEN_SIZE_Y / 2));
	
	if (lpTimeMng.getTime() == TIME::FTR)
	{
		//GraphFilter(_workLayer, DX_GRAPH_FILTER_HSB, 0, 0, -255, 0);
		//GraphFilterBlt(_tmpWorkLayer, _workLayer, DX_GRAPH_FILTER_HSB, 0, 0, -255, 0);
		GraphFilterRectBlt(_tmpWorkLayer, _workLayer, x, y, x + SCREEN_SIZE_X, y + SCREEN_SIZE_Y, x, y, DX_GRAPH_FILTER_HSB, 0, 0, -255, 0);
	}
	
	DrawRectGraph(0, 0, x, y, SCREEN_SIZE_X, SCREEN_SIZE_Y, _workLayer, false, false);

	DrawBox(0, lpSceneMng.ScreenSize.y - 100, lpSceneMng.ScreenSize.x, lpSceneMng.ScreenSize.y, 0x123456,true);
	DrawEffekseer2D_Begin();
	lpEffectMng.UpdateEffekseer();
	DrawEffekseer2D_End();

	for (const auto& data : _drawList[1])
	{
		int id, x, y, blend, prm;
		double ex_rate, rad;
		LAYER layer;

		std::tie(id, x, y, ex_rate, rad, layer, std::ignore, blend, prm) = data;

		if (blend != _oldBlend.first || prm != _oldBlend.second)
		{
			SetDrawBlendMode(blend, prm);
			_oldBlend = { blend, prm };
		}

		DrawRotaGraph(x, y, ex_rate, rad, id, true);
	}

	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();
	DrawGraph(0,0,_screen,true);

	ScreenEffect();
	DrawFormatString(10, 10, 0xffffff, "fps %.3f", GetFPS());
	DrawFormatString(10, 30, 0xffffff, "DC %d", GetDrawCallCount());

	ScreenFlip();

	_drawList[0].clear();
	_drawList[1].clear();
}

void ImageMng::Draw(int screen, bool deleteFlag)
{
	UpdateEffect();
	// レイヤーとzオーダーでソート
	std::sort(_drawList[0].begin(), _drawList[0].end(), [](DrawData i, DrawData j) {
		return (std::tie(std::get<static_cast<int>(DrawElm::LAYER)>(i), std::get<static_cast<int>(DrawElm::ZORDER)>(i)) <
			std::tie(std::get<static_cast<int>(DrawElm::LAYER)>(j), std::get<static_cast<int>(DrawElm::ZORDER)>(j)));
	});

	std::sort(_drawList[1].begin(), _drawList[1].end(), [](DrawData i, DrawData j) {
		return (std::tie(std::get<static_cast<int>(DrawElm::LAYER)>(i), std::get<static_cast<int>(DrawElm::ZORDER)>(i)) <
			std::tie(std::get<static_cast<int>(DrawElm::LAYER)>(j), std::get<static_cast<int>(DrawElm::ZORDER)>(j)));
	});

	SetDrawScreen(_workLayer);
	ClsDrawScreen();

	if (lpTimeMng.getTime() == TIME::FTR)
	{
		SetDrawScreen(_tmpWorkLayer);
		ClsDrawScreen();
	}

	for (const auto& data : _drawList[0])
	{
		int id, x, y, blend, prm;
		double ex_rate, rad;
		LAYER layer;

		std::tie(id, x, y, ex_rate, rad, layer, std::ignore, blend, prm) = data;

		if (blend != _oldBlend.first || prm != _oldBlend.second)
		{
			SetDrawBlendMode(blend, prm);
			_oldBlend = { blend, prm };
		}

		DrawRotaGraph(x, y, ex_rate, rad, id, true);
	}


	SetDrawScreen(_screen);
	ClsDrawScreen();

	int x, y;
	x = static_cast<int>(lpSceneMng.GetcPos().x - (SCREEN_SIZE_X / 2));
	y = static_cast<int>(lpSceneMng.GetcPos().y - (SCREEN_SIZE_Y / 2));

	if (lpTimeMng.getTime() == TIME::FTR)
	{
		//GraphFilterBlt(_tmpWorkLayer, _workLayer, DX_GRAPH_FILTER_HSB, 0, 0, -255, 0);
		GraphFilterRectBlt(_tmpWorkLayer, _workLayer, x, y, x + SCREEN_SIZE_X, y + SCREEN_SIZE_Y, x, y, DX_GRAPH_FILTER_HSB, 0, 0, -255, 0);
	}

	DrawRectGraph(0, 0, x, y, SCREEN_SIZE_X, SCREEN_SIZE_Y, _workLayer, false, false);

	DrawBox(0, lpSceneMng.ScreenSize.y - 100, lpSceneMng.ScreenSize.x, lpSceneMng.ScreenSize.y, 0x123456, true);
	DrawEffekseer2D_Begin();
	lpEffectMng.UpdateEffekseer();
	DrawEffekseer2D_End();

	for (const auto& data : _drawList[1])
	{
		int id, x, y, blend, prm;
		double ex_rate, rad;
		LAYER layer;

		std::tie(id, x, y, ex_rate, rad, layer, std::ignore, blend, prm) = data;

		if (blend != _oldBlend.first || prm != _oldBlend.second)
		{
			SetDrawBlendMode(blend, prm);
			_oldBlend = { blend, prm };
		}

		DrawRotaGraph(x, y, ex_rate, rad, id, true);
	}

	SetDrawScreen(screen);
	ClsDrawScreen();
	DrawGraph(0, 0, _screen, true);

	ScreenEffect();

	if (deleteFlag)
	{
		_drawList[0].clear();
		_drawList[1].clear();
	}
}

void ImageMng::playEffect(std::string key, const int* posX, const int* posY, double exRate, double rad, LAYER layer, int zOrder, int blend_mode, int blend_prm, int stage, EffectDrawType draw = EffectDrawType::DRAW_TO_RELATIVE)
{
	if (_effectMap.find(key) == _effectMap.end())
	{
		return;
	}
	_effectList.emplace_back(std::make_tuple(key, posX, posY, exRate, rad, layer, zOrder, blend_mode, blend_prm, 0, 0, stage, draw));
}

void ImageMng::stopEffect(void)
{
	_effectList.clear();
}

void ImageMng::UpdateEffect(void)
{
	for (auto data = _effectList.begin(); data != _effectList.end();)
	{
		std::string key;
		LAYER layer;
		int posX, posY, count, flame, blend, zOrder, prm, stage;
		double ex_rate, rad;
		EffectDrawType drawType;

		std::tie(key, std::ignore, std::ignore, ex_rate, rad, layer, zOrder, blend, prm, count, flame, stage, drawType) = (*data);

		if (std::get<11>(*data) == lpMapMng.GetnowStage() || std::get<11>(*data) == -1)
		{
			posX = *(std::get<static_cast<int>(EffectElm::X)>(*data));
			posY = *(std::get<static_cast<int>(EffectElm::Y)>(*data));

			if (drawType == EffectDrawType::DRAW_TO_RELATIVE)
			{
				AddDraw({ _effectMap[key][count].first , posX, posY, ex_rate, rad, layer, zOrder, blend, prm });
			}
			else if (drawType == EffectDrawType::DRAW_TO_ABSOLUTE)
			{
				AddBackDraw({ _effectMap[key][count].first , posX, posY, ex_rate, rad, layer, zOrder, blend, prm });
			}
			else
			{
				// なにもなし
			}
		}

		flame++;
		std::get<static_cast<int>(EffectElm::FLAME)>(*data)++;

		if (flame >= _effectMap[key][count].second)
		{
			std::get<static_cast<int>(EffectElm::COUNT)>(*data)++;
			count++;
			if (_effectMap[key][count].second == -1)
			{
				data = _effectList.erase(data);
			}
			else
			{
				data++;
			}
		}
		else
		{
			data++;
		}
	}
}

void ImageMng::AddDraw(DrawData data)
{
	_drawList[0].emplace_back(data);
}

void ImageMng::AddBackDraw(DrawData data)
{
	_drawList[1].emplace_back(data);
}

void ImageMng::ScreenEffect(void)
{
	switch(_Gkind)
	{
			case ScrEff::FADE:
					Fade();
					break;
			case ScrEff::FADEIN:
					FadeIn();
					break;
			case ScrEff::FADEOUT:
					FadeOut();
					break;
			case ScrEff::FADE2X:
					Fade();
					break;
			case ScrEff::MAX:
					break;
			default:
				break;

	}
}

void ImageMng::Fade(void)
{
	int bright = std::abs( 255 - std::abs(_fadeCnt - 255));
	SetDrawBright(bright,bright,bright);
	_fadeCnt += _fadeSpeed;
	if(_fadeCnt <= -255)
	{
		_Gkind = ScrEff::MAX;
		SetDrawBright(255,255,255);
	}
}

void ImageMng::FadeIn(void)
{
	int bright = _fadeCnt;
	SetDrawBright(bright,bright,bright);
	_fadeCnt += _fadeSpeed;
	if(_fadeCnt >= 255)
	{
		_Gkind = ScrEff::MAX;
		_plSmoveF = false;
	}
}

void ImageMng::FadeOut(void)
{
	int bright = _fadeCnt;
	SetDrawBright(bright,bright,bright);
	_fadeCnt += _fadeSpeed;

 		DrawGraph(0,0,_screenCap,false);

	if(_fadeCnt <= 0)
	{
		if(_plSmoveF)
		{
			setGkind(ScrEff::FADEIN);
			// std::get では変数は使えない？
			SetDrawBright(255, 255, 255);
			switch (_plFBXmoveF)
			{
			int nstage;
			case MAP_DATA::BACK:
				nstage = std::get<3>(lpMapMng.GetMapIndex(lpMapMng.GetnowStage()));
				lpEnemyMng.StageTrans(lpMapMng.GetnowStage(), nstage);
				(*lpSceneMng.GetPlObj(lpTimeMng.getTime()))->setStage(nstage);
				lpMapMng.StageTrans(std::get<3>(lpMapMng.GetMapIndex(lpMapMng.GetnowStage())));
				// 3 = MAP_DATA::BACK
				break;
			case MAP_DATA::FRONT:
				nstage = std::get<4>(lpMapMng.GetMapIndex(lpMapMng.GetnowStage()));
				lpEnemyMng.StageTrans(lpMapMng.GetnowStage(), nstage);
				(*lpSceneMng.GetPlObj(lpTimeMng.getTime()))->setStage(nstage);
				lpMapMng.StageTrans(std::get<4>(lpMapMng.GetMapIndex(lpMapMng.GetnowStage())));
				// 4 = MAP_DATA::FRONT
				break;
			case MAP_DATA::BRANCH:
				nstage = std::get<5>(lpMapMng.GetMapIndex(lpMapMng.GetnowStage()));
				lpEnemyMng.StageTrans(lpMapMng.GetnowStage(), nstage);
				(*lpSceneMng.GetPlObj(lpTimeMng.getTime()))->setStage(nstage);
				lpMapMng.StageTrans(std::get<5>(lpMapMng.GetMapIndex(lpMapMng.GetnowStage())));
				// 5 = MAP_DATA::BRANCH
				break;
			default:
				exit(1);
				break;
			}
			SetDrawBright(0, 0, 0);
			lpSceneMng.GetPlObj2(lpTimeMng.getTime())->nextPos();
		}
		else
		{
			_Gkind = ScrEff::MAX;
		}
			setGkind(ScrEff::FADEIN);
	}
}

void ImageMng::setGkind(ScrEff kind)
{
	_Gkind = kind;
	switch(_Gkind)
	{
			case ScrEff::FADE:
					_fadeCnt = 255;
					break;
			case ScrEff::FADEIN:
					_fadeCnt = 0;
					_fadeSpeed = 15;
					break;
			case ScrEff::FADEOUT:

					SetDrawScreen(_screenCap);
					ClsDrawScreen();
					DrawGraph(0, 0, _screen, true);
					_screenCapF = false;
					SetDrawScreen(DX_SCREEN_BACK);

					_screenCapF = true;
					_fadeCnt = 255;
					_fadeSpeed = -15;
					break;
			case ScrEff::FADE2X:
					_fadeCnt = 255;
					_fadeSpeed = -4;
					break;
			default:
					break;
	}
}

void ImageMng::SetplmoveF(bool plSmoveF, MAP_DATA plf)
{
	_plSmoveF = plSmoveF; 
	_plFBXmoveF = plf; 
}

ImageMng::ImageMng()
{
	ImageMngInit();
	_workLayer = MakeScreen(2560,1440,  true);
	_tmpWorkLayer = MakeScreen(2560, 1440, true);
	_screenCap = MakeScreen(lpSceneMng.ScreenSize.x,lpSceneMng.ScreenSize.y,true);
	_screen =  MakeScreen(lpSceneMng.ScreenSize.x,lpSceneMng.ScreenSize.y,true);
}


ImageMng::~ImageMng()
{
}

void ImageMng::ImageMngInit(void)
{
	_fadeCnt = 255;
	_fadeSpeed = -2;
	_Gkind = ScrEff::MAX;
	_plSmoveF = false;
	_plFBXmoveF = MAP_DATA::BACK;
	_screenCapF = true;
	_oldBlend = { DX_BLENDMODE_NOBLEND,0 };
}

