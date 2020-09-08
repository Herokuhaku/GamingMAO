#include "OpeningAnimationScene.h"
#include <DxLib.h>
#include "../SceneMng.h"
#include "../../Graphic/ImageMng.h"

namespace
{
	int _timer;

	int _castleImage;
	Vector2Template<int> _castlePos;
	float _castleExRate = 3.0f;
	int _anmScreen;

	Vector2Template<int> _demonPos;
	float _demonExRate = 3.5f;
	constexpr int SCENE1_DEMON_POS_BASE = 600;
}

OpeningAnimationScene::OpeningAnimationScene()
{
	_timer = 0;
	_update = &OpeningAnimationScene::Update1;
	_draw = &OpeningAnimationScene::Draw1;

	_castlePos = { 0, 380 };
	_demonPos = { 300,SCENE1_DEMON_POS_BASE };

	_anmScreen = MakeScreen(lpSceneMng.ScreenSize.x, lpSceneMng.ScreenSize.y, true);
	_castleImage = LoadGraph("image/AnimationScene/castle.png", true);

	lpImageMng.getImage("image/Enemy/demon-idle.png", "demon_idle", 160, 144, 6, 1);
}

OpeningAnimationScene::~OpeningAnimationScene()
{
	DeleteGraph(_anmScreen);
	DeleteGraph(_castleImage);
}

std::unique_ptr<BaseScene> OpeningAnimationScene::Update(std::unique_ptr<BaseScene> own)
{
	(this->*_update)();

	int screen, blend, param;
	GetDrawBlendMode(&blend, &param);
	screen = GetDrawScreen();
	SetDrawScreen(_anmScreen);
	ClsDrawScreen();
	(this->*_draw)();
	lpImageMng.AddBackDraw({ _anmScreen, lpSceneMng.ScreenSize.x / 2, lpSceneMng.ScreenSize.y / 2, 1.0, 0.0, LAYER::BG, 0, DX_BLENDMODE_NOBLEND, 0, true });

	SetDrawScreen(screen);
	SetDrawBlendMode(blend, param);

	return own;
}

void OpeningAnimationScene::Update1(void)
{
	_timer++;
	if (_timer % 2 == 0)
	{
		_castlePos.x++;
	}
	_demonPos.y = SCENE1_DEMON_POS_BASE - abs((_timer / 3 + 8) % 16 - 8);
}

void OpeningAnimationScene::Draw1(void)
{
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	Vector2Template<int> sc = lpSceneMng.ScreenSize;
	DrawRectExtendGraph(0, 0, sc.x, sc.y, _castlePos.x, _castlePos.y, static_cast<int>(sc.x / _castleExRate), static_cast<int>(sc.y / _castleExRate), _castleImage, true);
	DrawRotaGraph(_demonPos.x, _demonPos.y, _demonExRate, 0.0, lpImageMng.getImage("demon_idle")[4], true, true, false);
}
