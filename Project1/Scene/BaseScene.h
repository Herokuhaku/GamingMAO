#pragma once
#include <memory>

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	virtual std::unique_ptr<BaseScene> Update(std::unique_ptr<BaseScene> own) = 0;

};

