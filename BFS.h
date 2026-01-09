#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include "global.h"
#include "Route.h"
/// @brief グリッド上の幅優先探索を行い、スタート地点から各マスまでの最短距離を求めます。
/// @param grid グリッド（'#' は壁、それ以外は通路）
/// @param start スタート地点の座標
/// @return スタート地点から各マスまでの最短距離を記録した二次元配列（-1 は未訪問）
/// @note 出典:『競プロのための標準 C++』

inline std::vector<std::vector<int>> BFS( std::unordered_map<Point, Tile>& grid, const Point& start)
{
	// グリッドの行数 (高さ)
	const int H = STAGE_HEIGHT;

	// グリッドの列数 (幅)
	const int W = STAGE_WIDTH;

	// 各マスまでの最短距離（-1 は未訪問）
	std::vector<std::vector<int>> distances(H, std::vector<int>(W, -1));

	// スタート地点の距離は 0 とする
	distances[start.y][start.x] = 0;

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

			// 範囲外の場合はスキップする
			if ((nx < 0) || (W <= nx) || (ny < 0) || (H <= ny))
			{
				continue;
			}

			// 壁の場合はスキップする
			if (grid[{nx,ny}] == Tile::WALL)
			{
				continue;
			}

			// すでに訪れている場合はスキップする
			// MEMO: 初めに-1で初期化しており、距離を書き込んだ場合は0以上になるので-1は未訪問
			if (distances[ny][nx] != -1)
			{
				continue;
			}

			// 新たなマスまでの距離を記録する
			// MEMO: distances[current.y][current.x] 現在のマスのスタートからの距離。それに1を足している。未探索と隣マスだから
			distances[ny][nx] = (distances[current.y][current.x] + 1);

			// 新たなマスをキューに追加する
			q.emplace(nx, ny);
		}
	}

	return distances;
}

inline std::vector<RouteTile> RouteTileBFS(std::unordered_map<Point, Node>& grid, const Point& start)
{
	// グリッドの行数 (高さ)
	const int H = STAGE_HEIGHT;

	// グリッドの列数 (幅)
	const int W = STAGE_WIDTH;

	Point initPoint; initPoint.x = -1; initPoint.y = -1;
	// 各マスまでの最短距離（-1 は未訪問）
	std::vector<RouteTile> routeTiles(STAGE_WIDTH * STAGE_HEIGHT, RouteTile{ .distance = -1,.from = initPoint});
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
			if (grid[{nx, ny}].tile == Tile::WALL)
			{
				continue;
			}

			// すでに訪れている場合はスキップする
			// MEMO: 初めに-1で初期化しており、距離を書き込んだ場合は0以上になるので-1は未訪問
			/*if (distances[ny][nx] != -1)
			{
				continue;
			}*/
			if (routeTiles[nIndex].distance != -1)
			{
				continue;
			}

			// 新たなマスまでの距離を記録する
			// MEMO: distances[current.y][current.x] 現在のマスのスタートからの距離。それに1を足している。未探索と隣マスだから
			//distances[ny][nx] = (distances[current.y][current.x] + 1);
			routeTiles[nIndex].distance = (routeTiles[current.y * STAGE_WIDTH + current.x].distance + 1);
			routeTiles[nIndex].from = current;
			routeTiles[nIndex].pos = Point(nx, ny);
			// 新たなマスをキューに追加する
			q.emplace(nx, ny);
		}
	}

	return routeTiles;
}