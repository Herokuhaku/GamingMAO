#include "Object.h"

Object::Object()
{
	_pos = { 0,300 };
	_rad = 0.0;
	_time = TIME::NOW;
	_stage = 0;
	_zOrder = 0;
	_state_dir = { OBJ_STATE::NORMAL, DIR::RIGHT };
	_alive = true;
	_anmFlame = 0;
	_anmTime = 0;
}

Object::~Object()
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
}

std::pair<OBJ_STATE, DIR> Object::getState(void)
{
	return _state_dir;
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
	anmUpdate();
	lpImageMng.AddDraw({ _anmMap[_state_dir][_anmFlame].first, _pos.x, _pos.y, _rad, LAYER::CHAR, _zOrder });
}

void Object::anmUpdate(void)
{
	// 範囲外チェック
	if (_anmMap.find(_state_dir) == _anmMap.end())
	{
		return;
	}
	if ((_anmFlame >= _anmMap[_state_dir].size()) || (_anmFlame < 0))
	{
		return;
	}

	// アニメーションのカウントのチェック
	if (_anmTime >= _anmMap[_state_dir][_anmFlame].second)
	{
		// ループ再生かをチェック
		if (_anmMap[_state_dir][_anmFlame].second >= 0)
		{
			_anmFlame++;
			// ワンショットの後ノーマルに戻るかのチェック
			if (_anmFlame < _anmMap[_state_dir].size())
			{
				if (_anmMap[_state_dir][_anmFlame].first == -10)
				{
					_state_dir.first = OBJ_STATE::NORMAL;
					_anmTime = 0;
					_anmFlame = 0;
				}
			}
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
}
