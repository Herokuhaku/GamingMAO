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


	// -30 ~ 30xΜ_
	float rrad = rand() % 60 - 30;
	// vC[ΖeΜxNg
	auto v = pPos - ePos;
	// 
	_vec.x = static_cast<float>(-(v.x / 2));
	// ΐWβ³p
	_ePos.x -= static_cast<int>(_vec.x);
	_ePos.y -= static_cast<int>((0.001f) * pow(_vec.x, 2));
	// Θόπrradͺρ]
	angle = (rrad * 3.141529 / 180);
	// 
	addX = (static_cast<int>(_dir) - 1) * 5;

	// ΘόΜXΙΑZ
	_vec.x += addX;
	// ΘόΜYXπίΔΐWβ³
	_nextPos.y = static_cast<int>((0.001f) * pow(_vec.x, 2) + _ePos.y);
	_nextPos.x = _ePos.x + static_cast<int>(_vec.x);
	// ρ]
	_nextPos -= _fePos;
	_nextPos.x = _nextPos.x * cosf(angle) - _nextPos.y * sinf(angle);
	_nextPos.y = _nextPos.x * sinf(angle) + _nextPos.y * cosf(angle);
	_nextPos += _fePos;

	Init();
}

TrackingBall::~TrackingBall()
{
}

void TrackingBall::Update(void)
{
	_pos = _nextPos;
	// ΘόΜXΙΑZ
	_vec.x += addX;
	// ΘόΜYXπίΔΐWβ³
	_nextPos.y = (0.001f) * pow(_vec.x, 2) + _ePos.y;
	_nextPos.x = _ePos.x + static_cast<int>(_vec.x);
	// ρ]
	_nextPos -= _fePos;
	_nextPos.x = _nextPos.x * cosf(angle) - _nextPos.y * sinf(angle);
	_nextPos.y = _nextPos.x * sinf(angle) + _nextPos.y * cosf(angle);
	_nextPos += _fePos;
	// pxvZ
	_rad = atan2(_nextPos.y - _pos.y, _nextPos.x - _pos.x);// +1.5708;

	if (_pos.x < 0 || _pos.x > 2400 || _pos.y < 0 || _pos.y > 2400)
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

void TrackingBall::IfHitAttack(std::shared_ptr<Object> target)
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
