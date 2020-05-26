#pragma once
#include "../Object.h"

#define lpAtkMng AttackMng::getInstance()

enum class ATK_TYPE
{
	FIRE_BALL,
	MAX
};

class AttackMng :
	public Object
{
public:
	static AttackMng& getInstance()
	{
		if (sInstance == nullptr)
		{
			sInstance = new AttackMng();
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

	void Update(void)override;

	void Draw(void)override;

	std::vector<std::shared_ptr<Object>> GetAttackObjList(void);

	// 赤魔法
	void MakeFireBall(Vector2 pos, DIR dir, Vector2 vec, TIME time, int stage, OBJ_TYPE target);
	void MakeBomb(Vector2 pos, DIR dir, int speed, double vel, TIME time, int stage, OBJ_TYPE target);
	
	// 青魔法
	void MakeBubble(Vector2 pos, TIME time, int stage, OBJ_TYPE target);
	void MakeBubbleBlast(Vector2 pos, TIME time, int stage, OBJ_TYPE target);

	// 緑魔法
	void MakeFruit(Vector2 pos, DIR dir, int speed, TIME time, int stage, OBJ_TYPE target);

	// 紫魔法
	void MakePoisonFog(Vector2 pos, int count, TIME time, int stage, OBJ_TYPE target);

	// 水色魔法
	void MakeIceWall(Vector2 pos, TIME time, int stage, OBJ_TYPE target);

	// 黄色魔法
	void MakeThunderCloud(Vector2 pos, DIR dir, int speed, int count, int dur, TIME time, int stage, OBJ_TYPE target);
	void MakeThunder(Vector2 pos1, Vector2 pos2, int damage, TIME time, int stage, OBJ_TYPE target);

	// 白魔法
	void MakeHolyJudge(Vector2 pos, TIME time, int stage, OBJ_TYPE target);

private:
	static AttackMng* sInstance;

	std::vector<std::shared_ptr<Object>> _attackObj;

	AttackMng();
	~AttackMng();
};

