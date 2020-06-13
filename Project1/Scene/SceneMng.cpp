#include <DxLib.h>
#include "SceneMng.h"
#include "TitleScene.h"
#include "../Graphic/ImageMng.h"
#include "../Manage/ButtonMng.h"
#include "../Manage/KeyMng.h"

SceneMng *SceneMng::sInstance = nullptr;

void SceneMng::Run(void)
{
	SysInit();
	_activeScene = std::make_unique<TitleScene>();
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		lpKeyMng.KeyUpdate();
		lpButtonMng.Run();

		lpStrAdd.ClearScreen();

		_activeScene = (*_activeScene).Update(std::move(_activeScene));
		
		lpStrAdd.Draw();
		lpImageMng.Draw();

		_flame++;

		//(*_activeScene).RunActQue(std::move(_actList));
	}
}

const Vector2 SceneMng::GetPlPos(TIME time) const
{
	if (_plObj.find(time) == _plObj.end())
	{
		exit(1);
		return { 0,0 };
	}
	return _plObj.at(time)->getPos();
}

const std::shared_ptr<Object> SceneMng::GetPlObj2(TIME time) const
{
	if (_plObj.find(time) == _plObj.end())
	{
		exit(1);
		return nullptr;
	}
	return _plObj.at(time);
}

const std::shared_ptr<Object>* SceneMng::GetPlObj(TIME time) const
{
	if (_plObj.find(time) == _plObj.end())
	{
		exit(1);
		return nullptr;
	}
	return &(_plObj.at(time));
}

void SceneMng::SetPlObj(std::shared_ptr<Object>& plObj, TIME time)
{
	_plObj.insert_or_assign(time, plObj);
}

const Vector2D SceneMng::GetcPos(void) const
{
	Vector2D tmp = { _cPos->x,_cPos->y };
	return tmp;
}

const std::shared_ptr<Vector2D> SceneMng::GetccPos(void) const
{
	return _cPos;
}

void SceneMng::SetcPos(std::shared_ptr<Vector2D> cPos)
{
	_cPos = cPos;
}

void SceneMng::SetNum(int num)
{
	_work = num;
}

int SceneMng::GetNum(void)
{
	return _work;
}

bool SceneMng::SysInit(void)
{
	bool rtnFlag = true;

	SetWindowText("AGAME");
	SetGraphMode(ScreenSize.x, ScreenSize.y, 16);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)
	{
		rtnFlag = false;
	}

	SetDrawScreen(DX_SCREEN_BACK);
	// effekseer ÇÃèâä˙ê›íË
	if (Effekseer_Init(5000) == -1)	// 5000 âÊñ ç≈ëÂÇÃó 
	{
		return false;
	}

	SetUseDirect3DVersion(DX_DIRECT3D_11);	// verê›íË
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	Effekseer_Set2DSetting(ScreenSize.x, ScreenSize.y);

	std::shared_ptr<Vector2D> work(new Vector2D(0,0));
	_cPos = work;

	_flame = 0;

 	_work = MakeScreen(ScreenSize.x, ScreenSize.y, true);

	std::random_device rd;
	std::mt19937 makerand(rd());
	_rnd = makerand;

	return rtnFlag;
}

SceneMng::SceneMng()
{
}

SceneMng::~SceneMng()
{
	DxLib_End();
}
