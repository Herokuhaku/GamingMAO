#include "Rock.h"
#include "../Graphic/ImageMng.h"
#include "../Manage/ButtonMng.h"
#include "../Manage/ItemTrader.h"
#include "../Scene/SceneMng.h"

namespace
{
	constexpr int ROCK_WIDTH = 200;
	constexpr int ROCK_HEIGHT = 256;
	constexpr int ROCK_USE_WIDTH = 250;
	constexpr int ROCK_USE_HEIGHT = 256;
}

Rock::Rock(const Vector2 & pos, int stage):Gimmick(pos, stage)
{
	_hitBox = { ROCK_WIDTH, ROCK_WIDTH, ROCK_HEIGHT, ROCK_HEIGHT };
	_usableRange = { ROCK_USE_WIDTH, ROCK_USE_WIDTH, ROCK_USE_HEIGHT, ROCK_USE_HEIGHT };
	lpImageMng.getImage("image/Obstacle/rock.png", "rock");
	type_ = COLOR::RED;
}

Rock::~Rock()
{
}

void Rock::Update(void)
{
	if (lpButtonMng.ButtonTrg(0,XINPUT_BUTTON_DPAD_DOWN) && lpTimeMng.getTime() == TIME::NOW)
	{
		Vector2 tmp = lpSceneMng.GetPlPos(TIME::NOW);
		if (lpTradeMng.CheckTool())
		{
			if (lpTradeMng.getTool().colortype == type_ && abs(tmp.x - _pos.x) <= ROCK_USE_WIDTH)
			{
				lpTradeMng.SetUseTool(true,lpTradeMng.getTool());
				_deleted = true;
			}
		}
	}
}

void Rock::Draw(void)
{
	lpImageMng.AddDraw({ lpImageMng.getImage("rock")[0], _pos.x, _pos.y, 2.0, 0.0, LAYER::CHAR, -15, DX_BLENDMODE_NOBLEND, 0 });
}
