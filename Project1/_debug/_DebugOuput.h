#pragma once
#ifdef _DEBUG
#include <windows.h>
#include <string>
#define OUTPUT(outstr) {\
OutputDebugString(outstr);\
OutputDebugString(__FILE__);\
}

#define DXLIB_MAKE_SCREEN_ERROR "DxLib::MakeScreen �G���["
#define DXLIB_LOAD_GRAPH_ERROR "DxLib::LoadGraph �G���["


#define CONTROLLER_GETJOYPADNO_N_ERROR "ControllerMng::getJoypadNo(DWORD no) no����������"
#define CONTROLLER_GETJOYPADNO_T_ERROR "ControllerMng::getJoypadNo(KTY_TYPE type) type����������"
#define KEY_TYPE_ERROR "keytype����������"

#endif
