#include "ItemMenu.h"
#include "MenuExecuter.h"
#include "../Audio/AudioContainer.h"

ItemMenu::ItemMenu(std::shared_ptr<MenuExecuter> exe, std::shared_ptr<AudioContainer> audio) : MenuBase(exe, audio)
{
}

ItemMenu::~ItemMenu()
{
}

void ItemMenu::Update(void)
{
}

void ItemMenu::Draw(void)
{
}
