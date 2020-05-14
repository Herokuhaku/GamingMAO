#pragma once
#include "BaceScene.h"
#include "SceneMng.h"

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

	void Draw(void);
};

