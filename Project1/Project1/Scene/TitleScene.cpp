#include "TitleScene.h"
#include "../Graphic/ImageMng.h"
#include "SceneMng.h"
#include "SeleScene.h"
#include "GameScene.h"


TitleScene::TitleScene()
{
	lpImageMng.getImage("image/hurosiki.png", "���C�~");
}

TitleScene::~TitleScene()
{
}

std::unique_ptr<BaceScene> TitleScene::Update(std::unique_ptr<BaceScene> own)
{
	lpImageMng.AddDraw({ lpImageMng.getImage("���C�~")[0],300,250,0.0,LAYER::BG,0 });

	if (lpSceneMng.GetFlame() == 120)
	{
		return std::make_unique<GameScene>();
	}

	return std::move(own);
}