#include "MenuBase.h"
#include "../Audio/AudioContainer.h"
#include <DxLib.h>
#include "../common/algo.h"

MenuBase::MenuBase(std::shared_ptr<MenuExecuter> exe, std::shared_ptr<AudioContainer> audio):_executer(exe), _audio(audio)
{
}

MenuBase::~MenuBase()
{
}

void MenuBase::DrawMenuBox(int posX, int posY, int sizeX, int sizeY, unsigned int boxColor, unsigned int edgeColor, int transParam)
{
	int blend, param;
	GetDrawBlendMode(&blend, &param);

	unsigned int trprm = algo::Clamp(transParam, 0, 255);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, trprm);

	DrawBox(posX, posY, posX + sizeX, posY + sizeY, boxColor, true);

	DrawBox(posX, posY, posX + sizeX, posY + sizeY, edgeColor, false);

	SetDrawBlendMode(blend, param);
}
