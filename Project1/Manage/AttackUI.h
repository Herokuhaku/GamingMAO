#pragma once
#include <array>

#define lpAttackUI AttackUI::GetInstance()
#define STICK_TO_POS(val) (val / (0x7fff / (RING_RADIUS - STICK_OBJ_SIZE / 2)))
#define RAD(val) (val / 180.0 * acos(-1.0f))

// 攻撃の種類
enum class ATK_COLOR : int
{
	EX,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	MGN,
	CYAN,
	WHITE,
	MAX
};

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
	ATK_COLOR RunAttack(int coolTime);		// 攻撃を発動させる


private:
	static AttackUI* sInstance;

	// 定義
	static constexpr int UI_SIZE = 300;
	static constexpr int RING_SIZE = 204;
	static constexpr int RING_RADIUS = 100;
	static constexpr int STICK_OBJ_SIZE = 60;

	static constexpr int DRAW_OFFSET_X = 1150;
	static constexpr int DRAW_OFFSET_Y = 600;

	static constexpr int ACTIVE_RADIUS = 70000000;
	static constexpr double STICK_RADIUS = 0x8000;

	static constexpr int RED_BYTE	= 0b001;
	static constexpr int GREEN_BYTE = 0b010;
	static constexpr int BLUE_BYTE	= 0b100;

	static constexpr int MP_MAX = 100;

	// UI用のスクリーンハンドル
	int _uiScreen;	

	// スティックの情報
	short _stickX;
	short _stickY;

	// 現在の攻撃色の情報
	int _AttackColor;

	// 攻撃のクールタイム
	int _coolTime;

	void ColorUpdate(void);	// 色の更新
	void StickTrans(void);	// スティック座標を円に補正

	std::array<std::pair<ATK_STATE, unsigned int>, 3> _magicState;

	void StateUpdate(void);	// 魔法の状態の更新

	AttackUI();
	~AttackUI();
};

