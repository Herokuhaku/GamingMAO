#pragma once
#include "Gimmick.h"
#include "../Manage/COLOR.h"
class Door :
	public Gimmick
{
public:
	Door() = delete;
	Door(const Vector2& pos, int stage);
	~Door();

	void Update(void)override;
	void Draw(void)override;
private:
	COLOR type_;
	Vector2 pos_;

	bool _toDelete = false;

	static constexpr int FADEOUT_DURATION = 16;
	int _timer = FADEOUT_DURATION;
};

