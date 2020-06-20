#include "AttackUI.h"
#include "ButtonMng.h"
#include "../Graphic/ImageMng.h"
#include "ItemTrader.h"
#include "Menu.h"

AttackUI* AttackUI::sInstance = nullptr;

void AttackUI::Update(void)
{
	// 現在の色を保存
	_OldAttackColor = _AttackColor;

	// 現在の右スティックの情報の取得
	lpButtonMng.GetThumb(THUMB_RIGHT, _stickX, _stickY);

	MpUpdate();
	StickTrans();

	if (_coolTime != 0)
	{
		_coolTime--;
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

	CreateMaskScreen();
	unsigned int color = 0xff0000;
	for (int i = 0; i < PRIMARY_COLOR_COUNT; i++)
	{
		FillMaskScreen(1);
		DrawMask((UI_SIZE - RING_SIZE) / 2, (UI_SIZE - RING_SIZE) / 2, _maskHandle[i], DX_MASKTRANS_WHITE);
		DrawBox(0, MP_GAUGE_OFFSET[i] - _magicState[i].second * MP_GAUGE_HEIGHT[i] / MP_MAX, UI_SIZE, MP_GAUGE_OFFSET[i], color, true);
		color = color >> 8;
	}
	DeleteMaskScreen();

	DrawRotaGraph(UI_SIZE / 2 + STICK_TO_POS(_stickX), UI_SIZE / 2 - STICK_TO_POS(_stickY), 1.0, 0.0, lpImageMng.getImage("stick_obj")[std::underlying_type<COLOR>::type(_AttackColor)], true);

	if (_OldAttackColor != _AttackColor && _AttackColor != COLOR::BLACK)
	{
		lpImageMng.playEffect("stick_effect_" + std::to_string(static_cast<int>(_AttackColor)), &_absStickX, &_absStickY, EFFECT_EX_RATE_STICK, LAYER::EX, Z_ORDER + 1, DX_BLENDMODE_NOBLEND, 0, EffectDrawType::DRAW_TO_ABSOLUTE);
	}

	SetDrawBlendMode(DX_BLENDMODE_SUB, 25);
	DrawRotaGraph(UI_SIZE / 2, UI_SIZE / 2, 1.0, 0.0, lpImageMng.getImage("ui_filter_1")[0], true);
	SetDrawBlendMode(tmpBlend, tmpParam);
	DrawRotaGraph(UI_SIZE / 2, UI_SIZE / 2, 1.0, 0.0, lpImageMng.getImage("ui_filter_2")[0], true);

	// 描画先を戻す
	SetDrawScreen(tmpScreen);

	// スクリーンを描画してもらう
	lpImageMng.AddBackDraw({ _uiScreen, DRAW_OFFSET_X, DRAW_OFFSET_Y, 1.0, 0.0, LAYER::EX, Z_ORDER, DX_BLENDMODE_NOBLEND, 0 });
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

	_coolTime = coolTime;

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


void AttackUI::MpUpdate(void)
{
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
		length = sqrt(STICK_RADIUS * STICK_RADIUS + tmpY * tmpY);
	}
	else
	{
		exRate = abs(static_cast<double>(_stickY)) / STICK_RADIUS;
		tmpX = static_cast<short>(_stickX / exRate);
		length = sqrt(tmpX * tmpX + STICK_RADIUS * STICK_RADIUS);
	}
	length = sqrt(static_cast<double>(_stickX) * static_cast<double>(_stickX) + static_cast<double>(_stickY) * static_cast<double>(_stickY)) 
					* exRate * STICK_RADIUS / length;

	_stickX = static_cast<short>(length * cos(stickRad));
	_stickY = static_cast<short>(length * sin(stickRad));
	_absStickX = static_cast<int>(STICK_TO_POS(_stickX) + DRAW_OFFSET_X);
	_absStickY = static_cast<int>(STICK_TO_POS(-_stickY) + DRAW_OFFSET_Y);
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
}

AttackUI::~AttackUI()
{
	DeleteGraph(_uiScreen);
}
