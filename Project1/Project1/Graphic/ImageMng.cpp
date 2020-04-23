#include <algorithm>
#include "ImageMng.h"
#include <string>
#include "../MapMng.h"

ImageMng* ImageMng::sInstance = nullptr;

void ImageMng::setEffect(EFFECT effect, Vector2Template<int> pos)
{
	_effectList.emplace_back(std::make_tuple(effect, pos, 0, 0));
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
	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();

	// レイヤーとzオーダーでソート
	std::sort(_drawList.begin(), _drawList.end(), [](DrawData i,DrawData j) {
		return (std::tie(std::get<static_cast<int>(DrawElm::LAYER)>(i), std::get<static_cast<int>(DrawElm::ZORDER)>(i)) <
			std::tie(std::get<static_cast<int>(DrawElm::LAYER)>(j), std::get<static_cast<int>(DrawElm::ZORDER)>(j)));
	});

	for (auto data : _drawList)
	{
		int id, x, y;
		double rad;
		LAYER layer;

		std::tie(id, x, y, rad, layer, std::ignore) = data;


		DrawRotaGraph(x, y, 1.0, rad, id, true);
	}

	lpMapMng.BlockDraw();

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

ImageMng::ImageMng()
{
	ImageMngInit();
}


ImageMng::~ImageMng()
{
}

void ImageMng::ImageMngInit(void)
{
	getImage("image/effect.png", "gripEffect", 64, 64, 3, 1);

	_effectMap[EFFECT::GRIP].emplace_back(std::make_pair(getImage("gripEffect")[0], 3));
	_effectMap[EFFECT::GRIP].emplace_back(std::make_pair(getImage("gripEffect")[1], 6));
	_effectMap[EFFECT::GRIP].emplace_back(std::make_pair(getImage("gripEffect")[2], 9));
	_effectMap[EFFECT::GRIP].emplace_back(std::make_pair(getImage("gripEffect")[2], -1));

	getImage("image/smoke.png", "smokeEffect", 64, 64, 6, 1);

	_effectMap[EFFECT::SMOKE].emplace_back(std::make_pair(getImage("smokeEffect")[0], 3));
	_effectMap[EFFECT::SMOKE].emplace_back(std::make_pair(getImage("smokeEffect")[1], 6));
	_effectMap[EFFECT::SMOKE].emplace_back(std::make_pair(getImage("smokeEffect")[2], 9));
	_effectMap[EFFECT::SMOKE].emplace_back(std::make_pair(getImage("smokeEffect")[3], 12));
	_effectMap[EFFECT::SMOKE].emplace_back(std::make_pair(getImage("smokeEffect")[4], 15));
	_effectMap[EFFECT::SMOKE].emplace_back(std::make_pair(getImage("smokeEffect")[5], 18));
	_effectMap[EFFECT::SMOKE].emplace_back(std::make_pair(getImage("smokeEffect")[5], -1));
}




