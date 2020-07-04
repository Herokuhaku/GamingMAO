#pragma once
#include "BaseScene.h"

class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	~TitleScene();
	std::unique_ptr<BaseScene> Update(std::unique_ptr<BaseScene> own) override;
private:
	// çXêV
	BaseScene* FadeInUpdate(void);
	BaseScene* NormalUpdate(void);
	BaseScene* ReverseUpdate(void);
	BaseScene* FadeOutUpdate(void);

	BaseScene*(TitleScene::*_update)(void);

	// ï`âÊ
	void FadeInDraw(void);
	void NormalDraw(void);
	void ReverseDraw(void);
	void FadeOutDraw(void);		

	void(TitleScene::*_draw)(void);

	void DrawClock(void);
	void DrawReverseClock(void);
};

