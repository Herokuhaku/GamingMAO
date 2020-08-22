#include "TrackingBall.h"
#include "../../Graphic/ImageMng.h"
#include "../../Scene/SceneMng.h"
#include "../Attack/AttackMng.h"


TrackingBall::TrackingBall(Vector2 & ePos, Vector2 & pPos, TIME time, int stage, OBJ_TYPE target)
{
	_ePos = ePos;
	_fePos = ePos;
	_pos = _ePos;
	_pPos = pPos;
	_dir = _ePos.x > _pPos.x ? DIR::LEFT : DIR::RIGHT;
	_state_dir = { OBJ_STATE::NORMAL, _dir };
	_time = time;
	_stage = stage;
	_target = target;


	// -30 ~ 30度のランダム
	float rrad = rand() % 60 - 30;
	// プレイヤーと弾の角度
	auto v = pPos - ePos;

	float eprad = atan2(v.y, v.x);

	_vec.x = -(v.x / 2);
	_ePos.x -= _vec.x;

	_ePos.y -= (0.001f) * pow(_vec.x, 2);

	angle = (rrad * 3.141529 / 180) + eprad ;
	
	addX = (static_cast<int>(_dir) - 1) * 5;

	

	//auto a = v.UnitVec();
	//_vec = { a.x * 5.0f, a.y * 5.0f };


	_rad = atan2(_vec.y, _vec.x);

	Init();
}

TrackingBall::~TrackingBall()
{
}

void TrackingBall::Update(void)
{
	_vec.x += addX;

	_pos.y = (0.001f) * pow(_vec.x, 2) + _ePos.y;
	_pos.x = _ePos.x + _vec.x;

	_pos -= _fePos;
	_pos.x = _pos.x * cosf(angle) - _pos.y * sinf(angle);
	_pos.y = _pos.x * sinf(angle) + _pos.y * cosf(angle);
	_pos += _fePos;

	if (_pos.x < 0 || _pos.x > 2400)
	{
		_alive = false;
		setState({ OBJ_STATE::DEAD, _state_dir.second });
	}

//	_pos = { _pos.x + static_cast<int>(_vec.x), _pos.y + static_cast<int>(_vec.y) };
}

void TrackingBall::Draw(void)
{
	Object::Draw();
}

void TrackingBall::IfHitAttack(void)
{
	setState({ OBJ_STATE::DEAD, _state_dir.second });
}

bool TrackingBall::Init(void)
{
	AnmVec data;
	data.reserve(30);

	for (int i = 0; i < 30; i++)
	{
		data.emplace_back(lpImageMng.getImage("fireball")[i], i + 1);
	}

	setAnm({ OBJ_STATE::NORMAL, _state_dir.second }, data);

	for (int i = 0; i < 8; i++)
	{
		data.emplace_back(lpImageMng.getImage("explosion")[i], (i + 1)* 2);
	}
	data.emplace_back(-1, -1);

	setAnm({ OBJ_STATE::A_NORMAL, _state_dir.second }, data);

	std::vector<atkData> attack;
	attack.reserve(31);
	for (int i = 0; i < 30; i++)
	{
		attack.emplace_back(atkData(true, OBJ_TYPE::ATTACK, { 0, -6 }, { 20, 14 }, 30, 10, _target));
	}
	attack.emplace_back(atkData(false, OBJ_TYPE::ATTACK, { 0, 0 }, { 0, 0 }, 0, -1, _target));

	setAttack("fireball", attack);

	_type = OBJ_TYPE::ATTACK;
	setHitOffset({ 20,0,6,14 });

	AddAttack("fireball");
	return false;
}
