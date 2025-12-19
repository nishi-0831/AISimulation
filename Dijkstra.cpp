#include "Dijkstra.h"

void Dijkstra::Init(std::unordered_map<Point, Tile>& stage)
{
	graph.resize(STAGE_WIDTH);
	for (auto& edges : graph)
	{
		edges.resize(STAGE_HEIGHT);
	}

	for (int x = 0;x < STAGE_WIDTH;x++)
	{
		for (int y = 0;y < STAGE_HEIGHT;y++)
		{
			Point current{ x,y };
			Tile tile = stage[current];
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

				// 壁の場合はスキップする
				if (stage[{nx, ny}] == Tile::WALL)
				{
					continue;
				}

				
			}
		}
	}
}
