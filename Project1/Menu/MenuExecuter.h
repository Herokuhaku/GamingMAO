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

	// �X�V
	void Update(void);
	// �`��
	void Draw(void);

	// �y�[�W��ς���
	// menu:�ύX��̃y�[�W
	void ChangePage(MenuBase* menu);

	static bool IsActive(void);

	std::shared_ptr<MenuExecuter>& GetThis(void);
private:
	bool Control(void);

	// ���݂̃y�[�W
	std::unique_ptr<MenuBase> _currentMenu;
	
	GameScene* _gameScene;
	
	// �y�[�W��ς���p
	std::function<void(void)> _pageChanger;
	
	// ���j���[���J���Ă��邩
	static bool _active;
};

