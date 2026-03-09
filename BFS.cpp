#include "BFS.h"
#include <queue>
namespace BFS
{
	std::vector<std::pair<Tile, bool>> graph;
	std::vector<int> path;
	std::vector<int> p;
	std::vector<int> searchPoints;
	std::queue<int> queue;
	Point target;

	void Init(std::unordered_map<Point, Node>& _stage)
	{
		p.resize(STAGE_WIDTH * STAGE_HEIGHT, -1);
		graph.resize(STAGE_WIDTH * STAGE_HEIGHT);
		for (int y = 0; y < STAGE_HEIGHT; y++)
		{
			for (int x = 0; x < STAGE_WIDTH; x++)
			{
				Point curr; curr.x = x; curr.y = y;
				int idx = STAGE_WIDTH * y + x;
				graph[idx].first = _stage[curr].tile;
				graph[idx].second = false;
			}
		}
	}
	void SetStart(const Point& start)
	{
		queue.push(STAGE_WIDTH * start.y + start.x);
		searchPoints.push_back(STAGE_WIDTH * start.y + start.x);
		graph[STAGE_WIDTH * start.y + start.x].second = true;
	}
	void SetTarget(const Point& t)
	{
		target = t;
	}
	
	std::vector<int> GetPath()
	{
		return path;
	}
	void UpdateGraph()
	{
		if (queue.empty())
			return;

		int idx = queue.front();
		queue.pop();

		constexpr Point Offsets[] = { { 0, -1 }, { 0, 1 }, { -1, 0 }, { 1, 0 } };

		Point curr;
		curr.x = idx % STAGE_WIDTH;
		curr.y = idx / STAGE_WIDTH;
		for (const auto& offset : Offsets)
		{
			// 新たなマスの座標
			const int nx = (curr.x + offset.x);
			const int ny = (curr.y + offset.y);
			const int nIndex = (ny * STAGE_WIDTH + nx);
			Point nPoint(nx, ny);

			// 範囲外の場合はスキップする
			if ((nx < 0) || (STAGE_WIDTH <= nx) || (ny < 0) || (STAGE_HEIGHT <= ny))
			{
				continue;
			}

			// 壁の場合はスキップする
			if (graph[nIndex].first == Tile::WALL)
			{
				continue;
			}

			if (graph[nIndex].second)
			{
				continue;
			}
			graph[nIndex].second = true;

			queue.push(nIndex);
			searchPoints.push_back(nIndex);
			p[nIndex] = idx;
			if (nPoint == target)
			{
				int targetIdx = target.y * STAGE_WIDTH + target.x;
				// ターゲットの直前の頂点から、始点へ遡っていく
				for (int i = targetIdx; i != -1; i = p[i])
				{
					path.push_back(i);
				}
				std::reverse(path.begin(), path.end());
			}
		}
	}

	std::vector<int> GetSearchPoints()
	{
		return searchPoints;
	}

}

std::vector<RouteTile> RouteTileBFS(std::unordered_map<Point, Node>& distances, const Point& start)
{
	// グリッドの行数 (高さ)
	const int H = STAGE_HEIGHT;

	// グリッドの列数 (幅)
	const int W = STAGE_WIDTH;

	Point initPoint; initPoint.x = -1; initPoint.y = -1;
	// 各マスまでの最短距離（-1 は未訪問）
	std::vector<RouteTile> routeTiles(STAGE_WIDTH * STAGE_HEIGHT, RouteTile{ .distance = -1,.from = initPoint });
	//std::vector<std::vector<int>> distances(H, std::vector<int>(W, -1));

	// スタート地点の距離は 0 とする
	//distances[start.y][start.x] = 0;
	routeTiles[start.y * W + start.x].distance = 0;
	// 幅優先探索のキュー
	std::queue<Point> q;

	// スタート地点をキューに追加する
	q.push(start);

	// 上下左右のマスへのオフセット
	constexpr Point Offsets[] = { { 0, -1 }, { 0, 1 }, { -1, 0 }, { 1, 0 } };

	// MEMO: 先頭のマスを取り出し、四方向を調べて格納、また先頭の...という流れ
	while (!q.empty())
	{
		// キューの先頭のマスの座標（現在地）
		const Point current = q.front(); q.pop();

		// 上下左右の各マスを調べる
		// MEMO: 壁、範囲外の場合はキューに入れない
		for (const auto& offset : Offsets)
		{
			// 新たなマスの座標
			const int nx = (current.x + offset.x);
			const int ny = (current.y + offset.y);
			const int nIndex = (ny * STAGE_WIDTH + nx);

			// 範囲外の場合はスキップする
			if ((nx < 0) || (W <= nx) || (ny < 0) || (H <= ny))
			{
				continue;
			}

			// 壁の場合はスキップする
			if (distances[{nx, ny}].tile == Tile::WALL)
			{
				continue;
			}

			// すでに訪れている場合はスキップする
			// MEMO: 初めに-1で初期化しており、距離を書き込んだ場合は0以上になるので-1は未訪問
			if (routeTiles[nIndex].distance != -1)
			{
				continue;
			}

			// 新たなマスまでの距離を記録する
			// MEMO: distances[current.y][current.x] 現在のマスのスタートからの距離。それに1を足している。未探索と隣マスだから
			routeTiles[nIndex].distance = (routeTiles[current.y * STAGE_WIDTH + current.x].distance + 1);
			routeTiles[nIndex].from = current;
			routeTiles[nIndex].pos = Point(nx, ny);
			// 新たなマスをキューに追加する
			q.emplace(nx, ny);
		}
	}

	return routeTiles;
}