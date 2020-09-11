#include "SignMng.h"
#include "../Graphic/ImageMng.h"
#include "../Graphic/StringAddDraw.h"
#include "../Scene/SceneMng.h"
#include "MapMng.h"
#include "ButtonMng.h"
#include "TimeMng.h"

namespace
{
	constexpr int RANGE = 64;

	constexpr int BOX_OFFSET_X = 200;
	constexpr int BOX_OFFSET_Y = 100;
	constexpr int BOX_SIZE_X = 880;
	constexpr int BOX_SIZE_Y = 400;
}

SignMng & SignMng::GetInstance(void)
{
	static SignMng s;
	return s;
}

void SignMng::Check(void)
{
	if (!_isActive)
	{
		Vector2 pos = lpSceneMng.GetPlObj2(lpTimeMng.getTime())->getPos();
		for (const auto& s : _signs)
		{
			if (pos.x > s->_pos.x - RANGE &&
				pos.x < s->_pos.x + RANGE &&
				pos.y > s->_pos.y &&
				pos.y < s->_pos.y + RANGE)
			{
				lpImageMng.AddDraw({ lpImageMng.getImage("s_up")[0], s->_pos.x, s->_pos.y - 75, 1.5, 0.0, LAYER::BLOCK, 500, DX_BLENDMODE_NOBLEND, 0, true });

				if (lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).first == 2 && lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).second != 2)
				{
					s->_active = true;
					_isActive = true;
				}
			}
		}
	}
	else
	{
		if ((lpButtonMng.Buttonf(0, XINPUT_BUTTON_A).first == 1 && lpButtonMng.Buttonf(0, XINPUT_BUTTON_A).second != 1) ||
			(lpButtonMng.Buttonf(0, XINPUT_BUTTON_B).first == 1 && lpButtonMng.Buttonf(0, XINPUT_BUTTON_B).second != 1) ||
			(lpButtonMng.Buttonf(0, XINPUT_BUTTON_X).first == 1 && lpButtonMng.Buttonf(0, XINPUT_BUTTON_X).second != 1) ||
			(lpButtonMng.Buttonf(0, XINPUT_BUTTON_Y).first == 1 && lpButtonMng.Buttonf(0, XINPUT_BUTTON_Y).second != 1))
		{
			_isActive = false;
			for (auto& s : _signs)
			{
				s->_active = false;
			}
		}
	}
}

void SignMng::Draw(void)
{
	for (auto& s : _signs)
	{
		s->Draw();
	}
}

bool SignMng::IsActive(void)
{
	return _isActive;
}

SignMng::SignMng()
{
	lpImageMng.getImage("image/UI/stickL_up.png", "s_up");
	lpImageMng.getImage("image/Obstacle/sign.png", "sign");

	int ts, tb, tp, screen;
	lpImageMng.GetCurrentScreen(&ts, &tb, &tp);

	// 看板作るとこ
	// スクリーン作る
	screen = MakeScreen(lpSceneMng.ScreenSize.x, lpSceneMng.ScreenSize.y, true);
	SetDrawScreen(screen);
	ClsDrawScreen();

	// スクリーンに描画する
	DrawBox(BOX_OFFSET_X, BOX_OFFSET_Y, BOX_OFFSET_X + BOX_SIZE_X, BOX_OFFSET_Y + BOX_SIZE_Y, 0x333333, true);
	DrawBox(BOX_OFFSET_X, BOX_OFFSET_Y, BOX_OFFSET_X + BOX_SIZE_X, BOX_OFFSET_Y + BOX_SIZE_Y, 0xffffff, false);
	DrawStringToHandle(BOX_OFFSET_X + 30, BOX_OFFSET_Y + 30, " メニューの合成から赤の本と赤の石を合成して", 0xffffff, lpStrAdd.GetFont("TITLE"));
	DrawStringToHandle(BOX_OFFSET_X + 30, BOX_OFFSET_Y + 50, "ダイナマイトを作ろう！", 0xffffff, lpStrAdd.GetFont("TITLE"));

	// 渡す
	_signs.emplace_back(new SignData(Vector2{ 368, 1248 }, 1, screen));

	int KeyTeach = MakeScreen(lpSceneMng.ScreenSize.x, lpSceneMng.ScreenSize.y, true);
	SetDrawScreen(KeyTeach);
	ClsDrawScreen();

	// スクリーンに描画する
	DrawBox(BOX_OFFSET_X, BOX_OFFSET_Y, BOX_OFFSET_X + BOX_SIZE_X, BOX_OFFSET_Y + BOX_SIZE_Y, 0x333333, true);
	DrawBox(BOX_OFFSET_X, BOX_OFFSET_Y, BOX_OFFSET_X + BOX_SIZE_X, BOX_OFFSET_Y + BOX_SIZE_Y, 0xffffff, false);
	DrawStringToHandle(BOX_OFFSET_X + 30, BOX_OFFSET_Y + 30, "本と石を合わせると道具ができる", 0xffffff, lpStrAdd.GetFont("TITLE"));
	DrawStringToHandle(BOX_OFFSET_X + 30, BOX_OFFSET_Y + 50, "石と石で色を混ぜることができるよ！", 0xffffff, lpStrAdd.GetFont("TITLE"));

	// 渡す
	_signs.emplace_back(new SignData(Vector2{ 2496, 1232 }, 4,KeyTeach));

	SetDrawScreen(ts);
	SetDrawBlendMode(tb, tp);
}

void SignData::Draw(void)
{
	if (_stage != lpMapMng.GetnowStage())
	{
		return;
	}

	lpImageMng.AddDraw({ lpImageMng.getImage("sign")[0], _pos.x, _pos.y, 2.0, 0.0, LAYER::BG, 500, DX_BLENDMODE_NOBLEND, 0, true });

	if (_active)
	{
		lpImageMng.AddBackDraw({ _screen, lpSceneMng.ScreenSize.x / 2, lpSceneMng.ScreenSize.y / 2, 1.0, 0.0, LAYER::EX , 100, DX_BLENDMODE_NOBLEND, 0, true });
	}
}
