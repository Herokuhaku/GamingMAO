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

	void MakeFireBall(Vector2 pos, DIR dir, Vector2 vec, TIME time, int stage, OBJ_TYPE target);
	void MakeBubble(Vector2 pos, TIME time, int stage, OBJ_TYPE target);
	void MakeBubbleBlast(Vector2 pos, TIME time, int stage, OBJ_TYPE target);

private:
	static AttackMng* sInstance;

	std::vector<std::shared_ptr<Object>> _attackObj;

	AttackMng();
	~AttackMng();
};

