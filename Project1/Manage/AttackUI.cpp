#include "AttackUI.h"
#include "ButtonMng.h"
#include "../Graphic/ImageMng.h"
#include "ItemTrader.h"
#include "Menu.h"
#include "TimeMng.h"
#include "../Scene/SceneMng.h"
#include "../Object/Player.h"
#include "../Object/Attack/white/StopTime.h"

AttackUI* AttackUI::sInstance = nullptr;

namespace
{
	constexpr int Z_ORDER = 500;
	constexpr int UI_SIZE = 300;
	constexpr int RING_SIZE = 230;
	constexpr int RING_RADIUS = 102;
	constexpr int STICK_OBJ_SIZE = 60;
	constexpr int EFFECT_ANM_COUNT = 10;
	constexpr int EFFECT_ANM_INTERVAL = 3;
	constexpr double EFFECT_EX_RATE_STICK = 1.0;
	constexpr double EFFECT_EX_RATE_RUN = 5.0;

	constexpr int DRAW_OFFSET_X = 1150;
	constexpr int DRAW_OFFSET_Y = 600;

	constexpr int ACTIVE_RADIUS = 400000000;
	constexpr double STICK_RADIUS = 0x8000;

	constexpr float MP_MAX = 100.0f;
	constexpr float MP_REGENERATION_SPEED = 0.1f;

	constexpr int FEVER_DURATION = 400;
	constexpr float FEVER_MP_DEC = MP_MAX / static_cast<float>(FEVER_DURATION);
}

void AttackUI::Update(void)
{
	// 現在の色を保存
	_OldAttackColor = _AttackColor;

	if (lpTimeMng.getTime() == TIME::FTR && _active)
	{
		// 現在の右スティックの情報の取得
		lpButtonMng.GetThumb(THUMB_RIGHT, _stickX, _stickY);
	}
	else
	{
		_stickX = 0;
		_stickY = 0;
	}

	MpUpdate();
	//StickTrans();

	_absStickX = static_cast<int>(STICK_TO_POS(_stickX) + DRAW_OFFSET_X);
	_absStickY = static_cast<int>(STICK_TO_POS(-_stickY) + DRAW_OFFSET_Y);

	if (_coolTime != 0)
	{
		_coolTime--;
	}
	if (_feverTime != 0)
	{
		_feverTime--;
	}
	if (_coolTime == 0)
	{
		StateUpdate();
		ColorUpdate();
	}
}

void AttackUI::Draw(void)
{
	// 現在の描画先を退避
	int tmpScreen = GetDrawScreen();
	int tmpBlend;
	int tmpParam;

	GetDrawBlendMode(&tmpBlend, &tmpParam);

	// 描画
	SetDrawScreen(_uiScreen);
	ClsDrawScreen();

	DrawGraph((UI_SIZE - RING_SIZE) / 2, (UI_SIZE - RING_SIZE) / 2, lpImageMng.getImage("base_ring")[0], true);

	// MPゲージ
	unsigned int color = 0xff0000;
	for (int i = 0; i < PRIMARY_COLOR_COUNT; i++)
	{
		SetDrawScreen(_mpScreen[i]);
		ClsDrawScreen();
		CreateMaskScreen();
		FillMaskScreen(1);
		DrawMask((UI_SIZE - RING_SIZE) / 2, (UI_SIZE - RING_SIZE) / 2, _maskHandle[i], DX_MASKTRANS_WHITE);
		DrawBox(0, static_cast<int>(MP_GAUGE_OFFSET[i] - _magicState[i].second * MP_GAUGE_HEIGHT[i] / MP_MAX), UI_SIZE, MP_GAUGE_OFFSET[i], color, true);
		if (_magicState[i].first == ATK_STATE::NON)
		{
			GraphFilter(_mpScreen[i], DX_GRAPH_FILTER_HSB, 0, 0, -255, 0);
		}
		color = color >> 8;
		DeleteMaskScreen();
	}
	SetDrawScreen(_uiScreen);
	for (const auto& sc : _mpScreen)
	{
		DrawGraph(0, 0, sc, true);
	}

	// スティック
	DrawRotaGraph(UI_SIZE / 2 + STICK_TO_POS(_stickX), UI_SIZE / 2 - STICK_TO_POS(_stickY), 1.0, 0.0, lpImageMng.getImage("stick_obj")[std::underlying_type<COLOR>::type(_AttackColor)], true);

	if (_OldAttackColor != _AttackColor && _AttackColor != COLOR::BLACK)
	{
		lpImageMng.playEffect("stick_effect_" + std::to_string(static_cast<int>(_AttackColor)), &_absStickX, &_absStickY, EFFECT_EX_RATE_STICK, 0.0, LAYER::EX, Z_ORDER + 1, DX_BLENDMODE_NOBLEND, 0, -1, EffectDrawType::DRAW_TO_ABSOLUTE);
	}
	if (_feverTime != 0 && (FEVER_DURATION - _feverTime) % 20 == 0)
	{
		std::uniform_real_distribution<double> _urd(RAD(-180), RAD(180));
		lpImageMng.playEffect("rev_stick_effect_7", &_absStickX, &_absStickY, 1.5, _urd(lpSceneMng._rnd), LAYER::EX, Z_ORDER + 1, DX_BLENDMODE_NOBLEND, 0, -1, EffectDrawType::DRAW_TO_ABSOLUTE);
	}

	SetDrawBlendMode(DX_BLENDMODE_SUB, 25);
	DrawRotaGraph(UI_SIZE / 2, UI_SIZE / 2, 1.0, 0.0, lpImageMng.getImage("ui_filter_1")[0], true);
	SetDrawBlendMode(tmpBlend, tmpParam);
	DrawRotaGraph(UI_SIZE / 2, UI_SIZE / 2, 1.0, 0.0, lpImageMng.getImage("ui_filter_2")[0], true);

	// 描画先を戻す
	SetDrawScreen(tmpScreen);

	// スクリーンを描画してもらう
	lpImageMng.AddBackDraw({ _uiScreen, DRAW_OFFSET_X, DRAW_OFFSET_Y, 1.0, 0.0, LAYER::EX, Z_ORDER, DX_BLENDMODE_NOBLEND, 0, true });
}

