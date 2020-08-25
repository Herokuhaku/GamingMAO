#include "StopTime.h"
#include "../../../Graphic/ImageMng.h"
#include "../../../Scene/SceneMng.h"

std::vector<int> StopTime::_image;

namespace
{
	constexpr int STOP_TIME = 300;

	bool _initialized = false;
}

StopTime::StopTime()
{
	Initialize();
}

void StopTime::Update(void)
{
	if (_timer > 0)
	{
		_timer--;
		if (_timer == 0)
		{
			_timeIsStoped = false;
		}
	}
}

void StopTime::Draw(void)
{
	int t = STOP_TIME - _timer;

	if (t >= _image.back())
	{
		return;
	}

	if (t >= _image[_current])
	{
		_current++;
		if (_current == 9)
		{
			_timeIsStoped = true;
		}
	}

	lpImageMng.AddBackDraw({ lpImageMng.getImage("clock_stop")[_current], lpSceneMng.ScreenSize.x / 2, lpSceneMng.ScreenSize.y / 2, 1.0, 0.0, LAYER::EX , 1000, DX_BLENDMODE_NOBLEND, 0 });
}

bool StopTime::IsTimeStoped(void)
{
	return _timeIsStoped;
}

bool StopTime::IsCountdowned(void)
{
	return _timer != 0;
}

void StopTime::Stop(void)
{
	_timer = STOP_TIME;
	_current = 0;
}

void StopTime::Initialize(void)
{
	if (_initialized)
	{
		return;
	}
	_initialized = true;

	lpImageMng.getImage("image/Attack/clock_stop.png", "clock_stop", 480, 480, 5, 3);

	_image.reserve(15);
	_image.emplace_back(2);
	_image.emplace_back(4);
	_image.emplace_back(6);
	_image.emplace_back(8);
	_image.emplace_back(12);
	_image.emplace_back(16);
	_image.emplace_back(23);
	_image.emplace_back(30);
	_image.emplace_back(32);
	_image.emplace_back(34);
	_image.emplace_back(36);
	_image.emplace_back(38);
	_image.emplace_back(40);
	_image.emplace_back(42);
	_image.emplace_back(56);
}
