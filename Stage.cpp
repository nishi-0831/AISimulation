#include "Stage.h"
#include "global.h"
#include <random>
#include <chrono>
#include <algorithm>
#include "BFS.h"
#include "Dijkstra.h"
#include "BFS.h"
#include <iostream>
#include <fstream>
#include "Input.h"
#include <ranges>
#include <filesystem>
using namespace std;
namespace views = std::ranges::views;
namespace fs = std::filesystem;
vector<string> split(const string& _text, const char delimiter = ' ')
{
	vector<string> ret;
	for (const auto& word_range : _text | views::split(delimiter))
	{
		auto itr = std::ranges::begin(word_range);
		auto len = static_cast<size_t>(std::ranges::distance(word_range));
		string str(&*itr, len);
		ret.push_back(str);
	}
	return ret;
}

namespace
{
	// 通路の開始位置
	Point startPoint{ 2,2 };
	
	// 現在時刻をシード値に
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	// 謎の乱数生成器
	std::mt19937 gen(seed);

	// 掘り進めスタート位置を記録
	std::vector<Point> roads;
	
	// シャッフル用の掘り進め方向の配列
	std::vector<Point> dirArray = { moveDirArray[0],moveDirArray[1],moveDirArray[2],moveDirArray[3] };

	std::vector<Point> roadOnly;
}

bool IsOutOfStage(Point p);
bool IsEven(Point p);

Stage* Stage::instance_ = nullptr;
Stage::Stage()
{	
	//LoadMapData();
	Dig();
	BFS::Init(stage_);
	BFS::SetTarget(end_);
	BFS::SetStart(start_);
	//Dijkstra::InitToTargetDistance();
}

Stage::~Stage()
{
	instance_ = nullptr;
}

void Stage::Update()
{
	if (Input::IsKeyDown(KEY_INPUT_SPACE))
	{
		BFS::UpdateGraph();
	}
}

void Stage::Draw()
{
	//外枠の描画
	//ステージの描画
	for (int y = 0; y < STAGE_HEIGHT; y++)
	{
		for (int x = 0; x < STAGE_WIDTH; x++)
		{
			int color;
			bool flag = false;
			switch (stage_[Point{x,y}].tile)
			{
			case Tile::ROAD:
				color = GetColor(0, 0, 125);
				break;
			case Tile::ESCAPEPOINT:
				color = GetColor(122, 122, 122);
				flag = true;
				break;
			case Tile::WALL:
				color = GetColor(139, 69, 19);
				flag = true;
				break;
			default:
				color = GetColor(255, 255, 255);
			}
			Node& node = stage_[Point{ .x = x,.y = y }];
			DrawBox(x * CHA_SIZE, y * CHA_SIZE, (x + 1) * CHA_SIZE, (y + 1) * CHA_SIZE, color, flag);

		}
	}
	DrawDistance();
	int color = GetColor(255, 0, 0);
	DrawBox(start_.x * CHA_SIZE, start_.y * CHA_SIZE, (start_.x + 1) * CHA_SIZE, (start_.y + 1) * CHA_SIZE, color, false);
	DrawString(end_.x * CHA_SIZE, end_.y * CHA_SIZE, "end", color);
}

void Stage::DrawDistance()
{
	unsigned int red = GetColor(200, 0, 0);

	std::vector<int> distance = BFS::GetSearchPoints();
	std::vector<int> path = BFS::GetPath();

	for (int i = 0; i < distance.size();i++)
	{
		int dis = distance[i];
		int x = dis % STAGE_WIDTH;
		int y = dis / STAGE_WIDTH;

		
		if (dis != COST_MAX)
		{
			std::string disStr = std::to_string(dis);
			
			DrawBox(x * CHA_SIZE, y * CHA_SIZE, (x + 1) * CHA_SIZE, (y + 1) * CHA_SIZE, red, true);			
		}
	}
	for (int i = 0; i < path.size();i++)
	{
		int idx = path[i];
		int x = idx % STAGE_WIDTH;
		int y = idx / STAGE_WIDTH;
		
		int color = GetColor(255, 255, 255);
		DrawBox(x * CHA_SIZE, y * CHA_SIZE, (x + 1) * CHA_SIZE, (y + 1) * CHA_SIZE, color, true);
	}
	
}

