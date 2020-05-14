#include "Object.h"

std::map<std::string, std::vector<atkData>> Object::_attackMap;

Object::Object()
{
	_pos = { 0,0 };
	_rad = 0.0;
	_time = TIME::NOW;
	_zOrder = 0;
	_state_dir = { OBJ_STATE::NORMAL, DIR::RIGHT };
	_alive = true;
	_anmFlame = 0;
	_anmTime = 0;
	_hp = -1;
	_inv = 0;
	_hitOffset = {};
	_drawOffset_y = 0;
	_type = OBJ_TYPE::PLAYER;
	_nextPos = { 0,0 };
	_stage = 1;
}

Object::~Object()
{
}

void Object::Update(void)
{
}

void Object::setPos(Vector2Template<int> pos)
{
	_pos = pos;
}

Vector2Template<int> Object::getPos(void)
{
	return _pos;
}

void Object::setState(std::pair<OBJ_STATE, DIR> state)
{
	_state_dir = state;
	_anmFlame = 0;
	_anmTime = 0;
}

std::pair<OBJ_STATE, DIR> Object::getState(void)
{
	return _state_dir;
}

void Object::setHP(int hp)
{
	_hp = hp;
}

int Object::getHP(void)
{
	return _hp;
}

void Object::damagingHP(int damage)
{
	_hp -= damage;
	if (_hp <= 0)
	{
		setState({ OBJ_STATE::DEAD, _state_dir.second });
		if (_type == OBJ_TYPE::PLAYER)
		{
			stopAttack();
			lpEffectMng.stopEffect(_anmEfkHd);
		}
	}
	else if (_type == OBJ_TYPE::PLAYER)
	{
		setState({ OBJ_STATE::DAMAGE, _state_dir.second });
		stopAttack();
		lpEffectMng.stopEffect(_anmEfkHd);
	}
	else
	{

	}
}

void Object::setInv(int time)
{
	_inv = time;
}

bool Object::checkInv(void)
{
	return (_inv != 0);
}

void Object::InvUpdate(void)
{
	if (_inv > 0)
	{
		_inv--;
	}
}

void Object::setHitOffset(std::array<int, 4> ary)
{
	_hitOffset = ary;
}

std::array<int, 4> Object::getHitOffset(void)
{
	std::array<int, 4> tmpArray = _hitOffset;
	if (_state_dir.second == DIR::RIGHT)
	{
		tmpArray[0] = _hitOffset[1];
		tmpArray[1] = _hitOffset[0];
	}
	return _hitOffset;
}

void Object::setAnm(const std::pair<OBJ_STATE, DIR> state,AnmVec& data)
{
	_anmMap.try_emplace(state, std::move(data));
}

bool Object::isAnmEnd(void)
{
	return _anmMap[_state_dir][_anmFlame].second == -1;
}

bool Object::isAlive(void)
{
	if (_state_dir.first == OBJ_STATE::DEAD && isAnmEnd())
	{
		return false;
	}
	if (!_alive)
	{
		_state_dir.first = OBJ_STATE::DEAD;
	}
	return true;
}

void Object::Draw(void)
{
	if (!anmUpdate())
	{
		return;
	}

	lpImageMng.AddDraw({ _anmMap[_state_dir][_anmFlame].first, _pos.x, _pos.y - _drawOffset_y, _rad, LAYER::CHAR, _zOrder });
}

bool Object::anmUpdate(void)
{
	// 範囲外チェック
	if (_anmMap.find(_state_dir) == _anmMap.end())
	{
		return false;
	}
	if ((_anmFlame >= _anmMap[_state_dir].size()) || (_anmFlame < 0))
	{
		return false;
	}

	// アニメーションのカウントのチェック
	if (_anmTime >= _anmMap[_state_dir][_anmFlame].second)
	{
		// ループ再生かをチェック
		if (_anmMap[_state_dir][_anmFlame].first != -1)
		{
			_anmFlame++;
			if (_anmFlame < _anmMap[_state_dir].size() && 
				_anmMap[_state_dir][_anmFlame].second == 0)
			{
				setState({ OBJ_STATE::NORMAL, _state_dir.second });
			}
		}
		else
		{
			return false;
		}
	}

	// アニメーションのコマ数のチェック
	if (_anmFlame < _anmMap[_state_dir].size())
	{
		_anmTime++;
	}
	else
	{
		_anmTime = 0;
		_anmFlame = 0;
	}

	return true;
}

void Object::setAttack(const std::string key, std::vector<atkData>& data)
{
	auto check = _attackMap.try_emplace(key, std::move(data));
	if (check.second == false)
	{
		data.clear();
	}
}

void Object::AddAttack(const std::string key)
{
	if (_attackMap.find(key) == _attackMap.end())
	{
		return;
	}
	_attackData.emplace_back(key, 0);
}

void Object::attackUpdate(void)
{
	for (auto data = _attackData.begin(); data != _attackData.end();)
	{
		// 例外チェック
		if (_attackMap.find(data->first) == _attackMap.end())
		{
			data = _attackData.erase(data);
			continue;
		}
		// コマを進める
		(data->second)++;

		if (data->second >= _attackMap[data->first].size())
		{
			data = _attackData.erase(data);
		}
		else
		{
			data++;
		}
	}
}

std::vector<atkData> Object::getAttackQue(void)
{
	// 返すデータ
	std::vector<atkData> rtnvec;
	
	for (auto data = _attackData.begin(); data != _attackData.end();)
	{
		// 範囲外チェック
		if (_attackMap.find(data->first) == _attackMap.end())
		{
			data = _attackData.erase(data);
			continue;
		}

		if (data->second >= _attackMap[data->first].size())
		{
			data = _attackData.erase(data);
			continue;
		}

		if (std::get<0>(_attackMap[data->first][data->second]))
		{
			rtnvec.emplace_back(_attackMap[data->first][data->second]);
		}

		data++;
	}

	return rtnvec;
}

void Object::stopAttack(void)
{
	_attackData.clear();
}

void Object::setTimeLine(TIME time)
{
	_time = time;
}

TIME Object::getTimeLine(void)
{
	return _time;
}

