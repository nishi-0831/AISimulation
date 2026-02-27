#include <vector>
#include <string>
#include <queue>
#include "../global.h"

/// @brief グリッド上の幅優先探索を行い、スタート地点から各マスまでの最短距離を求めます。
/// @param grid グリッド（'#' は壁、それ以外は通路）
/// @param start スタート地点の座標
/// @return スタート地点から各マスまでの最短距離を記録した二次元配列（-1 は未訪問）
/// @note 出典:『競プロのための標準 C++』

std::vector<std::vector<int>> GridBFS(const std::vector<std::string>& distances, const Point& start)
{
	// グリッドの行数 (高さ)
	const int H = static_cast<int>(distances.size());

	// グリッドの列数 (幅)
	const int W = static_cast<int>(distances[0].size());

	// 各マスまでの最短距離（-1 は未訪問）
	std::vector<std::vector<int>> costs(H, std::vector<int>(W, -1));

	// スタート地点の距離は 0 とする
	costs[start.y][start.x] = 0;

	// 幅優先探索のキュー
	std::queue<Point> q;

	// スタート地点をキューに追加する
	q.push(start);

	// 上下左右のマスへのオフセット
	constexpr Point Offsets[] = { { 0, -1 }, { 0, 1 }, { -1, 0 }, { 1, 0 } };

	while (!q.empty())
	{
		// キューの先頭のマスの座標（現在地）
		const Point current = q.front(); q.pop();

		// 上下左右の各マスを調べる
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
			if (distances[ny][nx] == '#')
			{
				continue;
			}

			// すでに訪れている場合はスキップする
			if (costs[ny][nx] != -1)
			{
				continue;
			}

			// 新たなマスまでの距離を記録する
			costs[ny][nx] = (costs[current.y][current.x] + 1);

			// 新たなマスをキューに追加する
			q.emplace(nx, ny);
		}
	}

	return costs;
}