#include "SeleScene.h"
#include "../Graphic/ImageMng.h"


SeleScene::SeleScene()
{
	arrow = { 55,80 };
	arrowflag = true;
	sel = 0;
	sel2 = 0;
	lpImageMng.getImage("image/select.png", "�I��");
	lpImageMng.getImage("image/arrow.png", "���");
}


SeleScene::~SeleScene()
{
}

std::unique_ptr<BaceScene> SeleScene::Update(std::unique_ptr<BaceScene> own)
{
	// 1�l--------- ���߂���
	// 		|-----  ��������

	// 2�l--------- ���������
	// 		|-----  �����ɓ���

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


	lpImageMng.AddDraw({ lpImageMng.getImage("�I��")[0],300,250,0.0,LAYER::BG,0 });
	lpImageMng.AddDraw({ lpImageMng.getImage("���")[0],arrow.x,arrow.y,0.0,LAYER::UI,0 });
	return own;
}
