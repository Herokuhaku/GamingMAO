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

	_flame = 0;

	return rtnFlag;
}

SceneMng::SceneMng()
{
}

SceneMng::~SceneMng()
{
}
