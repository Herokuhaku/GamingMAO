#pragma once
#include "../Graphic/StringAddDraw.h"
#include "BaceScene.h"
#include "SceneMng.h"
#include "../Manage/KeyMng.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "../Manage/ButtonMng.h"

using StrData = std::tuple<int, int, const TCHAR*, int>;	// カーソル番号、y座標、文字列、色

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

	std::vector<StrData> _strSet;

	int _cursor;
	static constexpr int CURSOR_MAX = 1;

	std::unique_ptr<BaceScene> CursorControl(std::unique_ptr<BaceScene> scene);
	std::unique_ptr<BaceScene> SkipControl(std::unique_ptr<BaceScene> scene);
	std::unique_ptr<BaceScene> (GameOverScene::*_control)(std::unique_ptr<BaceScene> scene);

	bool Init(void);

	void Draw(void);
};

