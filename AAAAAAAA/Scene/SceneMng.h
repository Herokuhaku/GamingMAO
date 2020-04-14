#pragma once
#include <memory>
#include "BaceScene.h"

#define lpSceneMng SceneMng::GetInstance()

class SceneMng
{
public:

	void Run(void);

	static SceneMng &GetInstance(void)
	{
		Create();
		return *sInstance;
	};

	static void Create()
	{
		if (sInstance == nullptr)
		{
			sInstance = new SceneMng();
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

	unsigned int GetFlame(void) { return _flame; };

private:
	static SceneMng *sInstance;
	std::unique_ptr<BaceScene> _activeScene;

	unsigned int _flame;

	bool SysInit(void);
	SceneMng();
	~SceneMng();
	
};
