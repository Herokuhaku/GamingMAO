#pragma once
#include <array>
#include "COLOR.h"

#define lpAttackUI AttackUI::GetInstance()
#define STICK_TO_POS(val) (val / (0x7fff / (RING_RADIUS - STICK_OBJ_SIZE / 2)))
#define RAD(val) (val / 180.0 * acos(-1.0f))

enum class ATK_STATE
{
	NON,
	WAIT,
	RUN
};

class AttackUI
{
public:
	static AttackUI& GetInstance()
	{
		if (sInstance == nullptr)
		{
			sInstance = new AttackUI();
		}
		return *sInstance;
	}

	static void Destroy()
	{
		if (sInstance != nullptr)
		{
			delete sInstance;
		}
		sInstance = nullptr;
	}

	void Update(void);	// 更新
	void Draw(void);	// 描画

	bool CheckAttackActivate(void);			// 右スティックが一定以上傾いているか
	COLOR RunAttack(int coolTime);		// 攻撃を発動させる


private:
	static AttackUI* sInstance;

	// 定義
	static constexpr int UI_SIZE = 300;
	static constexpr int RING_SIZE = 204;
	static constexpr int RING_RADIUS = 100;
	static constexpr int STICK_OBJ_SIZE = 60;
	static constexpr int EFFECT_ANM_COUNT = 10;
	static constexpr int EFFECT_ANM_INTERVAL = 3;
	static constexpr double EFFECT_EX_RATE = 1.0;

	static constexpr int DRAW_OFFSET_X = 1150;
	static constexpr int DRAW_OFFSET_Y = 600;

	static constexpr int ACTIVE_RADIUS = 70000000;
	static constexpr double STICK_RADIUS = 0x8000;

	static constexpr int MP_MAX = 100;

	// UI用のスクリーンハンドル
	int _uiScreen;	

	// スティックの情報
	short _stickX;
	short _stickY;
	// スティックの絶対座標
	int _absStickX;
	int _absStickY;

	// 攻撃色の情報
	COLOR _OldAttackColor;
	COLOR _AttackColor;

	// 攻撃のクールタイム
	int _coolTime;

	void ColorUpdate(void);	// 色の更新
	void StickTrans(void);	// スティック座標を円に補正

	std::array<std::pair<ATK_STATE, unsigned int>, 3> _magicState;

	void StateUpdate(void);	// 魔法の状態の更新

	AttackUI();
	~AttackUI();
};

