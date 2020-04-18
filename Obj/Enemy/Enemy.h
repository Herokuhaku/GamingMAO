#pragma once
#include "../Object.h"

class Enemy :
	public Object
{
public:
	virtual	void Update(void) override;
	Enemy();
	~Enemy();
private:
	void Init(void);
	int cnt;
protected:

};
