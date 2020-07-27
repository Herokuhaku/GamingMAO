#include "TitleScene.h"
#include <ctime>
#include "../Graphic/ImageMng.h"
#include "../Graphic/StringAddDraw.h"
#include "SceneMng.h"
#include "SeleScene.h"
#include "SceneMng.h"
#include "../Manage/ButtonMng.h"
#include "../Manage/KeyMng.h"
#include "AnimatedScene/OpeningAnimationScene.h"
#include "GameScene.h"
#include "../Audio/AudioContainer.h"

namespace
{
	AudioContainer _audio;

	constexpr int FADE_INTERVAL = 45;	// ÉtÉFÅ[ÉhÇ…Ç©ÇØÇÈéûä‘
	constexpr int NORMAL_INTERVAL = 30;
	constexpr int REVERSE_INTERVAL = 120; // éûñﬂÇµÇ…Ç©ÇØÇÈéûä‘
	constexpr int BLINK_INTERVAL_NORMAL = 30;	// ì_ñ≈ÇÃä‘äu
	constexpr int BLINK_INTERVAL_FAST = 5;
	int _blinkTimer;	// ì_ñ≈ópÉ^ÉCÉ}Å[
	int _blinkInterval;
	int _timer;		// É^ÉCÉ}Å[

	float _degreeSpeed;
	float _minDegree;
	float _hourDegree;

	constexpr int CLOCK_POSITION_Y = 320;

	int _titleScreen;	// ï`âÊópÉXÉNÉäÅ[Éì
}

// åªç›éûä‘
namespace realtime
{
	constexpr int MIN_ANGLE = 360 / 60;
	constexpr int HOUR_ANGLE = 360 / 12;

	double GetRadFromMinute(void)
	{
		time_t now = time(NULL);
		tm time;
		localtime_s(&time, &now);
		return static_cast<double>(time.tm_min * MIN_ANGLE) / 180.0 * acos(-1.0) - acos(-1.0);
	}
	double GetRadFromHour(void)
	{
		time_t now = time(NULL);
		tm time;
		localtime_s(&time, &now);
		return static_cast<double>(time.tm_hour * HOUR_ANGLE) / 180.0 * acos(-1.0) + static_cast<double>(time.tm_min / 2) / 180.0 * acos(-1.0) - acos(-1.0);
	}
	float GetDegFromMinute(void)
	{
		time_t now = time(NULL);
		tm time;
		localtime_s(&time, &now);
		return static_cast<float>(time.tm_min * MIN_ANGLE);
	}
	float GetDegFromHour(void)
	{
		time_t now = time(NULL);
		tm time;
		localtime_s(&time, &now);
		return static_cast<float>(time.tm_hour * HOUR_ANGLE + time.tm_min / 2);
	}
};

TitleScene::TitleScene()
{
	lpImageMng.getImage("image/hurosiki.png", "ïóòCï~");
	lpImageMng.getImage("image/Title/tokei.png", "éûåv", 128, 128, 3, 1);
	lpImageMng.getImage("image/Title/cursor.png", "cursor");

	_update = &TitleScene::FadeInUpdate;
	_draw = &TitleScene::FadeInDraw;

	_blinkTimer = 0;
	_blinkInterval = BLINK_INTERVAL_NORMAL;
	_timer = FADE_INTERVAL;
	_degreeSpeed = 0;
	_cursor = 0;
	
	Vector2Template<int> pos;
	pos = { lpSceneMng.ScreenSize.x / 2, 525 };
	_menu.emplace_back("ÇÕÇ∂ÇﬂÇ©ÇÁ", pos, []() { return new GameScene(); });
	pos = { lpSceneMng.ScreenSize.x / 2, 575 };
	_menu.emplace_back("Ç¬Ç√Ç´Ç©ÇÁ", pos, []() { return new GameScene(); });

	_titleScreen = MakeScreen(lpSceneMng.ScreenSize.x, lpSceneMng.ScreenSize.y, true);

	_audio.LoadSound("sound/system/cursor_move.wav", "move", 5);
	_audio.LoadSound("sound/system/cursor_select.wav", "select", 3);
	_audio.LoadSound("sound/system/cancel.wav", "cancel", 3);
	_audio.ChangeVolume("move", 180);
	_audio.ChangeVolume("select", 210);
	_audio.ChangeVolume("cancel", 180);
}

TitleScene::~TitleScene()
{
}

