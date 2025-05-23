#pragma once
#include "Library/GameObject.h"
#include "global.h"
class GameObject2D :
	public GameObject
{
protected:
	Point pos_;
	int hImage_;
	Point tile_;
	DIR nowDir;
public:
	GameObject2D();
	~GameObject2D();
	virtual void SetDir() {};
	virtual void Move() {};
	virtual void Update() override;
	virtual void Draw() override;
};

