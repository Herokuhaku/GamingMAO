#pragma once
#include <memory>
#include <vector>

class Gimmick;

class GimmickMng
{
public:
	static GimmickMng& GetInstance()
	{
		if (sInstance == nullptr)
		{
			sInstance = new GimmickMng();
		}
		return *sInstance;
	}

	static void Destroy(void)
	{
		if (sInstance != nullptr)
		{
			delete sInstance;
			sInstance = nullptr;
		}
	}

	void Update(void);
	void Draw(void);

private:
	static GimmickMng* sInstance;

	std::vector<std::shared_ptr<Gimmick>> _gimmickList;

	GimmickMng();
	GimmickMng(const GimmickMng&) = delete;
	GimmickMng operator=(const GimmickMng&) = delete;
	~GimmickMng() = default;
};

