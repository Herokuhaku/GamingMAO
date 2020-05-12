#include "KeyMng.h"

KeyMng* KeyMng::sInstance = nullptr;

char * KeyMng::getBuf(void)
{
	return _buf;
}

char * KeyMng::getOldBuf(void)
{
	return _oldBuf;
}

void KeyMng::KeyUpdate(void)
{
	for (int i = 0; i < 256; i++)
	{
		_oldBuf[i] = _buf[i];
	}
	GetHitKeyStateAll(_buf);
}

KeyMng::KeyMng()
{
	GetHitKeyStateAll(_buf);
	GetHitKeyStateAll(_oldBuf);
}

KeyMng::~KeyMng()
{
}
