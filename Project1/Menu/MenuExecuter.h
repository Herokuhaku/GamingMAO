#pragma once
#include <vector>
#include <memory>
#include <functional>
#include "MenuBase.h"

class GameScene;

class MenuExecuter
{
public:
	MenuExecuter(GameScene* gs);
	~MenuExecuter() = default;

	// 更新
	void Update(void);
	// 描画
	void Draw(void);

	// ページを変える
	// menu:変更後のページ
	void ChangePage(MenuBase* menu);

	static bool IsActive(void);

	std::shared_ptr<MenuExecuter>& GetThis(void);
private:
	bool Control(void);

	// 現在のページ
	std::unique_ptr<MenuBase> _currentMenu;
	
	GameScene* _gameScene;
	
	// ページを変える用
	std::function<void(void)> _pageChanger;
	
	// メニューを開いているか
	static bool _active;
};

