#pragma once
#include "../common/Vector2.h"
#include <array>

class Gimmick
{
public:
	Gimmick() = default;
	Gimmick(const Vector2Template<int>& pos, int stage);
	virtual ~Gimmick() = default;

	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	bool isDeleted(void);

	const Vector2Template<int>& GetPos(void)const;
	const std::array<int, 4>& GetHitBox(void)const;
	const std::array<int, 4>& GetUsable(void)const;
protected:
	// ���W
	Vector2Template<int> _pos;
	// �X�e�[�W
	int _stage;
	// �����蔻��
	std::array<int, 4> _hitBox;
	// �A�C�e���g�p�\�͈�
	std::array<int, 4> _usableRange;
	// �폜���Ă�����
	bool _deleted = false;
};

