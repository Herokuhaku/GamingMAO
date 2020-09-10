#include "TimeMng.h"
#include "../Scene/SceneMng.h"
#include "MapMng.h"

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
		_changeTime = 0;
	}
}

void TimeMng::resetFlag(void)
{
	if (_changeTime == 0 && _changeFlag)
	{
		_crTime = static_cast<TIME>(1 - static_cast<int>(_crTime));
		_changeFlag = false;

		// ステージが変わっているか
		if ((*lpSceneMng.GetPlObj(TIME::FTR))->getStage() != (*lpSceneMng.GetPlObj(TIME::NOW))->getStage())
		{
			lpMapMng.StageTrans((*lpSceneMng.GetPlObj(_crTime))->getStage());
		}
	}

	if (_changeTime > 0)
	{
		_changeTime--;
	}
}

void TimeMng::TimeInit(void)
{
	_changeFlag = false;
	_changeTime = 0;
	_crTime = TIME::NOW;
}

TimeMng::TimeMng()
{
	TimeInit();
}

TimeMng::~TimeMng()
{

}
