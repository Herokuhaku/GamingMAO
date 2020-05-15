#include "GameOverScene.h"

GameOverScene::GameOverScene()
{
	_alphaPrm = 0;
	_gameOverMoment = lpSceneMng.GetNum();
	lpImageMng.getImage("image/GameOverChar.png", "gameover_char");
	_gameOverScreen = MakeScreen(lpSceneMng.ScreenSize.x, lpSceneMng.ScreenSize.y, 0);

	_control = &GameOverScene::SkipControl;

	_cursor = 0;

	Init();
}
GameOverScene::~GameOverScene()
{
}

std::unique_ptr<BaceScene> GameOverScene::Update(std::unique_ptr<BaceScene> own)
{
	own = (this->*_control)(std::move(own));

	Draw();
	return own;
}

std::unique_ptr<BaceScene> GameOverScene::CursorControl(std::unique_ptr<BaceScene> scene)
{
	if (lpKeyMng.getBuf()[KEY_INPUT_UP] && !lpKeyMng.getOldBuf()[KEY_INPUT_UP])
	{
		_cursor--;
		if (_cursor < 0)
		{
			_cursor = CURSOR_MAX;
		}
	}
	else if (lpKeyMng.getBuf()[KEY_INPUT_DOWN] && !lpKeyMng.getOldBuf()[KEY_INPUT_DOWN])
	{
		_cursor++;
		if (_cursor > CURSOR_MAX)
		{
			_cursor = 0;
		}
	}

	if (lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).first == 2 && lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).second == 0)
	{
		_cursor--;
		if (_cursor < 0)
		{
			_cursor = CURSOR_MAX;
		}
	}
	else if (lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).first == 1 && lpButtonMng.Thumbf(0,XINPUT_THUMBL_Y).second == 0)
	{
		_cursor++;
		if (_cursor > CURSOR_MAX)
		{
			_cursor = 0;
		}
	}

	if (lpKeyMng.getBuf()[KEY_INPUT_SPACE] && !lpKeyMng.getOldBuf()[KEY_INPUT_SPACE])
	{
		switch (_cursor)
		{
		case 0:
			scene = std::make_unique<GameScene>();
			break;
		case 1:
			scene = std::make_unique<TitleScene>();
			break;
		default:
			break;
		}
	}

	return std::move(scene);
}

std::unique_ptr<BaceScene> GameOverScene::SkipControl(std::unique_ptr<BaceScene> scene)
{
	// スペースキーを押すと暗くなっていくのをスキップできる
	if (lpKeyMng.getBuf()[KEY_INPUT_SPACE] && !lpKeyMng.getOldBuf()[KEY_INPUT_SPACE])
	{
		_alphaPrm = 118;
		_control = &GameOverScene::CursorControl;
	}

	if (_alphaPrm >= 120)
	{
		_control = &GameOverScene::CursorControl;
	}

	return scene;
}

bool GameOverScene::Init(void)
{
	int strLen;
	int strWidth;

	strLen = strlen("RESTART");
	strWidth = GetDrawStringWidthToHandle("RESTART", strLen, lpSceneMng.GetFont());
	_strSet.emplace_back(StrData(0, strWidth, 500, "RESTART", 0x33ff33));

	strLen = strlen("QUIT");
	strWidth = GetDrawStringWidthToHandle("QUIT", strLen, lpSceneMng.GetFont());
	_strSet.emplace_back(StrData(1, strWidth, 600, "QUIT", 0xff3333));

	return true;
}

void GameOverScene::Draw(void)
{
	int tmpScreen = GetDrawScreen();

	_alphaPrm++;

	if (_alphaPrm < 120)
	{
		SetDrawScreen(_gameOverScreen);
		ClsDrawScreen();

		DrawGraph(0, 0, _gameOverMoment, true);

		// 段々暗く
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alphaPrm);
		DrawBox(0, 0, lpSceneMng.ScreenSize.x, lpSceneMng.ScreenSize.y, 0x000000, true);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alphaPrm * 2);
		DrawRotaGraph(lpSceneMng.ScreenSize.x / 2, 200, 1.0, 0.0, lpImageMng.getImage("gameover_char")[0], true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else
	{
		SetDrawScreen(_gameOverMoment);
		ClsDrawScreen();

		for (auto data : _strSet)
		{
			int cursor, width, pos_y, color;
			const TCHAR* str;

			std::tie(cursor, width, pos_y, str, color) = data;

			if (cursor == _cursor)
			{
				DrawStringToHandle((lpSceneMng.ScreenSize.x - width) / 2, pos_y, str, color, lpSceneMng.GetFont());
			}
			else
			{
				DrawStringToHandle((lpSceneMng.ScreenSize.x - width) / 2, pos_y, str, 0xaaaaaa, lpSceneMng.GetFont());
			}
		}

		lpImageMng.AddBackDraw({ _gameOverMoment, lpSceneMng.ScreenSize.x / 2, lpSceneMng.ScreenSize.y / 2, 0.0, LAYER::EX, INT_MAX - 15 });
	}

	SetDrawScreen(tmpScreen);

	lpImageMng.AddBackDraw({ _gameOverScreen, lpSceneMng.ScreenSize.x / 2, lpSceneMng.ScreenSize.y / 2, 0.0, LAYER::EX, INT_MAX - 20 });
}
