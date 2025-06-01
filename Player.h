#pragma once
#include "Library/GameObject.h"
#include "GameObject2D.h"
#include "global.h"
class Player :
    public GameObject2D
{
	Point pos_;
	Point tile_;
	Point move;
public:
	Player();
	~Player();
	void Update() override;
	void SetDir() override;
	void Move() override;
	void Draw() override;
	Point GetTilePos() { return tile_; }
};

