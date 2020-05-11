#include "SeleScene.h"
#include "../Graphic/ImageMng.h"


SeleScene::SeleScene()
{
	arrow = { 55,80 };
	arrowflag = true;
	sel = 0;
	sel2 = 0;
	lpImageMng.getImage("image/select.png", "選択");
	lpImageMng.getImage("image/arrow.png", "矢印");
}


SeleScene::~SeleScene()
{
}

std::unique_ptr<BaceScene> SeleScene::Update(std::unique_ptr<BaceScene> own)
{
	// 1人--------- 初めから
	// 		|-----  続きから

	// 2人--------- 部屋を作る
	// 		|-----  部屋に入る

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


	lpImageMng.AddDraw({ lpImageMng.getImage("選択")[0],300,250,0.0,LAYER::BG,0 });
	lpImageMng.AddDraw({ lpImageMng.getImage("矢印")[0],arrow.x,arrow.y,0.0,LAYER::UI,0 });
	return own;
}
