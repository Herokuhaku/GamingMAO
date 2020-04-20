#pragma once
#include <memory>
#include "BaceScene.h"
#include "../Obj/Object.h"
#include "GameScene.h"
#include "../KeyMng.h"

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

	const std::shared_ptr<Object> *GetPlObj(void) const;
	void SetPlObj(std::shared_ptr<Object> plObj);
private:
	static SceneMng *sInstance;
	std::unique_ptr<BaceScene> _activeScene;
	std::shared_ptr<Object> _plObj;
	unsigned int _flame;

	bool SysInit(void);
	SceneMng();
	~SceneMng();
	
};
