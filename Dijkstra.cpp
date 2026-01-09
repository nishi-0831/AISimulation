#include "Dijkstra.h"

// graph の 一次元目がマス、二次元目がそれに繋がっているマス
namespace Dijkstra
{
	Graph graph;
}
void Dijkstra::Init(std::unordered_map<Point, Node>& stage)
{
	graph.resize(STAGE_WIDTH * STAGE_HEIGHT);

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

Dijkstra::Graph& Dijkstra::GetGraph()
{
	 return graph;
}
