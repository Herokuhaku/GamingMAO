#include "TitleScene.h"
#include "../Graphic/ImageMng.h"
#include "../Graphic/StringAddDraw.h"
#include "SceneMng.h"
#include "SeleScene.h"
#include "SceneMng.h"
#include "../Manage/ButtonMng.h"
#include "../Manage/KeyMng.h"

namespace
{
	constexpr int FADE_INTERVAL = 45;	// ÉtÉFÅ[ÉhÇ…Ç©ÇØÇÈéûä‘
	constexpr int REVERSE_INTERVAL = 45; // éûñﬂÇµÇ…Ç©ÇØÇÈéûä‘
	constexpr int BLINK_INTERVAL_NORMAL = 30;	// ì_ñ≈ÇÃä‘äu
	constexpr int BLINK_INTERVAL_FAST = 5;
	int _blinkTimer;	// ì_ñ≈ópÉ^ÉCÉ}Å[
	int _timer;		// É^ÉCÉ}Å[
	

	int _titleScreen;	// ï`âÊópÉXÉNÉäÅ[Éì
}

TitleScene::TitleScene()
{
	lpImageMng.getImage("image/hurosiki.png", "ïóòCï~");

	_update = &TitleScene::FadeInUpdate;
	_draw = &TitleScene::FadeInDraw;

	_blinkTimer = 0;
	_timer = FADE_INTERVAL;

	_titleScreen = MakeScreen(lpSceneMng.ScreenSize.x, lpSceneMng.ScreenSize.y, true);
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
	}
	return nullptr;
}

BaseScene* TitleScene::ReverseUpdate(void)
{
	_timer--;
	_blinkTimer++;
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
	DrawGraph(0, 0, lpImageMng.getImage("ïóòCï~")[0], true);
	SetDrawBlendMode(DX_BLENDMODE_SUB, static_cast<int>(255.0f * (static_cast<float>(_timer) / static_cast<float>(FADE_INTERVAL))));
	DrawBox(0, 0, lpSceneMng.ScreenSize.x, lpSceneMng.ScreenSize.y, 0xffffff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void TitleScene::NormalDraw(void)
{
	DrawGraph(0, 0, lpImageMng.getImage("ïóòCï~")[0], true);
	if (_blinkTimer / BLINK_INTERVAL_NORMAL % 2 == 1)
	{
		lpStrAdd.AddStringDraw("P R E S S 'B'", "TITLE", lpSceneMng.ScreenSize.x / 2, lpSceneMng.ScreenSize.y * 4 / 5, 0xffffff, DRAW_TO_CENTER);
	}
}

void TitleScene::ReverseDraw(void)
{
	DrawGraph(0, 0, lpImageMng.getImage("ïóòCï~")[0], true);
	if (_blinkTimer / BLINK_INTERVAL_FAST % 2 == 1)
	{
		lpStrAdd.AddStringDraw("P R E S S 'B'", "TITLE", lpSceneMng.ScreenSize.x / 2, lpSceneMng.ScreenSize.y * 4 / 5, 0xffffff, DRAW_TO_CENTER);
	}
}

void TitleScene::FadeOutDraw(void)
{
	DrawGraph(0, 0, lpImageMng.getImage("ïóòCï~")[0], true);
	SetDrawBlendMode(DX_BLENDMODE_SUB, static_cast<int>(255.0f * (1.0f - static_cast<float>(_timer) / static_cast<float>(FADE_INTERVAL))));
	DrawBox(0, 0, lpSceneMng.ScreenSize.x, lpSceneMng.ScreenSize.y, 0xffffff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