std::unique_ptr<BaseScene> TitleScene::Update(std::unique_ptr<BaseScene> own)
{
	//lpImageMng.AddBackDraw({ lpImageMng.getImage("ïóòCï~")[0], lpSceneMng.ScreenSize.x / 2, lpSceneMng.ScreenSize.y / 2, 1.0, 0.0, LAYER::BG, 0, DX_BLENDMODE_NOBLEND, 0 });

	//if ((lpKeyMng.getBuf()[KEY_INPUT_RETURN] && !lpKeyMng.getOldBuf()[KEY_INPUT_RETURN]) ||
	//	lpButtonMng.ButtonTrg(0, XINPUT_BUTTON_B))
	//{
	//	lpImageMng.setGkind(ScrEff::FADEOUT);
	//	return std::make_unique<SeleScene>();
	//}

	BaseScene* scene = (this->*_update)();
	if (scene != nullptr)
	{
		return std::unique_ptr<BaseScene>(scene);
	}

	int tmpScreen = GetDrawScreen();
	int tmpBlend, tmpParam;
	GetDrawBlendMode(&tmpBlend, &tmpParam);
	SetDrawScreen(_titleScreen);
	ClsDrawScreen();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	(this->*_draw)();
	lpImageMng.AddBackDraw({ _titleScreen, lpSceneMng.ScreenSize.x / 2, lpSceneMng.ScreenSize.y / 2, 1.0, 0.0, LAYER::BG, 0, DX_BLENDMODE_NOBLEND, 0 });
	
	SetDrawScreen(tmpScreen);
	SetDrawBlendMode(tmpBlend, tmpParam);

	return std::move(own);
}

BaseScene* TitleScene::FadeInUpdate(void)
{
	_timer--;
	if (_timer < 0 || lpButtonMng.ButtonTrg(0, XINPUT_BUTTON_B))
	{
		_update = &TitleScene::NormalUpdate;
		_draw = &TitleScene::NormalDraw;
		_timer = -1;
	}
	return nullptr;
}

BaseScene* TitleScene::NormalUpdate(void)
{
	_blinkTimer++;
	if (lpButtonMng.ButtonTrg(0, XINPUT_BUTTON_B))
	{
		PlaySoundMem(_audio.GetSound("select"), DX_PLAYTYPE_BACK, true);
		_timer = NORMAL_INTERVAL;
		_blinkInterval = BLINK_INTERVAL_FAST;
	}
	if (_timer >= 0)
	{
		_timer--;
		if (_timer < 0)
		{
			_update = &TitleScene::SelectUpdate;
			_draw = &TitleScene::SelectDraw;
			_blinkInterval = BLINK_INTERVAL_NORMAL;
			_blinkTimer = 0;
		}
	}
	return nullptr;
}

BaseScene * TitleScene::SelectUpdate(void)
{
	_blinkTimer++;
	if (lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).first == 2 && lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).second != 2)
	{
		PlaySoundMem(_audio.GetSound("move"), DX_PLAYTYPE_BACK, true);
		_cursor = (_menu.size() + _cursor - 1) % _menu.size();
		_blinkTimer = 0;
	}
	if (lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).first == 1 && lpButtonMng.Thumbf(0, XINPUT_THUMBL_Y).second != 1)
	{
		PlaySoundMem(_audio.GetSound("move"), DX_PLAYTYPE_BACK, true);
		_cursor = (_cursor + 1) % _menu.size();
		_blinkTimer = 0;
	}

	if (lpButtonMng.ButtonTrg(0, XINPUT_BUTTON_B))
	{
		PlaySoundMem(_audio.GetSound("select"), DX_PLAYTYPE_BACK, true);
		_update = &TitleScene::ReverseUpdate;
		_draw = &TitleScene::ReverseDraw;
		_timer = REVERSE_INTERVAL;
		_blinkInterval = BLINK_INTERVAL_FAST;
		_minDegree = realtime::GetDegFromMinute();
		_hourDegree = realtime::GetDegFromHour();
	}
	return nullptr;
}

BaseScene* TitleScene::ReverseUpdate(void)
{
	_timer--;
	_blinkTimer++;
	_degreeSpeed += 2.3f;
	if (_timer < 0)
	{
		_update = &TitleScene::FadeOutUpdate;
		_draw = &TitleScene::FadeOutDraw;
		_timer = FADE_INTERVAL;
	}
	return nullptr;
}

BaseScene* TitleScene::FadeOutUpdate(void)
{
	_timer--;
	_blinkTimer++;
	if (_timer < 0)
	{
		return _menu[_cursor]._func();
	}
	return nullptr;
}

