#pragma once
#include "Library/GameObject.h"
#include "GameObject2D.h"
#include "global.h"
#include "ImGuiSample.h"
#include <map>
#include <functional>
class State;
class RouteSearch;
namespace
{
	enum UPDATESTATE
	{
		AUTO,
		DEBUG
	};
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
	//std::map<ESTATE, std::function<void()>> stateFunc_;
	std::vector<State*> eState_;
	ESTATE currentEstate_ = ESTATE::NORMAL; // åªç›ÇÃèÛë‘
	UPDATESTATE updateState_ = UPDATESTATE::AUTO;
public:
	Enemy();
	~Enemy();
	void SetDir() override;
	
	void Anim() override;
	void Move() override;
	void Update() override;
	void Draw() override;
	bool isUpdateCommandReceived_;
};

