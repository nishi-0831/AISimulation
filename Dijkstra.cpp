#include "Dijkstra.h"
#include <queue>
// graph の 一次元目がマス、二次元目がそれに繋がっているマス
namespace Dijkstra
{
	Graph graph;
	// ステージ全体のデータを持っている
	// 始点はコスト0で～
	std::vector<std::vector<int>> currentRoute;
}
void Dijkstra::Init(std::unordered_map<Point, Node>& stage)
{
	graph.resize(STAGE_WIDTH * STAGE_HEIGHT);
	currentRoute.resize(STAGE_HEIGHT);
	currentRoute[0].resize(STAGE_WIDTH);

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
				Point newPoint = Point::Add(current,offset);

				// 壁の場合はスキップする
				if (stage[newPoint].tile == Tile::WALL)
				{
					continue;
				}
				else
				{
					Edge edge = { .point = newPoint,.cost = stage[newPoint].cost};
					graph[y * STAGE_WIDTH + x].push_back(edge);
				}
				
			}
		}
	}
}

void Dijkstra::SetStart(const Point& start)
{
	//currentRoute[start.y][start.x].cost = 0;
}

// {距離(コスト)、頂点のインデックス}
using Pair = std::pair<int, int>;

std::vector<int> Dijkstra::GetDistance(const Point& start)
{
	// 降順で並べる。そうすれば昇順で取り出せる
	std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> queue;

	std::vector<int> distances(STAGE_WIDTH * STAGE_HEIGHT,INT_MAX);

	// 開始地点のコストを距離を0とする。
	queue.emplace(std::make_pair(0, STAGE_WIDTH * start.y + start.x));

	while (queue.empty() == false)
	{
		Pair pair = queue.top();
		auto [nodeCost, idx] = pair;
		queue.pop();

		// 取り出したマスと繋がっている辺を取得
		std::vector<Edge> edges = graph[idx];
		for (Edge& edge : edges)
		{
			// 辺のコスト + ノードの現時点でのコスト
			int cost = edge.cost + nodeCost;
			int toIdx = STAGE_WIDTH * edge.point.y + edge.point.x;
			if (cost < distances[toIdx])
			{
				distances[toIdx] = cost;
				queue.emplace(std::make_pair(distances[toIdx], toIdx));
			}
		}
	}

	return distances;
}

Dijkstra::Graph& Dijkstra::GetGraph()
{
	 return graph;
}
