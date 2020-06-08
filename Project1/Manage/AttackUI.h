#pragma once

#define lpAttackUI AttackUI::GetInstance()
#define STICK_TO_POS(val) (val / (RING_RADIUS - STICK_OBJ_SIZE / 2))

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

	void Update(void);
	void Draw(void);
private:
	static AttackUI* sInstance;

	// 定義
	constexpr static int UI_SIZE = 300;
	constexpr static int RING_SIZE = 204;
	constexpr static int RING_RADIUS = 100;
	constexpr static int STICK_OBJ_SIZE = 60;

	constexpr static int DRAW_OFFSET_X = 1150;
	constexpr static int DRAW_OFFSET_Y = 600;

	// UI用のスクリーンハンドル
	int _uiScreen;	

	// スティックの情報
	short _stickX;
	short _stickY;

	AttackUI();
	~AttackUI();
};

