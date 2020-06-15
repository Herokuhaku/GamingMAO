#include <Dxlib.h>
#include "Scene/SceneMng.h"
#include "Graphic/ImageMng.h"
#include "Manage/ButtonMng.h"
#include "Manage/Menu.h"
#include "Manage/ItemTrader.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpSmdLine, int nCmdShow)
{
	SceneMng::GetInstance().Run();
	
	ButtonMng::GetInstance().Destroy();
	ItemTrader::GetInstance().Destroy();
	Menu::GetInstance().Destroy();

	Effkseer_End();
	DxLib_End();
	return 0;
}
