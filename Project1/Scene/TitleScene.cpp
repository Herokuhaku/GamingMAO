#include "TitleScene.h"
#include <ctime>
#include "../Graphic/ImageMng.h"
#include "../Graphic/StringAddDraw.h"
#include "SceneMng.h"
#include "SeleScene.h"
#include "SceneMng.h"
#include "../Manage/ButtonMng.h"
#include "../Manage/KeyMng.h"

namespace
{
	constexpr int FADE_INTERVAL = 45;	// フェードにかける時間
	constexpr int REVERSE_INTERVAL = 120; // 時戻しにかける時間
	constexpr int BLINK_INTERVAL_NORMAL = 30;	// 点滅の間隔
	constexpr int BLINK_INTERVAL_FAST = 5;
	int _blinkTimer;	// 点滅用タイマー
	int _timer;		// タイマー

	float _degreeSpeed;
	float _minDegree;
	float _hourDegree;

	constexpr int CLOCK_POSITION_Y = 320;

	int _titleScreen;	// 描画用スクリーン
}

// 現在時間
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
	lpImageMng.getImage("image/hurosiki.png", "風呂敷");
	lpImageMng.getImage("image/Title/tokei.png", "時計", 128, 128, 3, 1);

	_update = &TitleScene::FadeInUpdate;
	_draw = &TitleScene::FadeInDraw;

	_blinkTimer = 0;
	_timer = FADE_INTERVAL;
	_degreeSpeed = 0;


	_titleScreen = MakeScreen(lpSceneMng.ScreenSize.x, lpSceneMng.ScreenSize.y, true);
}

TitleScene::~TitleScene()
{
}

std::unique_ptr<BaseScene> TitleScene::Update(std::unique_ptr<BaseScene> own)
{
	//lpImageMng.AddBackDraw({ lpImageMng.getImage("風呂敷")[0], lpSceneMng.ScreenSize.x / 2, lpSceneMng.ScreenSize.y / 2, 1.0, 0.0, LAYER::BG, 0, DX_BLENDMODE_NOBLEND, 0 });

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
	}
	return nullptr;
}

BaseScene* TitleScene::NormalUpdate(void)
{
	_blinkTimer++;
	if (lpButtonMng.ButtonTrg(0, XINPUT_BUTTON_B))
	{
		_update = &TitleScene::ReverseUpdate;
		_draw = &TitleScene::ReverseDraw;
		_timer = REVERSE_INTERVAL;
		_blinkTimer = 0;
		_minDegree = realtime::GetDegFromMinute();
		_hourDegree = realtime::GetDegFromHour();
	}
	return nullptr;
}

BaseScene* TitleScene::ReverseUpdate(void)
{
	_timer--;
	_blinkTimer++;
	_degreeSpeed += 0.5;
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
		return new SeleScene();
	}
	return nullptr;
}

void TitleScene::FadeInDraw(void)
{
	Vector2Template<int> screen = lpSceneMng.ScreenSize;
	DrawGraph(0, 0, lpImageMng.getImage("風呂敷")[0], true);
	DrawClock();
	SetDrawBlendMode(DX_BLENDMODE_SUB, static_cast<int>(255.0f * (static_cast<float>(_timer) / static_cast<float>(FADE_INTERVAL))));
	DrawBox(0, 0, screen.x, screen.y, 0xffffff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	GraphFilter(_titleScreen, DX_GRAPH_FILTER_HSB, 0, 0, -255, 0);
}

void TitleScene::NormalDraw(void)
{
	Vector2Template<int> screen = lpSceneMng.ScreenSize;
	DrawGraph(0, 0, lpImageMng.getImage("風呂敷")[0], true);
	DrawClock();
	if (_blinkTimer / BLINK_INTERVAL_NORMAL % 2 == 1)
	{
		lpStrAdd.AddStringDraw("P R E S S 'B'", "TITLE", lpSceneMng.ScreenSize.x / 2, lpSceneMng.ScreenSize.y * 4 / 5, 0xffffff, DRAW_TO_CENTER);
	}
	GraphFilter(_titleScreen, DX_GRAPH_FILTER_HSB, 0, 0, -255, 0);
}

void TitleScene::ReverseDraw(void)
{
	Vector2Template<int> screen = lpSceneMng.ScreenSize;
	DrawGraph(0, 0, lpImageMng.getImage("風呂敷")[0], true);
	DrawReverseClock();
	if (_blinkTimer / BLINK_INTERVAL_FAST % 2 == 1)
	{
		lpStrAdd.AddStringDraw("P R E S S 'B'", "TITLE", lpSceneMng.ScreenSize.x / 2, lpSceneMng.ScreenSize.y * 4 / 5, 0xffffff, DRAW_TO_CENTER);
	}
	GraphFilter(_titleScreen, DX_GRAPH_FILTER_HSB, 0, 0, static_cast<int>(-255.0f * (static_cast<float>(_timer) / static_cast<float>(REVERSE_INTERVAL))), 0);
}

void TitleScene::FadeOutDraw(void)
{
	Vector2Template<int> screen = lpSceneMng.ScreenSize;
	DrawGraph(0, 0, lpImageMng.getImage("風呂敷")[0], true);
	DrawReverseClock();
	SetDrawBlendMode(DX_BLENDMODE_SUB, static_cast<int>(255.0f * (1.0f - static_cast<float>(_timer) / static_cast<float>(FADE_INTERVAL))));
	DrawBox(0, 0, lpSceneMng.ScreenSize.x, lpSceneMng.ScreenSize.y, 0xffffff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void TitleScene::DrawClock(void)
{
	Vector2Template<int> screen = lpSceneMng.ScreenSize;
	DrawRotaGraph(screen.x / 2, CLOCK_POSITION_Y, 2.0, 0.0, lpImageMng.getImage("時計")[0], true);
	DrawRotaGraph(screen.x / 2, CLOCK_POSITION_Y, 2.0, realtime::GetRadFromMinute(), lpImageMng.getImage("時計")[1], true);
	DrawRotaGraph(screen.x / 2, CLOCK_POSITION_Y, 2.0, realtime::GetRadFromHour(), lpImageMng.getImage("時計")[2], true);
}

void TitleScene::DrawReverseClock(void)
{
	_minDegree = fmodf(_minDegree - _degreeSpeed, 360.0f);
	_hourDegree = fmodf(_hourDegree - _degreeSpeed, 360.0f);
	Vector2Template<int> screen = lpSceneMng.ScreenSize;
	DrawRotaGraph(screen.x / 2, CLOCK_POSITION_Y, 2.0, 0.0, lpImageMng.getImage("時計")[0], true);
	DrawRotaGraph(screen.x / 2, CLOCK_POSITION_Y, 2.0, (_minDegree - 180.0f) / 180.0f * acos(-1.0), lpImageMng.getImage("時計")[1], true);
	DrawRotaGraph(screen.x / 2, CLOCK_POSITION_Y, 2.0, (_hourDegree - 180.0f) / 180.0f * acos(-1.0), lpImageMng.getImage("時計")[2], true);
}
