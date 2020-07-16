#pragma once
#include "../BaseScene.h"

class OpeningAnimationScene :
	public BaseScene
{
public:
	OpeningAnimationScene();
	~OpeningAnimationScene();
	std::unique_ptr<BaseScene> Update(std::unique_ptr<BaseScene> own) override;
private:
	void Update1(void);

	void (OpeningAnimationScene::*_update)(void);

	void Draw1(void);
	void (OpeningAnimationScene::*_draw)(void);
};

