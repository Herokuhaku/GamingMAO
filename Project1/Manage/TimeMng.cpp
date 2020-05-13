#include "TimeMng.h"

TimeMng* TimeMng::sInstance = nullptr;

void TimeMng::setTime(TIME time)
{
	_crTime = time;
}

TIME TimeMng::getTime(void)
{
	return _crTime;
}

void TimeMng::ChangeTime(void)
{
	if (!_changeFlag)
	{
		_changeFlag = true;
		_changeTime = 150;
	}
}

void TimeMng::resetFlag(void)
{
	if (_changeTime == 0 && _changeFlag)
	{
		_crTime = static_cast<TIME>(1 - static_cast<int>(_crTime));
		_changeFlag = false;
	}

	if (_changeTime > 0)
	{
		_changeTime--;
	}
}

TimeMng::TimeMng()
{
	_crTime = TIME::NOW;
	_changeFlag = false;
	_changeTime = 0;
}

TimeMng::~TimeMng()
{

}