COLOR AttackUI::GetAttackColor(void)
{
	return _AttackColor;
}

bool AttackUI::CheckAttackActivate(void)
{
	return ((ACTIVE_RADIUS <= (static_cast<double>(_stickX) * static_cast<double>(_stickX) + static_cast<double>(_stickY) * static_cast<double>(_stickY))) && _coolTime == 0);
}

bool AttackUI::RunAttack(const int& coolTime, const int& MP)
{
	COLOR tmpColor = _AttackColor;
	int checkColor = 0x001;

	for (auto& data : _magicState)
	{
		if (data.first == ATK_STATE::RUN)
		{
			data.first = ATK_STATE::WAIT;
		}
	}

	_AttackColor = COLOR::BLACK;

	if (coolTime == -1)
	{
		return false;
	}

	_coolTime = coolTime;

	if (_feverTime > 0)
	{
		return true;
	}

	for (int i = 0; i < PRIMARY_COLOR_COUNT; i++)
	{
		if (static_cast<int>(tmpColor) & checkColor)
		{
			if (_magicState[i].second < static_cast<float>(MP))
			{
				// MPが足りないなら攻撃をしない
				return false;
			}
		}
		checkColor = checkColor << 1;
	}

	checkColor = 0x001;
	for (int i = 0; i < PRIMARY_COLOR_COUNT; i++)
	{
		if (static_cast<int>(tmpColor) & checkColor)
		{
			_magicState[i].second -= static_cast<int>(MP);
		}
		checkColor = checkColor << 1;
	}

	return true;
}

bool AttackUI::ToFeverTime(void)
{
	for (auto& data : _magicState)
	{
		if (data.second != MP_MAX)
		{
			return false;
		}
	}

	if (_feverTime == 0)
	{
		_feverTime = FEVER_DURATION;
		return true;
	}
	return false;
}

void AttackUI::Active(bool flag)
{
	_active = flag;
}

void AttackUI::MpUpdate(void)
{
	if (_feverTime > 0)
	{
		for (auto& data : _magicState)
		{
			data.second -= FEVER_MP_DEC;
			if (data.second < 0.0f)
			{
				data.second = 0.0f;
			}
		}
		return;
	}

	if (std::dynamic_pointer_cast<Player>(lpSceneMng.GetPlObj2(TIME::FTR))->GetStopTime()->IsTimeStoped())
	{
		return;
	}

	for (auto& data : _magicState)
	{
		data.second += MP_REGENERATION_SPEED;
		if (data.second > MP_MAX)
		{
			data.second = MP_MAX;
		}
	}
}

void AttackUI::ColorUpdate(void)
{
	if (!CheckAttackActivate())
	{
		return;
	}
	double&& stickRad = atan2(_stickY, _stickX);

	if (stickRad <= RAD(30) && stickRad >= RAD(-90))
	{
		if (_magicState[COLOR::GREEN - 1].first == ATK_STATE::WAIT)
		{
			_magicState[COLOR::GREEN - 1].first = ATK_STATE::RUN;
			_AttackColor = _AttackColor | COLOR::GREEN;
		}
	}
	else if (stickRad <= RAD(150) && stickRad > RAD(30))
	{
		if (_magicState[COLOR::BLUE - 2].first == ATK_STATE::WAIT)
		{
			_magicState[COLOR::BLUE - 2].first = ATK_STATE::RUN;
			_AttackColor = _AttackColor | COLOR::BLUE;
		}
	}
	else
	{
		if (_magicState[COLOR::RED - 1].first == ATK_STATE::WAIT)
		{
			_magicState[COLOR::RED - 1].first = ATK_STATE::RUN;
			_AttackColor = _AttackColor | COLOR::RED;
		}
	}
}

