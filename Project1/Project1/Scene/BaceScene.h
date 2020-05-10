#pragma once
#include <memory>

class BaceScene
{
public:
	BaceScene();
	virtual ~BaceScene();
	virtual std::unique_ptr<BaceScene> Update(std::unique_ptr<BaceScene> own) = 0;

};

