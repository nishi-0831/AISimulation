#include "RouteSearch.h"
#include "global.h"
#include <vector>

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
    Point movement = Point::Sub(endTile_, startTile_);

    //std::vector<Point> route;
    //route.push_back(startTile_.x movement.x)
    
    if ((movement.x != startTile_.x) && (movement.y != startTile_.y))
    {
        if (movement.x > 0)
        {
            startTile_.x += 1;
        }
        else
        {
            startTile_.x += -1;
        }
        if (movement.y > 0)
        {
            startTile_.y += 1;
        }
        else
        {
            startTile_.y += -1;
        }
        //route.push_back(Point::Sub(startTile_, movement));
        return startTile_;
    }
    //return route;
    /*Point point = {0,0};
    if (movement.x > 0)
    {
        point.x = 1;
    }
    else if (movement.x < 0)
    {
        point.x = -1;
    }

    if (movement.y > 0)
    {
        point.y = 1;
    }
    else if (movement.y < 0)
    {
        point.y = -1;
    }*/
    //route.push_back(Point::Add(movement,))
}
