#include <Dxlib.h>
#include "Scene/SceneMng.h"
#include "Graphic/ImageMng.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpSmdLine, int nCmdShow)
{

	SceneMng::GetInstance().Run();
}
