#pragma once
#include <array>
#include "COLOR.h"

#define lpAttackUI AttackUI::GetInstance()
#define STICK_TO_POS(val) (val / (0x7fff / (RING_RADIUS - STICK_OBJ_SIZE / 2)))
#define RAD(val) (val / 180.0 * acos(-1.0f))

// 色ごとの状態
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

	COLOR GetAttackColor(void);	// 現在の攻撃色の取得

	bool CheckAttackActivate(void);			// 右スティックが一定以上傾いているか
	bool RunAttack(const int& coolTime, const int& MP);		// 攻撃を発動させる
	
	bool ToFeverTime(void);
	void Active(bool);

	void Reset(void);
private:
	static AttackUI* sInstance;

	void Init(void);

	static constexpr int PRIMARY_COLOR_COUNT = 3;

	static constexpr int MP_GAUGE_OFFSET[PRIMARY_COLOR_COUNT] = { 251, 251, 147 };
	static constexpr int MP_GAUGE_HEIGHT[PRIMARY_COLOR_COUNT] = { 149, 149, 98 };

	// UI用のスクリーンハンドル
	int _uiScreen;

	// MP用スクリーンハンドル
	int _mpScreen[PRIMARY_COLOR_COUNT];

	// マスク画像ハンドルの格納用
	int _maskHandle[PRIMARY_COLOR_COUNT];

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

	// MP無しで出せる時間
	int _feverTime;

	void MpUpdate(void);
	void ColorUpdate(void);	// 色の更新
	void StickTrans(void);	// スティック座標を円に補正

	bool _active = true;

	std::array<std::pair<ATK_STATE, float>, PRIMARY_COLOR_COUNT> _magicState;	// 魔法の状態

	void StateUpdate(void);	// 魔法の状態の更新

	AttackUI();
	AttackUI(const AttackUI&) = delete;
	AttackUI operator+(const AttackUI&) = delete;
	~AttackUI();
};

