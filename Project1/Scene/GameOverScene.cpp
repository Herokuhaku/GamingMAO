#include "GameOverScene.h"
#include "../Graphic/ImageMng.h"

GameOverScene::GameOverScene()
{
	_alphaPrm = 0;
	_gameOverMoment = lpSceneMng.GetNum();
	lpImageMng.getImage("image/GameOverChar.png", "gameover_char");
	_gameOverScreen = MakeScreen(lpSceneMng.ScreenSize.x, lpSceneMng.ScreenSize.y, true);

	_control = &GameOverScene::SkipControl;

	_cursor = 0;

	Init();
}
GameOverScene::~GameOverScene()
{
}

std::unique_ptr<BaseScene> GameOverScene::Update(std::unique_ptr<BaseScene> own)
{
	own = (this->*_control)(std::move(own));

	Draw();
	return own;
}

std::unique_ptr<BaseScene> GameOverScene::CursorControl(std::unique_ptr<BaseScene> scene)
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

	if ((lpKeyMng.getBuf()[KEY_INPUT_SPACE] && !lpKeyMng.getOldBuf()[KEY_INPUT_SPACE]) ||
		(lpButtonMng.ButtonTrg(0,XINPUT_BUTTON_B)))
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

std::unique_ptr<BaseScene> GameOverScene::SkipControl(std::unique_ptr<BaseScene> scene)
{
	// スペースキーを押すと暗くなっていくのをスキップできる
	if ((lpKeyMng.getBuf()[KEY_INPUT_SPACE] && !lpKeyMng.getOldBuf()[KEY_INPUT_SPACE]) || 
		(lpButtonMng.ButtonTrg(0, XINPUT_BUTTON_B)))
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
	_strSet.emplace_back(StrData(0, 500, "RESTART", 0x33ff33));

	_strSet.emplace_back(StrData(1, 600, "QUIT", 0xff3333));

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
		for (const auto& data : _strSet)
		{
			int cursor, pos_y, color;
			const TCHAR* str;

			std::tie(cursor, pos_y, str, color) = data;

			if (cursor == _cursor)
			{
				lpStrAdd.AddStringDraw(str, lpSceneMng.ScreenSize.x / 2, pos_y, color, DRAW_TO_CENTER);
			}
			else
			{
				lpStrAdd.AddStringDraw(str, lpSceneMng.ScreenSize.x / 2, pos_y, 0xaaaaaa, DRAW_TO_CENTER);
			}
		}
	}

	SetDrawScreen(tmpScreen);

	lpImageMng.AddBackDraw({ _gameOverScreen, lpSceneMng.ScreenSize.x / 2, lpSceneMng.ScreenSize.y / 2, 1.0, 0.0, LAYER::EX, 1000, DX_BLENDMODE_NOBLEND, 0 });
}
