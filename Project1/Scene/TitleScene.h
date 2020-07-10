#pragma once
#include "BaseScene.h"
#include "../common/Vector2.h"
#include <functional>
#include <string>
#include <vector>

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
	BaseScene* SelectUpdate(void);
	BaseScene* ReverseUpdate(void);
	BaseScene* FadeOutUpdate(void);

	BaseScene*(TitleScene::*_update)(void);

	// ï`âÊ
	void FadeInDraw(void);
	void NormalDraw(void);
	void SelectDraw(void);
	void ReverseDraw(void);
	void FadeOutDraw(void);		

	void(TitleScene::*_draw)(void);

	void DrawClock(void);
	void DrawReverseClock(void);

	struct MenuParts
	{
		std::string _text;
		Vector2Template<int> _pos;
		std::function<void(void)> _func;

		MenuParts(const char* text, Vector2Template<int>& pos, std::function<void(void)> func) :_text(text), _pos(pos), _func(func) {};
	};
	std::vector<MenuParts> _menu;
	int _cursor;
};

