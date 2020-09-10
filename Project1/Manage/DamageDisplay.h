#pragma once
#include<deque>
#include<memory>
#include"../common/Vector2.h"

struct DamageInfo;

class DamageDisplay
{
public:
	static DamageDisplay& GetInstance();

	void Draw(void);

	void AddDamage(DamageInfo* dInfo);

	void DeleteAll(void);
private:
	~DamageDisplay() = default;

	std::deque<std::unique_ptr<DamageInfo>> _damage;
};

struct DamageInfo
{
	friend DamageDisplay;

	DamageInfo(const Vector2& pos, int damage, int stage) :_pos(pos), _damage(abs(damage)), _stage(stage) { damage < 0 ? _color = 0x00ff00 : _color = 0xff0000; };
private:
	Vector2 _pos;
	int _damage;
	int _timer = 0;
	unsigned int _color;

	int _stage;
	bool _delete = false;
};

