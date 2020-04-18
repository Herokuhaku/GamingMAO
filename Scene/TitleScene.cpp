#include "TitleScene.h"
#include "../Graphic/ImageMng.h"
#include "SceneMng.h"
#include "SeleScene.h"

TitleScene::TitleScene()
{
	lpImageMng.getImage("image/hurosiki.png", "•—˜C•~");
	lpImageMng.getImage("image/char.png", "1");
	lpImageMng.getImage("image/—§‚¿1.png", "2");
}


TitleScene::~TitleScene()
{
}

std::unique_ptr<BaceScene> TitleScene::Update(std::unique_ptr<BaceScene> own)
{
	lpImageMng.AddDraw({ lpImageMng.getImage("•—˜C•~")[0],300,250,0.0,LAYER::BG,0 });
	lpImageMng.AddDraw({ lpImageMng.getImage("1")[0],300,250,0.0,LAYER::CHAR,0 });
	lpImageMng.AddDraw({ lpImageMng.getImage("2")[0],300,450,0.0,LAYER::CHAR,0 });

	if (lpSceneMng.GetFlame() == 120)
	{
		return std::make_unique<SeleScene>();
	}

	return std::move(own);
}
