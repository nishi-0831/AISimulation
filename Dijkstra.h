#pragma once
#include <queue>
#include <vector>
#include <list>
#include "global.h"
namespace Dijkstra
{
	struct Edge
	{
		int to;
		int cost;
	};

	struct Node
	{
		Point pos;
		//std::list<Node*> children;
		std::list<Edge*> edges;
		bool confirmed = false;

		int cost;
	};

	using Graph = std::vector<std::vector<Edge>>;
	Graph graph;
	void Init(std::unordered_map<Point, Tile>& stage);
}