#include "RouteSearch.h"
#include "global.h"
#include <vector>
#include <math.h>
void RouteSearch::SetStartTile(Point startTile) { startTile_ = startTile; }
void RouteSearch::SetEndTile(Point endTile) { endTile_ = endTile; }
Point RouteSearch::CalculateRoute()
{
    return Point::Add(startTile_, GetMovement());
}

Point RouteSearch::GetMovement()
{
    Point movement = Point::Sub(endTile_, startTile_);
    Point ret{ 0,0 };
    if ((movement.x != 0))
    {
        int x = movement.x / abs(movement.x);
        ret.x = x;
    }
    if ((movement.y != 0))
    {
        int y = movement.y / abs(movement.y);
        ret.y = y;
    }
    return ret;
}
