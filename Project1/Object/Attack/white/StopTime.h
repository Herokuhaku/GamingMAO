#pragma once
#include <vector>

struct StopTime
{
	StopTime();
	~StopTime() = default;

	void Update(void);
	void Draw(void);

	bool IsTimeStoped(void);
	bool IsCountdowned(void);
	void Stop(void);
private:
	int _timer = 0;
	bool _timeIsStoped = false;

	static std::vector<int> _image;
	size_t _current;

	void Initialize(void);
};

