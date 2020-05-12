#include "SeleScene.h"
#include "../Graphic/ImageMng.h"


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

std::unique_ptr<BaceScene> SeleScene::Update(std::unique_ptr<BaceScene> own)
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


	lpImageMng.AddDraw({ lpImageMng.getImage("Select")[0],300,250,0.0,LAYER::BG,0 });
	lpImageMng.AddDraw({ lpImageMng.getImage("Arrow")[0],arrow.x,arrow.y,0.0,LAYER::UI,0 });
	return own;
}
