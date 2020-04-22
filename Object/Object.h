#pragma once
#include <map>
#include <vector>
#include <memory>
#include "../Graphic/ImageMng.h"
#include "Object.h"


enum class OBJ_TYPE
{
	PLAYER,
	ENEMY,
	ITEM,
	CAMERA,
};

enum class OBJ_STATE
{
	NORMAL,
	WALK,
	ATTACK,
	DEAD
};

enum class DIR
{
	LEFT,
	NORMAL,
	RIGHT
};

enum class TIME
{
	NOW,	// ����
	FTR,	// ����
};

using AnmVec = std::vector<std::pair<int, int>>;

class Object
{
public:
	Object();
	virtual ~Object();

	virtual void Update(void) = 0;

	OBJ_TYPE getType(void) { return _type; };

	void setPos(Vector2Template<int> pos);
	Vector2Template<int> getPos(void);
	Vector2Template<int>* getPos2(void);

	void setState(std::pair<OBJ_STATE, DIR> state);
	std::pair<OBJ_STATE, DIR> getState(void);

	void setAnm(const std::pair<OBJ_STATE, DIR> state, AnmVec& data);
	bool isAnmEnd(void);
	bool isAlive(void);

	virtual void Draw(void);
	void anmUpdate(void);
protected:
	std::map<std::pair<OBJ_STATE, DIR>, AnmVec> _anmMap;	// �A�j���[�V������ۑ�����Ƃ�
	unsigned int _anmTime;				// �A�j���[�V�����̌o�ߎ���
	unsigned int _anmFlame;		// �A�j���[�V�����̌��݂̃R�}��

protected:
	Vector2Template<int> _pos;	// ���W
	double _rad;				// �p�x

	TIME _time;					// ���Ԏ�
	int _stage;					// �X�e�[�W

	bool _alive;				// �����Ă邩

	int _zOrder;							// Z�I�[�_�[
	OBJ_TYPE _type;							// �I�u�W�F�N�g�̎��
	std::pair<OBJ_STATE, DIR> _state_dir;	// �I�u�W�F�N�g�̏��
};

