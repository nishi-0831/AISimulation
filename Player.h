#pragma once
#include "Library/GameObject.h"
#include "GameObject2D.h"
#include "global.h"
#include "visit_struct/visit_struct.hpp"
class Player :
    public GameObject2D
{
	friend class VitableStruct;

	Point pos_;
	Point move;
	Point tile_;
public:
	Player();
	~Player();
	void Update() override;
	void SetDir() override;
	void Move() override;
	void Draw() override;
	Point GetTilePos() { return tile_; }
};

//VISITABLE_STRUCT(Player,tile_);