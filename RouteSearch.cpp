#include "RouteSearch.h"
#include "global.h"
#include <vector>
#include <math.h>
void RouteSearch::SetStartTile(Point startTile) { startTile_ = startTile; }
void RouteSearch::SetEndTile(Point endTile) { endTile_ = endTile; }


std::vector<Point> RouteSearch::CalculateRoute()
{
    std::vector<Point> ret;
    Point point = startTile_;
    //end‚ÉŽŠ‚é‚Ü‚Å
    while (!(Point::Equal(point, endTile_)))
    {
        point = Point::Add(point,GetMovement(point));
        ret.push_back(point);
    }

    return ret;
}

Point RouteSearch::GetMovement()
{
    return GetMovement(startTile_);
}

Point RouteSearch::GetMovement(Point start)
{
    Point movement = Point::Sub(endTile_, start);
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
