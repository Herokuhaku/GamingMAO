#include "EffekseerMng.h"
#include "../Scene/SceneMng.h"


EffekseerMng* EffekseerMng::sInstance = nullptr;

int EffekseerMng::getEffect(const std::string & key)
{
	return getEffect(key,key,1.0f);
}

int EffekseerMng::getEffect(const std::string & filename, const std::string & key, const float& exLate)
{
	if (_effectMap.find(key) == _effectMap.end())
	{
		_effectMap[key] = LoadEffekseerEffect(filename.c_str(), exLate);
	}
	return _effectMap[key];
}

int EffekseerMng::playEffect(const int efcHd, const int time, int* pos_x, int* pos_y, int offset_x, int offset_y, DIR* dir)
{
	int playEfcHd = PlayEffekseer2DEffect(efcHd);
	_effectList.emplace_back(playEfcHd, time, std::make_pair(pos_x, pos_y), std::make_pair(offset_x, offset_y), dir);
	return playEfcHd;
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
	UpdateEffekseer2D();
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
			DrawEffekseer2D_Draw(handle);
			data++;
		}
	}
}

EffekseerMng::EffekseerMng()
{
}


EffekseerMng::~EffekseerMng()
{
}

void EffekseerMng::EffectMngInit(void)
{
}
