#include <algorithm>
#include <string>
#include "ImageMng.h"
#include "../Manage/MapMng.h"
#include "../Scene/SceneMng.h"

#define SCREEN_SIZE_X lpSceneMng.ScreenSize.x
#define SCREEN_SIZE_Y lpSceneMng.ScreenSize.y

ImageMng* ImageMng::sInstance = nullptr;

void ImageMng::setEffect(EFFECT effect, Vector2Template<int> pos)
{
	//_effectList.emplace_back(std::make_tuple(effect, pos, 0, 0));
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
	std::sort(_drawList.begin(), _drawList.end(), [](DrawData i,DrawData j) {
		return (std::tie(std::get<static_cast<int>(DrawElm::LAYER)>(i), std::get<static_cast<int>(DrawElm::ZORDER)>(i)) <
			std::tie(std::get<static_cast<int>(DrawElm::LAYER)>(j), std::get<static_cast<int>(DrawElm::ZORDER)>(j)));
	});

	SetDrawScreen(_workLayer);
	ClsDrawScreen();

	for (auto data : _drawList)
	{
		int id, x, y;
		double rad;
		LAYER layer;

		std::tie(id, x, y, rad, layer, std::ignore) = data;

		DrawRotaGraph(x, y, 1.0, rad, id, true);
	}

	
	SetDrawScreen(DX_SCREEN_BACK);
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

	ScreenEffect();

	ScreenFlip();

	_drawList.clear();
}

void ImageMng::UpdateEffect(void)
{
	for (auto data = _effectList.begin(); data != _effectList.end();)
	{
		EFFECT effect;
		Vector2Template<int> pos;
		int count, flame;

		std::tie(effect, pos, count, flame) = (*data);

   		AddDraw({ _effectMap[effect][count].first , pos.x, pos.y, 0.0, LAYER::UI, 1000 });

		std::get<3>(*data)++;

		if (flame >= _effectMap[effect][count].second)
		{
			std::get<2>(*data)++;
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
	_drawList.emplace_back(data);
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
		_plmoveF = false;
	}
}

void ImageMng::FadeOut(void)
{
	int bright = _fadeCnt;
	SetDrawBright(bright,bright,bright);
	_fadeCnt += _fadeSpeed;
	if(_fadeCnt <= 0)
	{
		if(_plmoveF)
		{
			setGkind(ScrEff::FADEIN);
			lpSceneMng.GetPlObj2(lpTimeMng.getTime())->nextPos();
		}
		else
		{
			_Gkind = ScrEff::MAX;
		}
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
					_fadeSpeed = 4;
					break;
			case ScrEff::FADEOUT:
					_fadeCnt = 255;
					_fadeSpeed = -4;
					break;
			case ScrEff::FADE2X:
					_fadeCnt = 255;
					_fadeSpeed = -4;
					break;
			default:
					break;
	}
}

ImageMng::ImageMng()
{
	ImageMngInit();
	_workLayer = MakeScreen(2560,1440,  true);
}


ImageMng::~ImageMng()
{
}

void ImageMng::ImageMngInit(void)
{
	getImage("image/effect.png", "gripEffect", 64, 64, 3, 1);
	_fadeCnt = 255;
	_fadeSpeed = -2;
	_Gkind = ScrEff::MAX;
	_plmoveF = false;
}

