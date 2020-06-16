#pragma once
#include <random>
#include <memory>
#include "BaseScene.h"
#include "../Object/Object.h"
#include "../Graphic/StringAddDraw.h"

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

	const Vector2 GetPlPos(TIME time) const;
	const std::shared_ptr<Object> GetPlObj2(TIME time) const;
	const std::shared_ptr<Object>* GetPlObj(TIME time) const;
	void SetPlObj(std::shared_ptr<Object>& plObj, TIME time);

	const Vector2D GetcPos(void) const;
	const std::shared_ptr<Vector2D> GetccPos(void) const;
	void SetcPos(std::shared_ptr<Vector2D> cPos);

	void SetNum(int num);			// _workのset
	int GetNum(void);				// _workのget

	std::mt19937 _rnd;

	const Vector2 ScreenSize = { 1280,720 };
private:
	static SceneMng *sInstance;
	std::unique_ptr<BaseScene> _activeScene;
	std::map<TIME, std::shared_ptr<Object>> _plObj;
	std::shared_ptr<Vector2D> _cPos;									// カメラ座標

	unsigned int _flame;

	int _work;				// gameover用スクリーン

	bool SysInit(void);
	SceneMng();
	~SceneMng();
	
};
