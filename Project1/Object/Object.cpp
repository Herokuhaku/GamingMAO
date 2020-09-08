#include "Object.h"
#include "../Graphic/ImageMng.h"
#include "../Graphic/EffekseerMng.h"
#include "../Scene/SceneMng.h"
#include "Player.h"
#include "../func/CheckHitStage.h"
#include "../Audio/AudioContainer.h"
#include <memory>
#include <algorithm>

namespace
{
	AudioContainer _audio;
	const STATE_EFFECT_TYPE cantMoveEffects[] = { STATE_EFFECT_TYPE::PARALYSIS, STATE_EFFECT_TYPE::FREEZE, STATE_EFFECT_TYPE::CONFUSION };
}

Object::Object()
{
	_pos = { 0,0 };
	_rad = 0.0;
	_time = TIME::NOW;
	_zOrder = 0;
	_exRate = 1.0;
	_state_dir = { OBJ_STATE::NORMAL, DIR::RIGHT };
	_alive = true;

	_anmFlame = 0;
	_anmTime = 0;

	_hp = -1;
	_inv = 0;
	_hitBox = {};

	_drawOffset_y = 0;
	_type = OBJ_TYPE::PLAYER;
	_nextPos = { 0,0 };
	_stage = 1;

	_audio.LoadSound("sound/magic/freeze.wav", "freeze", 10);
	_audio.ChangeVolume("freeze", 180);
	_audio.LoadSound("sound/magic/confusion.wav", "confusion", 10);
	_audio.ChangeVolume("confusion", 180);
	_audio.LoadSound("sound/magic/paralysis.wav", "paralysis", 10);
	_audio.ChangeVolume("paralysis", 180);
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

Vector2Template<int> Object::getPosWithOffset(void)
{
	return Vector2Template<int>(_pos.x, _pos.y - _drawOffset_y);
}

void Object::MovePos(const Vector2Template<int>& pos)
{
	int l = CheckHitStage()(CHECK_DIR::LEFT, { _pos.x + pos.x, _pos.y }, getHitOffset(), _stage);
	int r = CheckHitStage()(CHECK_DIR::RIGHT, { _pos.x + pos.x, _pos.y }, getHitOffset(), _stage);
	int u = CheckHitStage()(CHECK_DIR::UP, { _pos.x, _pos.y + pos.y }, getHitOffset(), _stage);
	int d = CheckHitStage()(CHECK_DIR::DOWN, { _pos.x, _pos.y + pos.y }, getHitOffset(), _stage);

	if (l != NOTHIT)
	{
		_pos.x = l + getHitOffset()[static_cast<int>(CHECK_DIR::LEFT)];
	}
	else if (r != NOTHIT)
	{
		_pos.x = r - getHitOffset()[static_cast<int>(CHECK_DIR::RIGHT)];
	}
	else
	{
		_pos.x += pos.x;
	}
	if (u != NOTHIT)
	{
		_pos.y = u + getHitOffset()[static_cast<int>(CHECK_DIR::UP)];
	}
	else if (d != NOTHIT)
	{
		_pos.y = d - getHitOffset()[static_cast<int>(CHECK_DIR::DOWN)];
	}
	else
	{
		_pos.y += pos.y;
	}
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

void Object::SetStateEffect(StateEffect* sEff)
{
	if (IsEffected(sEff->_type))
	{
		return;
	}
	_sEff.emplace_back(sEff);

	switch (sEff->_type)
	{
	case STATE_EFFECT_TYPE::PARALYSIS:
		PlaySoundMem(_audio.GetSound("paralysis"), DX_PLAYTYPE_BACK, true);
		break;
	case STATE_EFFECT_TYPE::FREEZE:
		PlaySoundMem(_audio.GetSound("freeze"), DX_PLAYTYPE_BACK, true);
		break;
	case STATE_EFFECT_TYPE::CONFUSION:
		PlaySoundMem(_audio.GetSound("confusion"), DX_PLAYTYPE_BACK, true);
		break;
	}
}

void Object::UpdateStateEffect(void)
{
	if (_sEff.size() == 0)
	{
		return;
	}

	auto it = std::remove_if(_sEff.begin(), _sEff.end(), [](std::unique_ptr<StateEffect>& sEff) 
		{
			sEff->_timer--;
			return sEff->_timer <= 0;
		});
	_sEff.erase(it, _sEff.end());
}

bool Object::IsEffected(STATE_EFFECT_TYPE type)
{
	for (auto& se : _sEff)
	{
		if (se->_type == type)
		{
			return true;
		}
	}
	return false;
}

bool Object::CanMoveWithEffect(void)
{
	if (_sEff.size() == 0)
	{
		return true;
	}

	for (auto& se : _sEff)
	{
		for (auto& cme : cantMoveEffects)
		{
			if (se->_type == cme)
			{
				return false;
			}
		}
	}
	return true;
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
	if (damage == -1)
	{
		return;
	}

	_hp -= damage;
	if (damage <= 0)
	{
		if (damage < 0)
		{
			_hp = min(_hp, _hpLimit);
		}
		return;
	}

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
	_hitBox = ary;
}

std::array<int, 4> Object::getHitOffset(void)
{
	std::array<int, 4> tmpArray = _hitBox;
	if (_state_dir.second == DIR::RIGHT)
	{
		tmpArray[0] = _hitBox[1];
		tmpArray[1] = _hitBox[0];
	}
	return _hitBox;
}

void Object::setAnm(const std::pair<OBJ_STATE, DIR> state,AnmVec& data)
{
	_anmMap.try_emplace(state, std::move(data));	// dataを渡した後dataは使わないためmoveで移行する
}

bool Object::isAnmEnd(void)
{
	return _anmMap[_state_dir][_anmFlame].second == 2828;
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

	lpImageMng.AddDraw({ _anmMap[_state_dir][_anmFlame].first, _pos.x, _pos.y - _drawOffset_y, _exRate, _rad, LAYER::CHAR, _zOrder, DX_BLENDMODE_NOBLEND, 0, _isColored });
	DrawStateEffect();
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

	if (!(_type == OBJ_TYPE::PLAYER && _time == TIME::FTR) && std::dynamic_pointer_cast<Player>(lpSceneMng.GetPlObj2(TIME::FTR))->IsTimeStoped())
	{
		return true;
	}

	if (IsEffected(STATE_EFFECT_TYPE::FREEZE))
	{
		return true;
	}

	// アニメーションのカウントのチェック
	if (_anmTime >= _anmMap[_state_dir][_anmFlame].second)
	{
		// ループ再生かをチェック
		if (_anmMap[_state_dir][_anmFlame].first != -1)
		{
			_anmFlame++;
			if (_anmFlame < _anmMap[_state_dir].size() && 
				_anmMap[_state_dir][_anmFlame].first == -1)
			{
				if (_anmMap[_state_dir][_anmFlame].second == 0)
				{
					setState({ OBJ_STATE::NORMAL, _state_dir.second });
				}
				else
				{
					_alive = false;
				}
			}
		}
		else
		{
			_alive = false;
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
			if (_attackMap[data->first][data->second]._invincibleTime == -1)
			{
				data->second = 0;
			}
			data++;
		}
	}
}

std::vector<atkData>& Object::getAttackQue(void)
{
	// 返すデータ
	//std::vector<atkData> rtnvec;
	rtnvec.clear();
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

		if (_attackMap[data->first][data->second]._isHit == true)
		{
			rtnvec.emplace_back(_attackMap[data->first][data->second]);
		}

		data++;
	}

	return rtnvec;
}

int Object::getAnmEfk(void)
{
	return _anmEfkHd;
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

void Object::IfHitAttack(std::shared_ptr<Object> target)
{
	// 通常は何もなし
}

void Object::DrawStateEffect(void)
{
	if (_sEff.size() == 0)
	{
		return;
	}

	for (auto& se : _sEff)
	{
		switch (se->_type)
		{
		case STATE_EFFECT_TYPE::FREEZE:
			lpImageMng.AddDraw({ lpImageMng.getImage("ice_effect")[min(se->_duration / 4 - se->_timer / 4, 3)], _pos.x, _pos.y + _hitBox[3] - 50 * _stateEffectExRate, _stateEffectExRate, _rad, LAYER::CHAR, _zOrder + 1, DX_BLENDMODE_NOBLEND, 0, false });
			break;
		case STATE_EFFECT_TYPE::PARALYSIS:
			lpImageMng.AddDraw({ lpImageMng.getImage("spark")[se->_timer / 2 % 4 + 2], _pos.x, _pos.y - _drawOffset_y, _stateEffectExRate, _rad, LAYER::CHAR, _zOrder + 1, DX_BLENDMODE_NOBLEND, 0, false });
			break;
		case STATE_EFFECT_TYPE::CONFUSION:
			lpImageMng.AddDraw({ lpImageMng.getImage("star")[se->_timer / 4 % 6], _pos.x, _pos.y - _hitBox[2] - 15, 1.0, _rad, LAYER::CHAR, _zOrder + 1, DX_BLENDMODE_NOBLEND, 0, false });
			break;
		}
	}
}

int atkData::GetLeft(void) const
{
	return min(_topLeft.x, _bottomRight.x);
}

int atkData::GetRight(void) const
{
	return max(_topLeft.x, _bottomRight.x);
}

bool atkData::IsHit(const Vector2& mypos, DIR mydir, const Vector2 & targetpos, const std::array<int, 4>& hitbox)const
{
	int left = targetpos.x - hitbox[static_cast<int>(CHECK_DIR::LEFT)];
	int right = targetpos.x + hitbox[static_cast<int>(CHECK_DIR::RIGHT)];
	int top = targetpos.y - hitbox[static_cast<int>(CHECK_DIR::UP)];
	int bottom = targetpos.y + hitbox[static_cast<int>(CHECK_DIR::DOWN)];
	bool flag = true;
	Vector2 opos;

	int myleft;
	int myright;

	switch (_colType)
	{
	case COLLISION_TYPE::SQUARE:
		myleft = _topLeft.x * (static_cast<int>(mydir) - 1);
		myright = _bottomRight.x * (static_cast<int>(mydir) - 1);

		if (myleft > myright)
		{
			std::swap(myleft, myright);
		}

		return (left <= mypos.x + myright &&
			right >= mypos.x + myleft &&
			top <= mypos.y + _bottomRight.y &&
			bottom >= mypos.y + _topLeft.y);
		break;
	case COLLISION_TYPE::CIRCLE:
		opos = mypos + Vector2{ _offset.x * (static_cast<int>(mydir) - 1), _offset.y };

		if (left <= opos.x &&
			right >= opos.x &&
			top <= opos.y &&
			bottom >= opos.y)
		{
			return true;
		}

		if (left - _radius >= opos.x ||
			right + _radius <= opos.x ||
			top - _radius >= opos.y ||
			bottom + _radius <= opos.y)
		{
			return false;
		}
		else if (left >= opos.x && top >= opos.y &&
			_radius * _radius <= (opos.x - left) * (opos.x - left) + (opos.y - top) * (opos.y - top))
		{
			return false;
		}
		else if (right <= opos.x && top >= opos.y &&
			_radius * _radius <= (opos.x - right) * (opos.x - right) + (opos.y - top) * (opos.y - top))
		{
			return false;
		}
		else if (left >= opos.x && bottom <= opos.y &&
			_radius * _radius <= (opos.x - left) * (opos.x - left) + (opos.y - bottom) * (opos.y - bottom))
		{
			return false;
		}
		else if (right <= opos.x && bottom <= opos.y &&
			_radius * _radius <= (opos.x - right) * (opos.x - right) + (opos.y - bottom) * (opos.y - bottom))
		{
			return false;
		}
		return true;
		break;
	default:
		break;
	}
	return false;
}