void AttackUI::StickTrans(void)
{

	// スティック座標を円形に矯正
	double&& stickRad = atan2(_stickY, _stickX);
	double length;
	double exRate;
	short tmpX;
	short tmpY;

	if (abs(_stickX) >= abs(_stickY))
	{
		exRate = abs(static_cast<double>(_stickX)) / STICK_RADIUS;
		tmpY = static_cast<short>(_stickY / exRate);
		length = sqrt(STICK_RADIUS * STICK_RADIUS + static_cast<double>(tmpY) * static_cast<double>(tmpY));
	}
	else
	{
		exRate = abs(static_cast<double>(_stickY)) / STICK_RADIUS;
		tmpX = static_cast<short>(_stickX / exRate);
		length = sqrt(static_cast<double>(tmpX) * static_cast<double>(tmpX) + STICK_RADIUS * STICK_RADIUS);
	}
	length = sqrt(static_cast<double>(_stickX) * static_cast<double>(_stickX) + static_cast<double>(_stickY) * static_cast<double>(_stickY))
		* exRate * STICK_RADIUS / length;

	_stickX = static_cast<short>(length * cos(stickRad));
	_stickY = static_cast<short>(length * sin(stickRad));
}

void AttackUI::StateUpdate(void)
{
	for (int i = 0; i < 3; i++)
	{
		if (_magicState[i].first != ATK_STATE::RUN)
		{
			if (lpTradeMng.ReBook(static_cast<COLOR>(static_cast<int>(exp2(i)))))
			{
				_magicState[i].first = ATK_STATE::WAIT;
			}
			else
			{
				_magicState[i].first = ATK_STATE::NON;
			}
		}
	}
}

AttackUI::AttackUI()
{
	// スクリーンの作成
	_uiScreen = MakeScreen(UI_SIZE, UI_SIZE, true);
	for (auto& sc : _mpScreen)
	{
		sc = MakeScreen(UI_SIZE, UI_SIZE, true);
	}

	// 素材読み込み
	char filename[32];
	std::string key;
	EffectData effect;
	effect.reserve(EFFECT_ANM_COUNT + 1);

	for (int i = 0; i < static_cast<int>(COLOR::MAX); i++)
	{
		key = "stick_effect_" + std::to_string(i);
		sprintf_s(filename, "image/UI/StickObjEffect%d.png", i);
		lpImageMng.getImage(filename, key, 120, 120, 10, 1);
		for (int j = 0; j < EFFECT_ANM_COUNT; j++)
		{
			effect.emplace_back(lpImageMng.getImage(key)[EFFECT_ANM_COUNT - j - 1], EFFECT_ANM_INTERVAL * (j + 1));
		}
		effect.emplace_back(0, -1);
		lpImageMng.setEffect(key, effect);
	}


	for (int j = 0; j < EFFECT_ANM_COUNT; j++)
	{
		effect.emplace_back(lpImageMng.getImage("stick_effect_7")[j], EFFECT_ANM_INTERVAL * (j + 1));
	}
	effect.emplace_back(0, -1);
	lpImageMng.setEffect("rev_stick_effect_7", effect);

	LoadDivMask("image/UI/MpMask.png", PRIMARY_COLOR_COUNT, PRIMARY_COLOR_COUNT, 1, RING_SIZE, RING_SIZE, _maskHandle);
	lpImageMng.getImage("image/UI/Ring1.png", "base_ring");
	lpImageMng.getImage("image/UI/StickObj.png", "stick_obj", 90, 90, 8, 1);
	lpImageMng.getImage("image/UI/UIFilter1.png", "ui_filter_1");
	lpImageMng.getImage("image/UI/UIFilter2.png", "ui_filter_2");

	// 初期化
	_stickX = 0;
	_stickY = 0;
	_absStickX = 0;
	_absStickY = 0;
	_OldAttackColor = COLOR::BLACK;
	_AttackColor = COLOR::BLACK;
	_magicState = { std::make_pair(ATK_STATE::NON, MP_MAX), std::make_pair(ATK_STATE::NON, MP_MAX), std::make_pair(ATK_STATE::NON, MP_MAX) };
	_coolTime = 0;
	_feverTime = 0;
}

AttackUI::~AttackUI()
{
	DeleteGraph(_uiScreen);
}
