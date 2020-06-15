#include "EffekseerMng.h"
#include "../Scene/SceneMng.h"


EffekseerMng* EffekseerMng::sInstance = nullptr;
std::map<std::string, int> EffekseerMng::_effectMap;

int EffekseerMng::getEffect(const std::string & key)
{
	return getEffect(key,key,1.0f);
}

int EffekseerMng::getEffect(const std::string & filename, const std::string & key, const float& exRate)
{
	if (_effectMap.find(key) == _effectMap.end())
	{
		//_effectMap[key] = LoadEffekseerEffect(filename.c_str(), exRate);
		_effectMap.emplace(key, LoadEffekseerEffect(filename.c_str(), exRate));
	}
	return _effectMap[key];
}

int EffekseerMng::playEffect(const int efcHd, const int time, int* pos_x, int* pos_y, int offset_x, int offset_y, DIR* dir)
{
	int playEfcHd = PlayEffekseer2DEffect(efcHd);
	_effectList.emplace_back(playEfcHd, time, std::make_pair(pos_x, pos_y), std::make_pair(offset_x, offset_y), dir);
	return playEfcHd;
}

void EffekseerMng::stopEffect(int playEfkHd)
{
	auto eraseEfk = std::find_if(_effectList.begin(), _effectList.end(), [&](std::tuple<int, int, std::pair<int*, int*>, std::pair<int, int>, DIR*> val) {return std::get<0>(val) == playEfkHd; });
	
	if (eraseEfk == _effectList.end())
	{
		return;
	}
	
	_effectList.erase(eraseEfk);
	StopEffekseer2DEffect(playEfkHd);
}

void EffekseerMng::stopEffectAll(void)
{
	for (auto data : _effectList)
	{
		StopEffekseer2DEffect(std::get<std::underlying_type<EFK_DATA>::type(EFK_DATA::HD)>(data));
	}
	_effectList.clear();
}

void EffekseerMng::UpdateEffekseer(void)
{
	for (auto data = _effectList.begin(); data != _effectList.end();)
	{
		int handle, time;
		std::pair<int*, int*> pos;
		std::pair<int, int> offset;
		DIR* dir;
		
		std::tie(handle, time, pos, offset, dir) = (*data);

		time--;
		if (time <= 0)
		{
			StopEffekseer2DEffect(handle);
			data = _effectList.erase(data);
		}
		else
		{
			SetPosPlayingEffekseer2DEffect(handle,
				static_cast<float>(*(pos.first) - static_cast<int>(lpSceneMng.GetcPos().x) + lpSceneMng.ScreenSize.x / 2  + offset.first * (static_cast<int>(*dir) - 1)),
				static_cast<float>(*(pos.second) - static_cast<int>(lpSceneMng.GetcPos().y) + lpSceneMng.ScreenSize.y / 2 + offset.second), 0);
			data++;
		}
	}
	UpdateEffekseer2D();
	for (auto data : _effectList)
	{
		DrawEffekseer2D_Draw(std::get<0>(data));
	}
}

EffekseerMng::EffekseerMng()
{
}


EffekseerMng::~EffekseerMng()
{
	stopEffectAll();
	for (auto data : _effectMap)
	{
		DeleteEffekseerEffect(data.second);
	}
}

