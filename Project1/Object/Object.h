#pragma once
#include <map>
#include <vector>
#include <array>
#include <memory>
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

// ��Ԉُ�
enum class STATE_EFFECT_TYPE
{
	PARALYSIS,
	FREEZE,
	CONFUSION
};

enum class COLLISION_TYPE
{
	SQUARE,
	CIRCLE,
};

class StateEffect;

using AnmVec = std::vector<std::pair<int, unsigned int>>;

struct atkData
{
	bool _isHit;
	OBJ_TYPE _myType;

	Vector2 _topLeft;
	Vector2 _bottomRight;

	Vector2 _offset;
	float _radius;

	int _damage;
	int _invincibleTime;
	OBJ_TYPE _target;
	COLLISION_TYPE _colType;

	atkData(bool isHit, OBJ_TYPE mytype, const Vector2& topleft, const Vector2& bottomright, int damage, int inv, OBJ_TYPE target) :
		_isHit(isHit), _myType(mytype), _topLeft(topleft), _bottomRight(bottomright), _damage(damage), _invincibleTime(inv), _target(target) 
	{
		_colType = COLLISION_TYPE::SQUARE;
	};

	atkData(bool isHit, OBJ_TYPE mytype, const Vector2& offset, float rad, int damage, int inv, OBJ_TYPE target) :
		_isHit(isHit), _myType(mytype), _offset(offset), _radius(rad), _damage(damage), _invincibleTime(inv), _target(target)
	{
		_colType = COLLISION_TYPE::CIRCLE;
	};

	int GetLeft(void)const;
	int GetRight(void)const;

	bool IsHit(const Vector2& mypos, DIR mydir, const Vector2& targetpos, const std::array<int, 4>& hitbox)const;
};

class Object
{
public:
	Object();
	virtual ~Object();
	
	virtual void Update(void);

	void setPos(Vector2Template<int> pos);
	void setPlTmpPos(Vector2Template<int> pos) { _tmpPos = { static_cast<double>(pos.x),static_cast<double>(pos.y) }; };
	Vector2Template<int> getPos(void);
	Vector2Template<int> getPosWithOffset(void);

	void MovePos(const Vector2Template<int>& pos);

	void setState(std::pair<OBJ_STATE, DIR> state);
	std::pair<OBJ_STATE, DIR> getState(void);
	
	// ��Ԉُ�֌W
	void SetStateEffect(StateEffect* sEff);
	void UpdateStateEffect(void);
	bool IsEffected(STATE_EFFECT_TYPE type);
	bool CanMoveWithEffect(void);

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

	virtual void IfHitAttack(std::shared_ptr<Object> target);

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

	bool _isColored = false;

	std::vector<std::unique_ptr<StateEffect>> _sEff; // ��Ԉُ�
	void DrawStateEffect(void);

	int _zOrder;							// Z�I�[�_�[
	double _exRate;							// �g�嗦
	OBJ_TYPE _type;							// �I�u�W�F�N�g�̎��
	std::pair<OBJ_STATE, DIR> _state_dir;	// �I�u�W�F�N�g�̏��
	double _stateEffectExRate = 1.0;

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

class StateEffect
{
	friend Object;

	STATE_EFFECT_TYPE _type;
	int _duration;
	int _timer;
public:
	/// <summary>
	/// ��Ԉُ�
	/// </summary>
	/// <param name="type">��Ԉُ�̎��</param>
	/// <param name="duration">��������</param>
	StateEffect(STATE_EFFECT_TYPE type, int duration) :_type(type), _duration(duration), _timer(duration) {};
	~StateEffect() = default;
};
