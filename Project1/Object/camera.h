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
	camera();
	~camera();
private:
	unsigned long long int _flame;			// �e�X�g
	std::map<TIME, std::shared_ptr<Object>> _plObj;
	std::shared_ptr<Vector2D> _cPos;
	Vector2 _oldPlPos[10];

	Vector2D _cOffSet;

	bool CheckPos(void);
};
