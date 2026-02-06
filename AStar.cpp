#include "AStar.h"
#include <queue>
namespace AStar
{
	using Graph = std::vector<std::vector<Edge>>;
	Graph graph;

	int startIdx;
	int targetIdx;

	// 各頂点への距離
	std::vector<int> distance;
	// コスト小さい奴から探索するためのキュー
	std::priority_queue<AStarNode, std::vector<AStarNode>, std::greater<AStarNode>> queue;

	// 頂点の直前の頂点を記録する配列
	std::vector<int> p;
	// 経路を記録
	std::vector<int> path;
}
void AStar::Init(const std::unordered_map<Point, Node>& stage)
{
	distance.resize(STAGE_HEIGHT * STAGE_WIDTH,INT_MAX);
		
	distance[startIdx] = 0;
	p.resize(STAGE_HEIGHT * STAGE_WIDTH,-1);
	path.resize(STAGE_HEIGHT * STAGE_WIDTH,-1);

	AStarNode node;
	node.cost = 0;
	int startX = startIdx % STAGE_WIDTH;
	int startY = startIdx / STAGE_WIDTH;
	int targetX = targetIdx % STAGE_WIDTH;
	int targetY = targetIdx / STAGE_WIDTH;
	node.distanceToTarget = std::abs(startX - targetX) + std::abs(startY - targetY);
	queue.push(node);

	Point dir[4] = { {0,1},{0,-1},{1,0},{-1,0} };
	for (int y = 0; y < STAGE_HEIGHT; y++)
	{
		for (int x = 0; x < STAGE_HEIGHT; x++)
		{
			Point p = { x,y };
			for (int i = 0;i < 4; i++)
			{
				Point searchPoint = Point::Add(p, dir[i]);

			}
		}
	}

}

void AStar::SetStart(const Point& start)
{
	startIdx = start.y * STAGE_WIDTH + start.x;
}

void AStar::SetTarget(const Point& target)
{
	targetIdx = target.y * STAGE_WIDTH + target.x;
}
