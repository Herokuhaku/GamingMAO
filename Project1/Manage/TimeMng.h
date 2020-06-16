#pragma once

enum class TIME : int
{
	NOW,	// åªç›
	FTR,	// ñ¢óà
};

#define lpTimeMng TimeMng::GetInstance()

class TimeMng
{
public:
	static TimeMng& GetInstance()
	{
		if (sInstance == nullptr)
		{
			sInstance = new TimeMng();
		}

		return *sInstance;
	}

	static void Destroy()
	{
		if (sInstance != nullptr)
		{
			delete sInstance;
		}

		sInstance = nullptr;
	}
	
	void setTime(TIME time);
	TIME getTime(void);

	void ChangeTime(void);
	void resetFlag(void);

	void TimeInit(void);
private:
	static TimeMng* sInstance;

	TIME _crTime;
	bool _changeFlag;
	int _changeTime;

	static constexpr int INTERVAL = 15;

	TimeMng();
	~TimeMng();
};

