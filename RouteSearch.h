#pragma once
#include "Library/GameObject.h"
#include "global.h"
#include <vector>
class RouteSearch :
    public GameObject
{
private:
    //始点(S)から終点(E)を受け取る
    //SからEまでの最短経路をひとつだけ計算
    //進行不可能の壁は一旦考えない
    //各一地点はPoint構造体で表す
    Point startTile_;
    Point endTile_;

    std::vector<Point> tiles_;

public:
    //内部リンケージがある型を含むシンボルは定義されていません
    void SetStartTile(Point startTile);
    void SetEndTile(Point endTile);
    Point CalculateRoute();
    Point GetMovement();
};

