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
	Thunder(Vector2 pos1, Vector2 pos2, int damage, TIME time, int stage, OBJ_TYPE target);
	~Thunder();

	void Draw(void)override;
private:
	void Init(void);

	int _damage;
	OBJ_TYPE _target;

	RAD_TYPE _rType;

};

