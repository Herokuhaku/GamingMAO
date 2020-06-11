#include "AttackUI.h"
#include "ButtonMng.h"
#include "../Graphic/ImageMng.h"
#include "ItemTrader.h"
#include "Menu.h"

AttackUI* AttackUI::sInstance = nullptr;

void AttackUI::Update(void)
{
	// ���݂̉E�X�e�B�b�N�̏��̎擾
	lpButtonMng.GetThumb(THUMB_RIGHT, _stickX, _stickY);

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
	// ���݂̕`����ޔ�
	int tmpScreen = GetDrawScreen();

	// �`��
	SetDrawScreen(_uiScreen);
	ClsDrawScreen();

	DrawGraph((UI_SIZE - RING_SIZE) / 2, (UI_SIZE - RING_SIZE) / 2, lpImageMng.getImage("base_ring")[0], true);
	DrawRotaGraph(UI_SIZE / 2 + STICK_TO_POS(_stickX), UI_SIZE / 2 - STICK_TO_POS(_stickY), 1.0, 0.0, lpImageMng.getImage("stick_obj")[std::underlying_type<COLOR>::type(_AttackColor)], true);
	
	// �`����߂�
	SetDrawScreen(tmpScreen);

	// �X�N���[����`�悵�Ă��炤
	lpImageMng.AddBackDraw({ _uiScreen, DRAW_OFFSET_X, DRAW_OFFSET_Y, 1.0, 0.0, LAYER::EX, 500, DX_BLENDMODE_NOBLEND, 0 });
}

bool AttackUI::CheckAttackActivate(void)
{
	return ((ACTIVE_RADIUS <= (static_cast<double>(_stickX) * static_cast<double>(_stickX) + static_cast<double>(_stickY) * static_cast<double>(_stickY))) && _coolTime == 0);
}

COLOR AttackUI::RunAttack(int coolTime)
{
	COLOR rtnColor = static_cast<COLOR>(_AttackColor);

	for (auto& data : _magicState)
	{
		if (data.first == ATK_STATE::RUN)
		{
			data.first = ATK_STATE::WAIT;
		}
	}

	_AttackColor = COLOR::BLACK;

	_coolTime = coolTime;

	return rtnColor;
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
	// �X�e�B�b�N���W���~�`�ɋ���
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

	
}

void AttackUI::StateUpdate(void)
{
	for (int i = 0; i < 3; i++)
	{
		if (_magicState[i].first != ATK_STATE::RUN)
		{
			if (lpTradeMng.ReBook(lpMenuMng.ColorPtr(i)))
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
	// �X�N���[���̍쐬
	_uiScreen = MakeScreen(UI_SIZE, UI_SIZE, true);

	// �f�ޓǂݍ���
	lpImageMng.getImage("image/UI/AttackUIRing.png", "base_ring");
	lpImageMng.getImage("image/UI/StickObj.png", "stick_obj", 60, 60, 8, 1);

	// ������
	_stickX = 0;
	_stickY = 0;
	_AttackColor = COLOR::BLACK;
	_magicState = { std::make_pair(ATK_STATE::NON, MP_MAX) };
	_coolTime = 0;
}

AttackUI::~AttackUI()
{
	DeleteGraph(_uiScreen);
}
