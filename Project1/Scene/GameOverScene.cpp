#include "GameOverScene.h"

GameOverScene::GameOverScene()
{
	_alphaPrm = 0;
	_gameOverMoment = lpSceneMng.GetNum();
	lpImageMng.getImage("image/GameOverChar.png", "gameover_char");
	_gameOverScreen = MakeScreen(lpSceneMng.ScreenSize.x, lpSceneMng.ScreenSize.y, 0);
}
GameOverScene::~GameOverScene()
{
}

std::unique_ptr<BaceScene> GameOverScene::Update(std::unique_ptr<BaceScene> own)
{
	Draw();
	return own;
}

void GameOverScene::Draw(void)
{
	_alphaPrm++;

	if (_alphaPrm < 120)
	{
		int tmpScreen = GetDrawScreen();

		SetDrawScreen(_gameOverScreen);
		ClsDrawScreen();

		DrawGraph(0, 0, _gameOverMoment, true);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alphaPrm);
		DrawBox(0, 0, lpSceneMng.ScreenSize.x, lpSceneMng.ScreenSize.y, 0x000000, true);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alphaPrm * 2);
		DrawRotaGraph(lpSceneMng.ScreenSize.x / 2, 300, 1.0, 0.0, lpImageMng.getImage("gameover_char")[0], true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		SetDrawScreen(tmpScreen);
	}
	else
	{

	}

	lpImageMng.AddBackDraw({ _gameOverScreen, lpSceneMng.ScreenSize.x / 2, lpSceneMng.ScreenSize.y / 2, 0.0, LAYER::EX, INT_MAX - 20 });
}
