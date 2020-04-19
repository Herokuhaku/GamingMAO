#include <DxLib.h>
#include "SceneMng.h"
#include "TitleScene.h"
#include "../Graphic/ImageMng.h"
#include "ButtonMng.h"

SceneMng *SceneMng::sInstance = nullptr;

void SceneMng::Run(void)
{
	SysInit();
	_activeScene = std::make_unique<TitleScene>();
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		lpButtonMng.Run();
		_activeScene = (*_activeScene).Update(std::move(_activeScene));
		lpImageMng.Draw();

		_flame++;

		//(*_activeScene).RunActQue(std::move(_actList));
	}
}

const std::shared_ptr<Object> *SceneMng::GetPlObj(void) const
{
	return &_plObj;
}

void SceneMng::SetPlObj(std::shared_ptr<Object> plObj)
{
	_plObj = std::move(plObj);
}

bool SceneMng::SysInit(void)
{
	bool rtnFlag = true;

	SetWindowText("AGAME");
	SetGraphMode(600, 500, 16);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)
	{
		rtnFlag = false;
	}

	SetDrawScreen(DX_SCREEN_BACK);
	
	lpImageMng.getImage("image/player.png", "player", 85, 90, 2, 2);
		lpImageMng.getImage("image/player.png", "player", 85, 90, 2, 2);
	lpImageMng.getImage("image/player_walk.png", "player_walk", 85, 90, 8, 2);

	lpImageMng.getImage("image/small_dragonR.png", "s_dragonR", 128, 128, 4, 5);
	lpImageMng.getImage("image/small_dragonL.png", "s_dragonL", 128, 128, 4, 5);

	_flame = 0;

	return rtnFlag;
}

SceneMng::SceneMng()
{
}

SceneMng::~SceneMng()
{
}
