#pragma once
#include <EffekseerForDXLib.h>
#include "../common/Vector2.h"
#include <memory>
#include "BaceScene.h"
#include "../Object/Object.h"
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

	const std::shared_ptr<Object> GetPlObj2(void) const;
	const std::shared_ptr<Object>* GetPlObj(void) const;
	void SetPlObj(std::shared_ptr<Object>& plObj);

	const Vector2D GetcPos(void) const;
	const std::shared_ptr<Vector2D> GetccPos(void) const;
	void SetcPos(std::shared_ptr<Vector2D> cPos);

	const Vector2 ScreenSize = { 1280,720 };
private:
	static SceneMng *sInstance;
	std::unique_ptr<BaceScene> _activeScene;
	std::shared_ptr<Object> _plObj;
	std::shared_ptr<Vector2D> _cPos;									// ÉJÉÅÉâç¿ïW

	unsigned int _flame;

	//Vector2Template<int> ScreenSize;
	Vector2Template<int> ScreenCenter;

	bool SysInit(void);
	SceneMng();
	~SceneMng();
	
};
