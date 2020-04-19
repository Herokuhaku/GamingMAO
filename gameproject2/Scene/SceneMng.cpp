#include <DxLib.h>
#include "SceneMng.h"
#include "TitleScene.h"
#include "../Graphic/ImageMng.h"

SceneMng *SceneMng::sInstance = nullptr;

void SceneMng::Run(void)
{
	SysInit();
	_activeScene = std::make_unique<GameScene>();
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		lpKeyMng.KeyUpdate();
		_activeScene = (*_activeScene).Update(std::move(_activeScene));
		lpImageMng.Draw();

		_flame++;

		
		//(*_activeScene).RunActQue(std::move(_actList));
	}
}

bool SceneMng::SysInit(void)
{
	bool rtnFlag = true;

	SetWindowText("AGAME");
	SetGraphMode(1280, 720, 16);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)
	{
		rtnFlag = false;
	}

	SetDrawScreen(DX_SCREEN_BACK);

	_flame = 0;

	lpImageMng.getImage("image/player.png", "player", 85, 90, 2, 2);
	lpImageMng.getImage("image/player_walk.png", "player_walk", 85, 90, 8, 2);


	return rtnFlag;
}

SceneMng::SceneMng()
{
}

SceneMng::~SceneMng()
{
}
