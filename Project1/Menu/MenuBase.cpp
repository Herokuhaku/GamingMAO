#include "MenuBase.h"
#include "../Audio/AudioContainer.h"

MenuBase::MenuBase(std::shared_ptr<MenuExecuter> exe, std::shared_ptr<AudioContainer> audio):_executer(exe), _audio(audio)
{
}

MenuBase::~MenuBase()
{
}
