#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include "global.h"
#include "Route.h"

namespace BFS
{
	void Init(std::unordered_map<Point, Node>& stage);
	void SetStart(const Point& start);
	void SetTarget(const Point& t);
	
	std::vector<int> GetPath();
	void UpdateGraph();
	std::vector<int> GetSearchPoints();
}



std::vector<RouteTile> RouteTileBFS(std::unordered_map<Point, Node>& distances, const Point& start);