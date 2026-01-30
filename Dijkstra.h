#pragma once
#include <queue>
#include <vector>
#include <list>
#include "global.h"
namespace Dijkstra
{
	struct Edge
	{
		Point point;
		int cost;
	};

	using Graph = std::vector<std::vector<Edge>>;
	
	/// <summary>
	/// ‚Ç‚±‚Æ‚Ç‚±‚ªŒq‚ª‚Á‚Ä‚¢‚é‚©İ’è‚·‚é
	/// </summary>
	/// <param name="stage"></param>
	void Init(std::unordered_map<Point, Node>& stage);
	void SetStart(const Point& start);
	void SetTarget(const Point& t);
	std::vector<int> GetDistance(const Point& start);
	std::vector<int> GetPath();
	void UpdateGraph();
	Graph& GetGraph();
}