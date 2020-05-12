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

TimeMng::TimeMng()
{
	_crTime = TIME::NOW;
}

TimeMng::~TimeMng()
{

}
