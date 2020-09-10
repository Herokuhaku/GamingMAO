#include "Door.h"
#include "../Graphic/ImageMng.h"
#include "../Manage/ButtonMng.h"
#include "../Manage/ItemTrader.h"
#include "../Scene/SceneMng.h"

namespace
{
	constexpr int DOOR_WIDTH = 64/2;
	constexpr int DOOR_HEIGHT = 112/2;
	constexpr int DOOR_USE_WIDTH = 64;
	constexpr int DOOR_USE_HEIGHT = 112;
}

Door::Door(const Vector2& pos, int stage)
{
	_hitBox = { DOOR_WIDTH, DOOR_WIDTH, DOOR_HEIGHT, DOOR_HEIGHT };
	_usableRange = { DOOR_USE_WIDTH, DOOR_USE_WIDTH, DOOR_USE_HEIGHT, DOOR_USE_HEIGHT };
	lpImageMng.getImage("image/Obstacle/door.png", "door");
	type_ = COLOR::YELLOW;
	_stage = stage;
	_pos = pos;

	_audio = std::make_shared<AudioContainer>();
	_audio->LoadSound("sound/magic/explosion.wav", "explosion", 10);
	_audio->ChangeVolume("explosion", 135);
}

Door::~Door()
{
}

void Door::Update(void)
{
	if (!_toDelete)
	{
		if (lpButtonMng.ButtonTrg(0, XINPUT_BUTTON_DPAD_DOWN) && lpTimeMng.getTime() == TIME::NOW)
		{
			Vector2 tmp = lpSceneMng.GetPlPos(TIME::NOW);
			if (lpTradeMng.CheckTool())
			{
				if (lpTradeMng.getTool().colortype == type_ && abs(tmp.x - _pos.x) <= DOOR_USE_WIDTH)
				{
					PlaySoundMem(_audio->GetSound("explosion"), DX_PLAYTYPE_BACK, true);
					lpTradeMng.SetUseTool(true, lpTradeMng.getTool());
					_toDelete = true;
					_hitBox = { 0,0,0,0 };
					lpTradeMng.UseDeleteTool();
				}
			}
		}
	}
	else
	{
		_timer--;
		if (_timer < 0)
		{
			_deleted = true;
		}
	}
}

void Door::Draw(void)
{
	lpImageMng.AddDraw({ lpImageMng.getImage("door")[0], _pos.x, _pos.y, 1.0, 0.0, LAYER::CHAR, -15, DX_BLENDMODE_ALPHA, static_cast<int>(255.0f * (static_cast<float>(_timer) / static_cast<float>(FADEOUT_DURATION))), true });
}
