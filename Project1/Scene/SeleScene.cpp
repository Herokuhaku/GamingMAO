#include "TitleScene.h"
#include "SeleScene.h"
#include "GameScene.h"
#include "../Graphic/ImageMng.h"
#include "../Manage/KeyMng.h"
#include "../Manage/ButtonMng.h"


SeleScene::SeleScene()
{
	arrow = { 55,80 };
	arrowflag = true;
	sel = 0;
	sel2 = 0;
	lpImageMng.getImage("image/select.png", "Select");
	lpImageMng.getImage("image/arrow.png", "Arrow");
}


SeleScene::~SeleScene()
{
}

std::unique_ptr<BaseScene> SeleScene::Update(std::unique_ptr<BaseScene> own)
{
	// 1êl--------- èâÇﬂÇ©ÇÁ
	// 		|-----  ë±Ç´Ç©ÇÁ

	// 2êl--------- ïîâÆÇçÏÇÈ
	// 		|-----  ïîâÆÇ…ì¸ÇÈ

	if (CheckHitKey(KEY_INPUT_DOWN) && sel == 0)
	{
		if (arrowflag)
		{
			arrow.y += 250;
			sel2 = 1;
		}
		else
		{
			arrow.y += 100;
		}
		sel = 1;
	}
	if (CheckHitKey(KEY_INPUT_UP) && sel == 1)
	{
		if (arrowflag)
		{
			arrow.y -= 250;
			sel2 = 0;
		}
		else
		{
			arrow.y -= 100;
		}
		sel = 0;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT) && arrowflag)
	{
		arrow.x += 300;
		arrowflag = false;
		sel = 0;
	}
	if (CheckHitKey(KEY_INPUT_LEFT) && !arrowflag)
	{
		arrow.x -= 300;
		arrowflag = true;
		sel = sel2;
		if (sel2 == 0)
		{
			arrow.y = 80;
		}
		else
		{
			arrow.y = 80 + 250;	
		}
	}
	
	if ((lpKeyMng.getBuf()[KEY_INPUT_RETURN] && !lpKeyMng.getOldBuf()[KEY_INPUT_RETURN]) ||
		(lpButtonMng.Buttonf(0, XINPUT_BUTTON_B).first == 1 && lpButtonMng.Buttonf(0, XINPUT_BUTTON_B).second == 0))
	{
		switch (sel)
		{
		case 0:
			switch (sel2)
			{
			case 0:
				lpImageMng.setGkind(ScrEff::FADEOUT);
				return std::make_unique<GameScene>();
				break;
			default:
				break;
			}
		case 1:
			switch (sel2)
			{
			case 0:
				break;
			default:
				break;
			}
		default:
			break;
		}

		lpImageMng.setGkind(ScrEff::FADEOUT);
		return std::make_unique<SeleScene>();
	}

	lpImageMng.AddBackDraw({ lpImageMng.getImage("Select")[0], 300, 250, 1.0, 0.0, LAYER::BG, 0, DX_BLENDMODE_NOBLEND, 0 });
	lpImageMng.AddBackDraw({ lpImageMng.getImage("Arrow")[0], arrow.x, arrow.y, 1.0, 0.0, LAYER::UI, 0, DX_BLENDMODE_NOBLEND, 0 });
	return own;
}