bool Stage::IsWall(Point point)
{
	if (stage_[point].tile == Tile::WALL)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void Stage::Dig()
{
	// 開始位置(x,yいずれか)が奇数だと4ブロック以上の道が出来てしまうので偶数にする
	std::uniform_int_distribution<> diceX(1, (STAGE_WIDTH - 2) / 2);
	std::uniform_int_distribution<> diceY(1, (STAGE_HEIGHT - 2) / 2);
	startPoint.x = diceX(gen) * 2;
	startPoint.y = diceY(gen) * 2;

	for (int y = 0; y < STAGE_HEIGHT; y++)
	{
		for (int x = 0; x < STAGE_WIDTH; x++)
		{
			stage_[{x, y}].tile = Tile::WALL;
			std::uniform_int_distribution<> diceCost(0, 10);
			stage_[{x, y}].cost = 0;
			//stage_[{x, y}].cost = diceCost(gen);
		}
	}
	
	// 初期の掘り進めスタート位置
	stage_[startPoint].tile = Tile::ROAD;
	roads.push_back(startPoint);

	while (roads.empty() == false)
	{
		Point point = roads.back();
		DigRecursive(point);
		roadOnly.push_back(point);
		// 一回掘ったらスタート位置は削除
		std::erase(roads, point);
	}

	std::uniform_int_distribution<> distGoal(0,roadOnly.size() - 1);
	int idxGoal = distGoal(gen);	
	end_ = roadOnly[idxGoal];
}

void Stage::DigRecursive(Point start)
{
	Point next = start;

	// 4方向どちらから掘るかランダムにする
	std::shuffle(dirArray.begin(), dirArray.end(), gen);

	for (int j = 0; j < 4; j++)
	{
		Point dir = dirArray[j];

		// 始点を保存
		Point prevNext = next;

		// 二つ先のマスを取得
		next = Point::Add(next, Point::Multi(dir, 2));

		// 範囲外ならtrue
		if (IsOutOfStage(next))
		{
			// 範囲外だったため以前の場所に戻って別の方向を試す
			next = prevNext;
			continue;
		}

		if (stage_[next].tile == Tile::ROAD)
		{
			// すでに掘られていたため以前の場所に戻って別の方向を試す
			next = prevNext;
			continue;
		}

		// 2マス先を掘る			
		stage_[next].tile = Tile::ROAD;

		// 1マス先も掘る
		stage_[Point::Sub(next, dir)].tile = Tile::ROAD;

		// 偶数なら掘り進めましたと記録しておく
		if (IsEven(next))
		{
			roads.push_back(next);
		}

		if (IsEven(Point::Sub(next, dir)))
		{
			roads.push_back(Point::Sub(next, dir));
		}

		// 掘れる方向があったのでfor文は終了
		j = 4;
		// 掘った場所を始点に再度、堀進めて行く
		DigRecursive(next);
	}

	// 4方向探してもなかった
	return;
}

Point Stage::GetRandRoadPos()
{
	std::uniform_int_distribution<> distIdx(0, roadOnly.size());	
	int index = distIdx(gen);
	return roadOnly[index];
}

void Stage::LoadMapData()
{
	//頑張ってファイル選択ダイアログを出す
	fs::path filePath = "Assets/SData.txt";

	//ファイル名はlpstrFileに渡したfilenameに入ってる
	{
		std::ifstream inputfile(filePath);
		if (!inputfile)
		{
			std::cerr << "ファイルを開けませんでした。" << std::endl;
		}
		//inputfileの中に読み込んだ文字列あるよ
		std::string str_buf;

		if (inputfile.is_open())
		{
			int width = 0;
			int height = 0;
			int weight = 0;
			if (getline(inputfile, str_buf))
			{
				std::vector<std::string> splitStr = split(str_buf, ',');
				width = std::stoi(splitStr[0]);
				height = std::stoi(splitStr[1]);
				STAGE_WIDTH = width;
				STAGE_HEIGHT = height;
			}

			for (int y = 0; y < height;y++)
			{
				for (int x = 0; x < width; )
				{
					getline(inputfile, str_buf);
					for (char str : str_buf)
					{
						Point point(x, y);
						if (str == '#')
						{
							stage_[point].tile = Tile::WALL;
							stage_[point].cost = INT_MAX;
						}
						else if (str == 'S')
						{
							start_ = point;
							stage_[point].tile = Tile::ROAD;
							stage_[point].cost = 0;
						}
						else if (str == 'G')
						{
							end_ = point;
							stage_[point].tile = Tile::ROAD;
							stage_[point].cost = 0;
						}
						else if (std::isdigit(str))
						{
							weight = str - '0';
							stage_[point].cost = weight;
							stage_[point].tile = Tile::ROAD;
						}
						x++;
					}
				}
			}
		}

	}
}

/// <summary>
/// 範囲外ならtrue、範囲内ならfalse
/// </summary>
/// <param name="p"></param>
/// <returns></returns>
bool IsOutOfStage(Point p)
{
	if (p.x >= 0 && p.x < STAGE_WIDTH && p.y >= 0 && p.y < STAGE_HEIGHT)
	{
		return false;
	}
	return true;
}

/// <summary>
/// x,yどちらも偶数ならtrue
/// </summary>
/// <param name="p"></param>
/// <returns></returns>
bool IsEven(Point p)
{
	if ((p.x % 2 == 0) && (p.y % 2 == 0))
	{
		return true;
	}
	return false;
}
