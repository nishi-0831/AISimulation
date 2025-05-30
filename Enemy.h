#pragma once
#include "Library/GameObject.h"
#include "GameObject2D.h"
#include "global.h"
class Enemy :
	public GameObject2D
{
	Point pos_;
	int hImage_;
	Point tile_;

public:
	Enemy();
	~Enemy();
	void SetDir() override;
	
	void Anim() override;
	void Move() override;
	void Update() override;
	void Draw() override;
};

