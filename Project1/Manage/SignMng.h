#pragma once
#include <string>
#include <memory>
#include <deque>
#include "../common/Vector2.h"

#define lpSignMng SignMng::GetInstance()

struct SignData;

class SignMng
{
public:
	static SignMng& GetInstance(void);
	
	void Check(void);
	void Draw(void);

	bool IsActive(void);
private:
	SignMng();
	SignMng(const SignMng&) = delete;
	SignMng operator=(const SignMng&) = delete;
	~SignMng() = default;

	bool _isActive = false;

	std::deque<std::unique_ptr<SignData>> _signs;
};

struct SignData
{
	SignData() = delete;
	SignData(const Vector2& pos, int stage, int screen) :_pos(pos), _stage(stage), _screen(screen) {};
	~SignData() = default;

	Vector2 _pos;
	int _stage;
	bool _active = false;

	int _screen;

	void Draw(void);
};
