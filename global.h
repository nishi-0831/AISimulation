#pragma once  
#include <cmath>  
#include <vector>  
#include <functional>   

// 二次元ベクトル(整数)  
struct Point  
{  
   int x;  
   int y;  

   // aとbを足すよ  
   static Point Add(Point a, Point b)  
   {  
       a.x += b.x;  
       a.y += b.y;  
       return a;  
   }  

   // aからbを引くよ  
   static Point Sub(Point a, Point b)  
   {  
       a.x -= b.x;  
       a.y -= b.y;  
       return a;  
   }  

   static bool Equal(Point a, Point b)  
   {  
       return (a.x == b.x && a.y == b.y);  
   }  

   static int ManhattanDistance(Point a, Point b)  
   {  
       // 2点 (x1, y1) と (x2, y2) 間のマンハッタン距離は、  
       // |x1 - x2| + |y1 - y2| で計算されます  
       return abs(a.x - b.x) + abs(a.y - b.y);  
   }  

   
   bool operator<(const Point& other) const  
   {  
       return std::tie(x, y) < std::tie(other.x, other.y);  
   } 
   bool operator==(const Point& other) const
   {
       return (x == other.x && y == other.y);
   }
};  


namespace std  
{  
   template <>  
   struct hash<Point>  
   {  
       size_t operator()(const Point& p) const  
       {  
           //例えば(18,0)と(0,18)が同じハッシュ値にならないように
           return hash<int>()(p.x) ^ (hash<int>()(p.y) << 1);  
       }  
   };  
}  

// 二次元ベクトル(浮動小数点数)  
struct Pointf  
{  
   float x;  
   float y;  
};  

// 矩形(くけい)を表すよ  
struct Rect  
{  
   int x; // 左上x  
   int y; // 左上y  
   int w; // 幅  
   int h; // 高さ  
};  

enum DIR  
{  
   UP,  
   DOWN,  
   LEFT,  
   RIGHT,  
   NONE,  
   MAX_DIR  
};  

enum class Tile  
{  
   ROAD,  
   WALL,  
   ESCAPEPOINT  
};  

static const Point moveDirArray[(int)DIR::MAX_DIR] = {  
   {0, -1},  
   {0, 1},  
   {-1, 0},  
   {1, 0},  
   {0, 0}  
};  

const Point escapePoint{18, 15};  
const std::vector<Point> wallPoint
{
    {5,5},
    {5,6},
    {5,7},
    {5,8},
    {5,9},
    {5,10},
    {5,11},
    {10,11},
    {10,12},
    {10,13},
    {10,14},
    {10,15},
    {20,5},
    {20,6},
    {20,7},
    {20,8},
    {20,9},
    {20,10},
    {20,11},
};


const int CHA_SIZE = 32; // キャラクターのサイズ  

const int STAGE_WIDTH = 39;  
const int STAGE_HEIGHT = 21;
  
