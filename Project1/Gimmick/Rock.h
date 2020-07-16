#pragma once
#include "Gimmick.h"

class Rock :
	public Gimmick
{
public:
	Rock() = delete;
	Rock(const Vector2& pos, int stage);
	~Rock();

	void Update(void)override;
	void Draw(void)override;
private:
};

