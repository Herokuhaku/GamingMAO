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
	// プレイヤーと弾のベクトル
	auto v = pPos - ePos;
	// 
	_vec.x = static_cast<float>(-(v.x / 2));
	// 座標補正用
	_ePos.x -= static_cast<int>(_vec.x);
	_ePos.y -= static_cast<int>((0.001f) * pow(_vec.x, 2));
	// 曲線をrrad分回転
	angle = (rrad * 3.141529 / 180);
	// 
	addX = (static_cast<int>(_dir) - 1) * 5;

	// 曲線のXに加算
	_vec.x += addX;
	// 曲線のYXを求めて座標補正
	_nextPos.y = static_cast<int>((0.001f) * pow(_vec.x, 2) + _ePos.y);
	_nextPos.x = _ePos.x + static_cast<int>(_vec.x);
	// 回転
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
	// 曲線のXに加算
	_vec.x += addX;
	// 曲線のYXを求めて座標補正
	_nextPos.y = (0.001f) * pow(_vec.x, 2) + _ePos.y;
	_nextPos.x = _ePos.x + static_cast<int>(_vec.x);
	// 回転
	_nextPos -= _fePos;
	_nextPos.x = _nextPos.x * cosf(angle) - _nextPos.y * sinf(angle);
	_nextPos.y = _nextPos.x * sinf(angle) + _nextPos.y * cosf(angle);
	_nextPos += _fePos;
	// 角度計算
	_rad = atan2(_nextPos.y - _pos.y, _nextPos.x - _pos.x);// +1.5708;

	if (_pos.x < 0 || _pos.x > 2400 || _pos.y < 0 || _pos.y > 2400)
	{
		_alive = false;
		setState({ OBJ_STATE::DEAD, _state_dir.second });
	}

	//if (CheckHitStage()(static_cast<CHECK_DIR>(static_cast<int>(_state_dir.second) / 2), _pos, getHitOffset(), _stage) != NOTHIT)
	//{
	//	//setState({ OBJ_STATE::A_NORMAL, _state_dir.second });
	//	//_update = &FireBall::ExplosionUpdate;
	//	//_exRate = 2.0;
	//	//_alive = false;
	//	//_timer = EXPLOSION_DURATION;
	//	//PlaySoundMem(_audio.GetSound("explosion"), DX_PLAYTYPE_BACK, true);
	//	_alive = false;
	//	setState({ OBJ_STATE::DEAD, _state_dir.second });
	//}
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

	attack.emplace_back(atkData(true, OBJ_TYPE::ATTACK, { 0, -6 }, { 20, 14 }, 30, 10, _target));
	attack.emplace_back(atkData(false, OBJ_TYPE::ATTACK, { 0, 0 }, { 0, 0 }, 0, -1, _target));

	setAttack("Efireball", attack);

	_type = OBJ_TYPE::ATTACK;
	setHitOffset({ 20,0,6,14 });

	AddAttack("Efireball");
	return false;
}
