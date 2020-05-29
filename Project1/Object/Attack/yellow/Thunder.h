#pragma once
#include "../../Object.h"

enum class RAD_TYPE
{
	VRT,	// èc
	HRZ,	// â°
	EX		// ÇªÇÍà»äO(ââèoóp)
};

class Thunder :
	public Object
{
public:
	Thunder();
	Thunder(Vector2 pos1, Vector2 pos2, bool useRef, Vector2* refPos, int damage, TIME time, int stage, OBJ_TYPE target);
	~Thunder();

	void Update(void)override;

	void Draw(void)override;
private:
	void Init(void);

	Vector2* _refPos;
	Vector2 _offset;

	int _damage;
	OBJ_TYPE _target;

	RAD_TYPE _rType;

};

