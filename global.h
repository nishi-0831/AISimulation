#pragma once  
#include <cmath>  
#include <vector>  
#include <functional>   

// �񎟌��x�N�g��(����)  
struct Point  
{  
   int x;  
   int y;  

   // a��b�𑫂���  
   static Point Add(Point a, Point b)  
   {  
       a.x += b.x;  
       a.y += b.y;  
       return a;  
   }  

   // a����b��������  
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
       // 2�_ (x1, y1) �� (x2, y2) �Ԃ̃}���n�b�^�������́A  
       // |x1 - x2| + |y1 - y2| �Ōv�Z����܂�  
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
           //�Ⴆ��(18,0)��(0,18)�������n�b�V���l�ɂȂ�Ȃ��悤��
           return hash<int>()(p.x) ^ (hash<int>()(p.y) << 1);  
       }  
   };  
}  

// �񎟌��x�N�g��(���������_��)  
struct Pointf  
{  
   float x;  
   float y;  
};  

// ��`(������)��\����  
struct Rect  
{  
   int x; // ����x  
   int y; // ����y  
   int w; // ��  
   int h; // ����  
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


const int CHA_SIZE = 32; // �L�����N�^�[�̃T�C�Y  

const int STAGE_WIDTH = 39;  
const int STAGE_HEIGHT = 21;
  
