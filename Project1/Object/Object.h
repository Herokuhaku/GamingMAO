#pragma once
#include <map>
#include <vector>
#include <array>
#include "../common/Vector2.h"
#include "DIR.h"
#include "../Manage/TimeMng.h"

enum class OBJ_TYPE : int
{
	PLAYER,
	ENEMY,
	ITEM,
	CAMERA,
	ATTACK,
	MAX
};

enum class OBJ_STATE : int
{
	NORMAL,
	WALK,
	DASH,
	JUMP,
	A_NORMAL,
	A_WALK,
	A_DASH,
	A_JUMP,
	DAMAGE,
	FALL,
	ATTACK,
	DEAD
};

enum class CHECK_DIR : int
{
	LEFT,
	RIGHT,
	UP,
	DOWN
};

using AnmVec = std::vector<std::pair<int, unsigned int>>;
using atkData = std::tuple<bool, OBJ_TYPE, Vector2, Vector2, int, int, OBJ_TYPE>;

class Object
{
public:
	Object();
	virtual ~Object();

	virtual void Update(void);

	void setPos(Vector2Template<int> pos);
	void setPlTmpPos(Vector2Template<int> pos) { _tmpPos = { static_cast<double>(pos.x),static_cast<double>(pos.y) }; };
	Vector2Template<int> getPos(void);

	void setState(std::pair<OBJ_STATE, DIR> state);
	std::pair<OBJ_STATE, DIR> getState(void);

	void setHP(int hp);
	int getHP(void);
	virtual void damagingHP(int damage);

	void setInv(int time);
	bool checkInv(void);
	void InvUpdate(void);

	OBJ_TYPE getObjType(void) { return _type; };

	void setHitOffset(std::array<int, 4> ary);
	std::array<int, 4> getHitOffset(void);

	void setAnm(const std::pair<OBJ_STATE, DIR> state, AnmVec& data);
	bool isAnmEnd(void);
	bool isAlive(void);
	bool Alive(void) { return _alive; };

	virtual void Draw(void);
	bool anmUpdate(void);
	
	void setAttack(const std::string key, std::vector<atkData>& data);
	void AddAttack(const std::string key);
	void attackUpdate(void);
	std::vector<atkData>& getAttackQue(void);
	int getAnmEfk(void);
	void stopAttack(void);

	void setTimeLine(TIME time);
	TIME getTimeLine(void);

	void setStage(int stage) { _stage = stage; };
	int getStage(void) { return _stage; };

	virtual void IfHitAttack(void);

	void nextPos(void) { _pos = _nextPos; _tmpPos = { static_cast<double>(_nextPos.x),static_cast<double>(_nextPos.y) }; };
private:
	int _inv;						// ���G���ԁ@0�Ȃ疳�G�ł͂Ȃ�
	std::array<int, 4> _hitBox;	// ���W����̓����蔻��͈̔� 0:�� 1:�E 2:�� 3:��
protected:
	int _hp;						// �̗�
	Vector2 _pos;					// ���W(x:���S�@y:����)
	double _rad;					// �p�x
	int _drawOffset_y;				// �`�掞�̃I�t�Z�b�g(�摜�̒������W - ���Ӎ��W)

	TIME _time;						// ���Ԏ�
	int _stage;						// �X�e�[�W

	bool _alive;					// �����Ă邩

	int _zOrder;							// Z�I�[�_�[
	double _exRate;							// �g�嗦
	OBJ_TYPE _type;							// �I�u�W�F�N�g�̎��
	std::pair<OBJ_STATE, DIR> _state_dir;	// �I�u�W�F�N�g�̏��

	std::map<std::pair<OBJ_STATE, DIR>, AnmVec> _anmMap;	// �A�j���[�V������ۑ�����Ƃ�
	unsigned int _anmTime;			// �A�j���[�V�����̌o�ߎ���
	unsigned int _anmFlame;			// �A�j���[�V�����̌��݂̃R�}��

	int _anmEfkHd;					// effekseer�̃A�j���[�V�����n���h��

	Vector2Template<double> _tmpPos;

	std::map<std::string, std::vector<atkData>> _attackMap;	// �U���̏��
	std::vector<std::pair<std::string, unsigned int>> _attackData;	// �U�����̍U��

	// �Ԃ��f�[�^
	std::vector<atkData> rtnvec;
protected:
	// �X�e�[�W�ړ�
	Vector2 _nextPos;

};
