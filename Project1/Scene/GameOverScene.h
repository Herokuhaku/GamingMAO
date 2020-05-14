#pragma once
#include "BaceScene.h"
#include "SceneMng.h"
#include "../Manage/KeyMng.h"

class GameOverScene :
	public BaceScene
{
public:
	GameOverScene();
	~GameOverScene();

	std::unique_ptr<BaceScene> Update(std::unique_ptr<BaceScene> own) override;
private:
	int _gameOverMoment;
	int _gameOverScreen;

	int _alphaPrm;

	std::unique_ptr<BaceScene> CursorControl(std::unique_ptr<BaceScene> scene);
	std::unique_ptr<BaceScene> SkipControl(std::unique_ptr<BaceScene> scene);
	std::unique_ptr<BaceScene> (GameOverScene::*_control)(std::unique_ptr<BaceScene> scene);

	void Draw(void);
};

