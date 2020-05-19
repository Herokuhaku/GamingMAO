#include <algorithm>
#include <string>
#include "ImageMng.h"
#include "../Manage/MapMng.h"
#include "../Scene/SceneMng.h"

#define SCREEN_SIZE_X lpSceneMng.ScreenSize.x
#define SCREEN_SIZE_Y lpSceneMng.ScreenSize.y

ImageMng* ImageMng::sInstance = nullptr;

void ImageMng::setEffect(EFFECT effect, Vector2Template<int> pos, double ex_rate, int zOrder, int blend_mode, int blend_prm)
{
	_effectList.emplace_back(std::make_tuple(effect, pos, ex_rate, zOrder, blend_mode, blend_prm, 0, 0));
}

std::vector<int> ImageMng::getImage(const std::string& key)
{
	return getImage(key,key);
}

std::vector<int> ImageMng::getImage(const std::string& filename, const std::string& key)
{
	if (_imageMap.find(key) == _imageMap.end())
	{
		_imageMap[key].resize(1);
		_imageMap[key][0] = (key, LoadGraph(filename.c_str(), true));
	}

	return _imageMap[key];
}

std::vector<int> ImageMng::getImage(const std::string& filename, const std::string& key, int size_x, int size_y, int cnt_x, int cnt_y)
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

	for (auto data : _drawList[0])
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
	x = lpSceneMng.GetcPos().x - (SCREEN_SIZE_X / 2);
	y = lpSceneMng.GetcPos().y - (SCREEN_SIZE_Y / 2);
	
	if (lpTimeMng.getTime() == TIME::FTR)
	{
		GraphFilter(_workLayer, DX_GRAPH_FILTER_HSB, 0, 0, -255, 0);
	}
	
	DrawRectGraph(0, 0, x, y, SCREEN_SIZE_X, SCREEN_SIZE_Y, _workLayer, false, false);

	DrawBox(0, lpSceneMng.ScreenSize.y - 100, lpSceneMng.ScreenSize.x, lpSceneMng.ScreenSize.y, 0x123456,true);
	DrawEffekseer2D_Begin();
	lpEffectMng.UpdateEffekseer();
	DrawEffekseer2D_End();

	for (auto data : _drawList[1])
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

	for (auto data : _drawList[0])
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
	x = lpSceneMng.GetcPos().x - (SCREEN_SIZE_X / 2);
	y = lpSceneMng.GetcPos().y - (SCREEN_SIZE_Y / 2);

	if (lpTimeMng.getTime() == TIME::FTR)
	{
		GraphFilter(_workLayer, DX_GRAPH_FILTER_HSB, 0, 0, -255, 0);
	}

	DrawRectGraph(0, 0, x, y, SCREEN_SIZE_X, SCREEN_SIZE_Y, _workLayer, false, false);

	DrawBox(0, lpSceneMng.ScreenSize.y - 100, lpSceneMng.ScreenSize.x, lpSceneMng.ScreenSize.y, 0x123456, true);
	DrawEffekseer2D_Begin();
	lpEffectMng.UpdateEffekseer();
	DrawEffekseer2D_End();

	for (auto data : _drawList[1])
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

void ImageMng::UpdateEffect(void)
{
	for (auto data = _effectList.begin(); data != _effectList.end();)
	{
		EFFECT effect;
		Vector2Template<int> pos;
		int count, flame, blend, zOrder, prm;
		double ex_rate;

		std::tie(effect, pos, ex_rate, zOrder, blend, prm, count, flame) = (*data);

		AddDraw({ _effectMap[effect][count].first , pos.x, pos.y, ex_rate, 0.0, LAYER::UI, 1000, blend, prm });

		flame++;

		if (flame >= _effectMap[effect][count].second)
		{
			count++;
			if (_effectMap[effect][count].second == -1)
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
			case MAP_DATA::BACK:
			(*lpSceneMng.GetPlObj(lpTimeMng.getTime()))->setStage(std::get<3>(lpMapMng.GetMapIndex(lpMapMng.GetnowStage())));
			lpMapMng.StageTrans(std::get<3>(lpMapMng.GetMapIndex(lpMapMng.GetnowStage())));
			// 3 = MAP_DATA::BACK
				break;
			case MAP_DATA::FRONT:
			(*lpSceneMng.GetPlObj(lpTimeMng.getTime()))->setStage(std::get<4>(lpMapMng.GetMapIndex(lpMapMng.GetnowStage())));
			lpMapMng.StageTrans(std::get<4>(lpMapMng.GetMapIndex(lpMapMng.GetnowStage())));
			// 4 = MAP_DATA::FRONT
				break;
			case MAP_DATA::BRANCH:
			(*lpSceneMng.GetPlObj(lpTimeMng.getTime()))->setStage(std::get<5>(lpMapMng.GetMapIndex(lpMapMng.GetnowStage())));
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

