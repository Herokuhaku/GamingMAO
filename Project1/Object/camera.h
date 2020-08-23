#pragma once
#include <memory>
#include "Object.h"
#include "../Scene/SceneMng.h"

class camera :
	public Object
{
public:

	void Update(void);
	void Draw(void) override;

	void SetcEndOffSet(Vector2&& cEndOffSet);

	camera();
	~camera();
private:
	std::map<TIME, std::shared_ptr<Object>> _plObj;
	std::shared_ptr<Vector2D> _cPos;
	Vector2 _oldPlPos[10];

	int addX1;
	int addX2;
	int addY1;
	int addY2;

	Vector2D _cOffSet;
	Vector2 _cEndOffSet;								// カメラがステージの最左右で行き過ぎないように

	bool CheckPos(void);
};
