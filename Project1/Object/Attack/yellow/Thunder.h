#pragma once
#include "../../Object.h"

enum class RAD_TYPE
{
	VRT,	// �c
	HRZ,	// ��
	EX		// ����ȊO(���o�p)
};

class Thunder :
	public Object
{
public:
	Thunder() = delete;
	// pos1:�n�_���W		pos2:�I�_���W
	// useRef:refPos���Q�Ƃ��邩(refPos�̈ړ��ɍ��킹�ē����悤�ɂȂ�)
	// refPos:�Q�ƂɎg�����W
	// damage:�_���[�W		time:���Ԏ�
	// stage:�X�e�[�W		target:�ڕW
	Thunder(Vector2 pos1, Vector2 pos2, bool useRef, Vector2* refPos, int damage, TIME time, int stage, OBJ_TYPE target);
	~Thunder();

	void Update(void)override;

	void Draw(void)override;

	void IfHitAttack(std::shared_ptr<Object> target)override;
private:
	void Init(void);

	Vector2* _refPos;
	Vector2 _offset;

	int _damage;
	OBJ_TYPE _target;

	RAD_TYPE _rType;

};

