#include "RouteSearch.h"
#include "global.h"
#include <vector>
#include <cassert>
#include <cmath>
void RouteSearch::SetStartTile(Point startTile) { startTile_ = startTile; }
void RouteSearch::SetEndTile(Point endTile) { endTile_ = endTile; }
Point RouteSearch::CalculateRoute()
{
    //Point startTile_;
    //Point endTile_;
    //std::vector<Point> tiles_;
    
    //始点-終点で移動距離は求まるんじゃねえかな

    //1 から 5
    //5-1=4
    //1,2,3,4
    Point distance = Point::Sub(endTile_, startTile_);
    
    Point movement = Point{ 0,0 };
    if (distance.x != 0)
    {
        movement.x = distance.x / std::abs(distance.x);
    }
    if (distance.y != 0)
    {
        movement.y = distance.y / std::abs(distance.y);
    }
    Point ret = movement + startTile_;
    assert(ret.x >= 0);
    assert(ret.y >= 0);
    return ret;
}
