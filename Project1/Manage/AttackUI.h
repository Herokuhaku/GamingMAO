#pragma once
#include <cstddef>

#define lpAttackUI AttackUI::GetInstance()
#define STICK_TO_POS(val) (val / (0x7fff / (RING_RADIUS - STICK_OBJ_SIZE / 2)))
#define RAD(val) (val / 180 * acos(-1.0f))

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

	bool CheckAttackActivate(void);	// 右スティックが一定以上傾いているか
	int GetColor(void);				// 現在の色を返す
private:
	static AttackUI* sInstance;

	// 定義
	constexpr static int UI_SIZE = 300;
	constexpr static int RING_SIZE = 204;
	constexpr static int RING_RADIUS = 100;
	constexpr static int STICK_OBJ_SIZE = 60;

	constexpr static int DRAW_OFFSET_X = 1150;
	constexpr static int DRAW_OFFSET_Y = 600;

	constexpr static int ACTIVE_RADIUS = 40000000;
	constexpr static double STICK_RADIUS = 0x8000;

	constexpr static int RED_BYTE	= 0b001;
	constexpr static int GREEN_BYTE = 0b010;
	constexpr static int BLUE_BYTE	= 0b100;

	// UI用のスクリーンハンドル
	int _uiScreen;	

	// スティックの情報
	short _stickX;
	short _stickY;

	// 現在の攻撃色の情報
	int _AttackColor;

	void ColorUpdate(void);	// 色の更新
	void StickTrans(void);	// スティック座標を円に補正

	AttackUI();
	~AttackUI();
};

