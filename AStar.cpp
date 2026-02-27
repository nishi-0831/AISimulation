#include "AStar.h"
#include <queue>
#include <algorithm>
namespace AStar
{
	std::vector<int> distances;
	// {コスト、頂点のインデックス}
	using Pair = std::pair<int, int>;
	// using Graph = std::vector<std::vector<Edge>>;
	// 頂点から伸びている辺の配列
	// graph[0] で、0番目の頂点から伸びている辺を取得できる
	Graph graph;

	// 降順で並べる。そうすれば昇順で取り出せる
	std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> queue;

	std::vector<int> costs;
	// ターゲットの座標
	Point target;

	// 直前の頂点を記録する
	std::vector<int> p;
	// 始点からターゲットまでの経路
	std::vector<int> path;

	void InitToTargetDistance();
	
	
	int CalculateToTargetDistance(const Point& point);
}

void AStar::InitToTargetDistance()
{
	for (int x = 0;x < STAGE_WIDTH;x++)
	{
		for (int y = 0;y < STAGE_HEIGHT;y++)
		{
			Point current{ x,y };
			distances[y * STAGE_WIDTH + x] = CalculateToTargetDistance(current);
		}
	}
}

int AStar::CalculateToTargetDistance(const Point& point)
{
	return Point::ManhattanDistance(point,target);
}

void AStar::Init(std::unordered_map<Point, Node>& stage)
{
	graph.resize(STAGE_WIDTH * STAGE_HEIGHT);
	costs.resize(STAGE_WIDTH * STAGE_HEIGHT, COST_MAX);
	p.resize(STAGE_WIDTH * STAGE_HEIGHT, -1);
	distances.resize(STAGE_WIDTH * STAGE_HEIGHT);

	for (int x = 0;x < STAGE_WIDTH;x++)
	{
		for (int y = 0;y < STAGE_HEIGHT;y++)
		{
			Point current{ x,y };
			Node& node = stage[current];
			Tile tile = node.tile;
			if (tile == Tile::WALL)
				continue;


			// 上下左右のマスへのオフセット
			constexpr Point Offsets[] = { { 0, -1 }, { 0, 1 }, { -1, 0 }, { 1, 0 } };
			for (const auto& offset : Offsets)
			{
				// 新たなマスの座標
				const int nx = (current.x + offset.x);
				const int ny = (current.y + offset.y);
				const int nIndex = (ny * STAGE_WIDTH + nx);

				// 範囲外の場合はスキップする
				if ((nx < 0) || (STAGE_WIDTH <= nx) || (ny < 0) || (STAGE_HEIGHT <= ny))
				{
					continue;
				}

				// オフセット分進んだマス
				Point newPoint = Point::Add(current, offset);

				// 壁の場合はスキップする
				if (stage[newPoint].tile == Tile::WALL)
				{
					continue;
				}
				else
				{
					Edge edge = { .point = newPoint,.cost = stage[newPoint].cost };
					graph[y * STAGE_WIDTH + x].push_back(edge);
				}

			}
		}
	}
}

void AStar::SetStart(const Point& start)
{
	// 開始地点のコストを距離を0とする。
	queue.emplace(std::make_pair(0, STAGE_WIDTH * start.y + start.x));

	std::fill(costs.begin(), costs.end(), COST_MAX);
	distances[STAGE_WIDTH * start.y + start.x] = CalculateToTargetDistance(start);
	
	costs[STAGE_WIDTH * start.y + start.x] = 0;
}

void AStar::SetTarget(const Point& t)
{
	target = t;
}

std::vector<int> AStar::GetDistance(const Point& start)
{
	return costs;
}

std::vector<int> AStar::GetPath()
{
	return path;
}

std::vector<int> AStar::GetGrid()
{
	return distances;
}

void AStar::UpdateGraph()
{
	if (queue.empty())
		return;

	Pair pair = queue.top();
	auto [nodeCost, idx] = pair;
	queue.pop();

	// 取り出したマスと繋がっている辺を取得
	std::vector<Edge> edges = graph[idx];
	for (Edge& edge : edges)
	{
		// 辺の先にあるノードのインデックス
		int toIdx = STAGE_WIDTH * edge.point.y + edge.point.x;
		
		// 辺のコスト
		int cost = edge.cost ;
		// そのノードに割り当てられているコストより小さいなら
		if (cost < costs[toIdx])
		{
			// 直前の頂点を記録
			p[toIdx] = idx;
			// コスト更新
			costs[toIdx] = cost + costs[idx];
			// 探索キューに入れておく
			queue.emplace(std::make_pair(costs[toIdx] + distances[toIdx], toIdx));
		}
	}
	// 目標地点のインデックス
	int targetIdx = target.y * STAGE_WIDTH + target.x;
	// 目標地点への距離が初期値(COST_MAX)でないなら、到達したということ
	if (costs[targetIdx] != COST_MAX)
	{
		// ターゲットの直前の頂点から、始点へ遡っていく
		for (int i = targetIdx; i != -1; i = p[i])
		{
			path.push_back(i);
		}
		// 始点からターゲットへ、となるよう順序を逆転
		std::reverse(path.begin(), path.end());
	}
}

AStar::Graph& AStar::GetGraph()
{
	return graph;
}
