#pragma once
#ifdef _DEBUG
#include <windows.h>
#include <string>
#define OUTPUT(outstr) {\
OutputDebugString(outstr);\
OutputDebugString(__FILE__);\
}

#define DXLIB_MAKE_SCREEN_ERROR "DxLib::MakeScreen エラー"
#define DXLIB_LOAD_GRAPH_ERROR "DxLib::LoadGraph エラー"


#define CONTROLLER_GETJOYPADNO_N_ERROR "ControllerMng::getJoypadNo(DWORD no) noがおかしい"
#define CONTROLLER_GETJOYPADNO_T_ERROR "ControllerMng::getJoypadNo(KTY_TYPE type) typeがおかしい"
#define KEY_TYPE_ERROR "keytypeがおかしい"

#endif
