#include <DxLib.h>
#include "SceneMng.h"
#include "TitleScene.h"
#include "../Graphic/ImageMng.h"
#include "ButtonMng.h"

SceneMng *SceneMng::sInstance = nullptr;

void SceneMng::Run(void)
{
	SysInit();
	_activeScene = std::make_unique<GameScene>();
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		lpKeyMng.KeyUpdate();
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
	SetGraphMode(1280, 720, 16);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)
	{
		rtnFlag = false;
	}
	if (Effekseer_Init(5000) == -1)
	{
		return false;
	}

	SetDrawScreen(DX_SCREEN_BACK);
	SetUseDirect3DVersion(DX_DIRECT3D_11);
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	Effekseer_Set2DSetting(ScreenSize.x, ScreenSize.y);

	
	lpImageMng.getImage("image/player.png", "player", 85, 90, 2, 2);
	lpImageMng.getImage("image/player_walk.png", "player_walk", 85, 90, 8, 2);
	lpImageMng.getImage("image/player_dash.png", "player_dash", 85, 90, 2, 2);
	lpImageMng.getImage("image/player_jump.png", "player_jump", 85, 90, 2, 2);
	lpImageMng.getImage("image/player_attack.png", "player_attack", 85, 90, 2, 12);

	lpImageMng.getImage("image/small_dragonR.png", "s_dragonR", 128, 128, 4, 5);
	lpImageMng.getImage("image/small_dragonL.png", "s_dragonL", 128, 128, 4, 5);
	lpImageMng.getImage("image/exclamationpoint.png", "excPoint", 80, 80, 1, 1);
	lpImageMng.getImage("image/questionmark.png", "queMark", 80, 80, 1, 1);

	

	_flame = 0;

	return rtnFlag;
}

SceneMng::SceneMng():ScreenSize(1280,720), ScreenCenter(ScreenSize / 2)
{
}

SceneMng::~SceneMng()
{
}
