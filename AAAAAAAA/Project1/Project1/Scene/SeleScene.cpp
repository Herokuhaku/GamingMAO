#include "SeleScene.h"
#include "../Graphic/ImageMng.h"


SeleScene::SeleScene()
{
	arrow = { 55,80 };
	arrowflag = false;
	ImageMngIns.getImage("image/select.png", "選択");
	ImageMngIns.getImage("image/arrow.png", "矢印");
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

	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		if (arrowflag)
		{
			arrow.y += 250;
		}
		else
		{
			arrow.y += 100;
		}
	}
	if (CheckHitKey(KEY_INPUT_UP))
	{
		if (arrowflag)
		{
			arrow.y -= 250;
		}
		else
		{
			arrow.y -= 100;
		}
	}
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{

	}

		ImageMngIns.AddDraw({ ImageMngIns.getImage("選択")[0],300,250,0.0,LAYER::BG,0 });
		ImageMngIns.AddDraw({ ImageMngIns.getImage("矢印")[0],arrow.x,arrow.y,0.0,LAYER::UI,0 });
		return own;
	}

