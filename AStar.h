#pragma once
#include <vector>
#include "global.h"

namespace AStar
{
	struct Edge
	{
		int cost;
		Point to;
	};
	struct AStarNode
	{
		int cost;
		int distanceToTarget;
	};
	bool operator>(const AStarNode& lhs, const AStarNode& rhs)
	{
		return (lhs.cost + lhs.distanceToTarget) > (rhs.cost + rhs.distanceToTarget);
	}
	bool operator<(const AStarNode& lhs, const AStarNode& rhs)
	{
		return rhs > lhs;
	}

	void Init(const std::unordered_map<Point, Node>& stage);
	void SetStart(const Point& start);
	void SetTarget(const Point& target);
}
