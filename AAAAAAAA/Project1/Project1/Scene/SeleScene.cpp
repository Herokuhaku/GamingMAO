#include "SeleScene.h"
#include "../Graphic/ImageMng.h"


SeleScene::SeleScene()
{
	arrow = { 55,80 };
	arrowflag = false;
	ImageMngIns.getImage("image/select.png", "�I��");
	ImageMngIns.getImage("image/arrow.png", "���");
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

		ImageMngIns.AddDraw({ ImageMngIns.getImage("�I��")[0],300,250,0.0,LAYER::BG,0 });
		ImageMngIns.AddDraw({ ImageMngIns.getImage("���")[0],arrow.x,arrow.y,0.0,LAYER::UI,0 });
		return own;
	}

