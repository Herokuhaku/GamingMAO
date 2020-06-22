#pragma once
#include <DxLib.h>

#define lpKeyMng KeyMng::GetInstance()

class KeyMng
{
public:
	static KeyMng &GetInstance(void)
	{
		Create();
		return *sInstance;
	};

	static void Create()
	{
		if (sInstance == nullptr)
		{
			sInstance = new KeyMng();
		}
	};

	static void Destroy()
	{
		if (sInstance != nullptr)
		{
			delete sInstance;
		}
		sInstance = nullptr;
	};

	char* getBuf(void);
	char* getOldBuf(void);
	void KeyUpdate(void);
private:
	static KeyMng* sInstance;

	char _buf[256];
	char _oldBuf[256];

	KeyMng();
	KeyMng(const KeyMng&) = delete;
	KeyMng operator=(const KeyMng&) = delete;
	~KeyMng();
};

