#include "camera.h"

void camera::Update(void)
{
	_cPos->x = _oldPlPos[0].x;
	_cPos->y = _oldPlPos[0].y;
	for (int i = 0; i < 9; i++)
	{
		_oldPlPos[i] = _oldPlPos[i + 1];
	}
	_oldPlPos[9] = _plObj->getPos();
}

void camera::Draw(void)
{
}

camera::camera() : _plObj{ lpSceneMng.GetPlObj2() }, _cPos{ new Vector2D(0,0) }
{
	_cPos->x = _plObj->getPos().x;
	_cPos->y = _plObj->getPos().y;
	lpSceneMng.SetcPos(_cPos);
	for (int i = 0; i < 10; i++)
	{
		_oldPlPos[i] = _plObj->getPos();
	}
	_type = OBJ_TYPE::CAMERA;
}

camera::~camera()
{
}