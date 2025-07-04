#pragma once
#include "Library/GameObject.h"
#include "GameObject2D.h"
#include "global.h"

class Player;
class RouteSearch;
namespace
{
	enum ESTATE
	{
		NORMAL,
		CHASE,
		ESCAPE,
		MAX_ESTATE
	};
}
class Enemy :
	public GameObject2D
{
	Point pos_;
	int hImage_;
	Point tile_;
	void UpdateNormal();
	void UpdateChase();
	void UpdateEscape();
	RouteSearch* routeSearch;
	ESTATE state_ = ESTATE::NORMAL; // åªç›ÇÃèÛë‘
public:
	Enemy();
	~Enemy();
	void SetDir() override;
	void SetDir(Point movement);
	void Anim() override;
	void Move() override;
	void Update() override;
	void Draw() override;
	bool CanSeePlayer(Player *p);

	bool IsInStage(Point point);
	void SafePushViewPoint(Point point);
};