void TitleScene::FadeInDraw(void)
{
	Vector2Template<int> screen = lpSceneMng.ScreenSize;
	DrawGraph(0, 0, lpImageMng.getImage("ïóòCï~")[0], true);
	DrawClock();
	SetDrawBlendMode(DX_BLENDMODE_SUB, static_cast<int>(255.0f * (static_cast<float>(_timer) / static_cast<float>(FADE_INTERVAL))));
	DrawBox(0, 0, screen.x, screen.y, 0xffffff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	GraphFilter(_titleScreen, DX_GRAPH_FILTER_HSB, 0, 0, -255, 0);
}

void TitleScene::NormalDraw(void)
{
	Vector2Template<int> screen = lpSceneMng.ScreenSize;
	DrawGraph(0, 0, lpImageMng.getImage("ïóòCï~")[0], true);
	DrawClock();
	if (_blinkTimer / _blinkInterval % 2 == 1)
	{
		lpStrAdd.AddStringDraw("P R E S S 'B'", "TITLE", lpSceneMng.ScreenSize.x / 2, lpSceneMng.ScreenSize.y * 4 / 5, 0xffffff, DRAW_TO_CENTER);
	}
	GraphFilter(_titleScreen, DX_GRAPH_FILTER_HSB, 0, 0, -255, 0);
}

void TitleScene::SelectDraw(void)
{
	Vector2Template<int> screen = lpSceneMng.ScreenSize;
	DrawGraph(0, 0, lpImageMng.getImage("ïóòCï~")[0], true);
	DrawClock();
	
	unsigned int color = 0xffffff;
	for (int i = 0 ; i < _menu.size(); i++)
	{
		if (i == _cursor)
		{
			DrawRotaGraph(_menu[i]._pos.x - 100, _menu[i]._pos.y + 16, 1.0, 0.0, lpImageMng.getImage("cursor")[0], true);
		}
		lpStrAdd.AddStringDraw(_menu[i]._text.c_str(), "TITLE", _menu[i]._pos.x, _menu[i]._pos.y, color, DRAW_TO_CENTER);
	}

	GraphFilter(_titleScreen, DX_GRAPH_FILTER_HSB, 0, 0, -255, 0);
}

void TitleScene::ReverseDraw(void)
{
	Vector2Template<int> screen = lpSceneMng.ScreenSize;
	DrawGraph(0, 0, lpImageMng.getImage("ïóòCï~")[0], true);
	DrawReverseClock();

	unsigned int color = 0xffffff;
	for (int i = 0; i < _menu.size(); i++)
	{
		if (i == _cursor)
		{
			if (_blinkTimer / _blinkInterval % 2 == 1)
			{
				lpStrAdd.AddStringDraw(_menu[i]._text.c_str(), "TITLE", _menu[i]._pos.x, _menu[i]._pos.y, color, DRAW_TO_CENTER);
			}
		}
		else
		{
			lpStrAdd.AddStringDraw(_menu[i]._text.c_str(), "TITLE", _menu[i]._pos.x, _menu[i]._pos.y, color, DRAW_TO_CENTER);
		}
	}
	GraphFilter(_titleScreen, DX_GRAPH_FILTER_HSB, 0, 0, static_cast<int>(-255.0f * (static_cast<float>(_timer) / static_cast<float>(REVERSE_INTERVAL))), 0);
}

void TitleScene::FadeOutDraw(void)
{
	Vector2Template<int> screen = lpSceneMng.ScreenSize;
	DrawGraph(0, 0, lpImageMng.getImage("ïóòCï~")[0], true);
	DrawReverseClock();
	SetDrawBlendMode(DX_BLENDMODE_SUB, static_cast<int>(255.0f * (1.0f - static_cast<float>(_timer) / static_cast<float>(FADE_INTERVAL))));
	DrawBox(0, 0, lpSceneMng.ScreenSize.x, lpSceneMng.ScreenSize.y, 0xffffff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void TitleScene::DrawClock(void)
{
	Vector2Template<int> screen = lpSceneMng.ScreenSize;
	DrawRotaGraph(screen.x / 2, CLOCK_POSITION_Y, 2.0, 0.0, lpImageMng.getImage("éûåv")[0], true);
	DrawRotaGraph(screen.x / 2, CLOCK_POSITION_Y, 2.0, realtime::GetRadFromMinute(), lpImageMng.getImage("éûåv")[1], true);
	DrawRotaGraph(screen.x / 2, CLOCK_POSITION_Y, 2.0, realtime::GetRadFromHour(), lpImageMng.getImage("éûåv")[2], true);
}

void TitleScene::DrawReverseClock(void)
{
	_minDegree = fmodf(_minDegree - _degreeSpeed, 360.0f);
	_hourDegree = fmodf(_hourDegree - _degreeSpeed / 12.0f, 360.0f);
	Vector2Template<int> screen = lpSceneMng.ScreenSize;
	DrawRotaGraph(screen.x / 2, CLOCK_POSITION_Y, 2.0, 0.0, lpImageMng.getImage("éûåv")[0], true);
	DrawRotaGraph(screen.x / 2, CLOCK_POSITION_Y, 2.0, (_minDegree - 180.0f) / 180.0f * acos(-1.0), lpImageMng.getImage("éûåv")[1], true);
	DrawRotaGraph(screen.x / 2, CLOCK_POSITION_Y, 2.0, (_hourDegree - 180.0f) / 180.0f * acos(-1.0), lpImageMng.getImage("éûåv")[2], true);
}
