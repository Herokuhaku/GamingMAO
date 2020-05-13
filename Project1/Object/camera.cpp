#include "camera.h"
#include "../Manage/MapMng.h"

void camera::Update(void)
{
	_cPos->x = _oldPlPos[0].x + _cOffSet.x;
	_cPos->y = _oldPlPos[0].y + _cOffSet.y;

	for (int i = 0; i < 3; i++)
	{
		_oldPlPos[i] = _oldPlPos[i + 1];
	}
	_oldPlPos[2] = _plObj.at(lpTimeMng.getTime())->getPos();
	CheckPos();
}

bool camera::CheckPos(void)
{
	if (_cPos->x < lpSceneMng.ScreenSize.x / 2)
	{
		_cPos->x = lpSceneMng.ScreenSize.x / 2;
	}

	if (_cPos->x > lpMapMng.GameMapSize.x - (lpSceneMng.ScreenSize.x / 2))
	{
		_cPos->x = lpMapMng.GameMapSize.x - (lpSceneMng.ScreenSize.x / 2);
	}
	return false;
}

void camera::Draw(void)
{
}

camera::camera() : _cPos{ new Vector2D(0,0) }
{
	_plObj.emplace(TIME::NOW, lpSceneMng.GetPlObj2(TIME::NOW));
	_plObj.emplace(TIME::FTR, lpSceneMng.GetPlObj2(TIME::FTR));

	_cOffSet = { 0,-140 };

	_cPos->x = _plObj.at(lpTimeMng.getTime())->getPos().x;
	_cPos->y = _plObj.at(lpTimeMng.getTime())->getPos().y;
	lpSceneMng.SetcPos(_cPos);
	for (int i = 0; i < 10; i++)
	{
		_oldPlPos[i] = _plObj.at(lpTimeMng.getTime())->getPos();
	}
}

camera::~camera()
{
}