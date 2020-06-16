#pragma once
#include <memory>
#include "../Graphic/StringAddDraw.h"
#include "BaseScene.h"
#include "SceneMng.h"
#include "../Manage/KeyMng.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "../Manage/ButtonMng.h"

using StrData = std::tuple<int, int, const TCHAR*, int>;	// カーソル番号、y座標、文字列、色

class GameOverScene :
	public BaseScene
{
public:
	GameOverScene();
	~GameOverScene();

	std::unique_ptr<BaseScene> Update(std::unique_ptr<BaseScene> own) override;
private:
	int _gameOverMoment;
	int _gameOverScreen;

	int _alphaPrm;

	std::vector<StrData> _strSet;

	int _cursor;
	static constexpr int CURSOR_MAX = 1;

	std::unique_ptr<BaseScene> CursorControl(std::unique_ptr<BaseScene> scene);
	std::unique_ptr<BaseScene> SkipControl(std::unique_ptr<BaseScene> scene);
	std::unique_ptr<BaseScene> (GameOverScene::*_control)(std::unique_ptr<BaseScene> scene);

	bool Init(void);

	void Draw(void);
};

