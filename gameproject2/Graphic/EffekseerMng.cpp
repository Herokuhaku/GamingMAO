#include "EffekseerMng.h"

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

int EffekseerMng::playEffect(const int& efcHd, const int& time)
{
	int playEfcHd = PlayEffekseer2DEffect(efcHd);
	_effectList.emplace_back(playEfcHd, time);
	return playEfcHd;
}

void EffekseerMng::stopEffectAll(void)
{
	for (auto data : _effectList)
	{
		StopEffekseer2DEffect(data.first);
	}
	_effectList.clear();
}

void EffekseerMng::UpdateEffekseer(void)
{
	UpdateEffekseer2D();
	DrawEffekseer2D();
	for (auto data = _effectList.begin(); data != _effectList.end();)
	{
		(*data).second--;
		if ((*data).second <= 0)
		{
			StopEffekseer2DEffect((*data).first);
			data = _effectList.erase(data);
		}
		else
		{
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
