#pragma once  
#include "Library/GameObject.h"  
#include "Source/Screen.h"  
#include "global.h"  
#include <vector>  
#include <map> 
#include <unordered_map>
#include <functional>  
#include "Route.h"
class Stage : public GameObject
{
private:
    Stage();
    static Stage* instance_;
public:
    static Stage* GetInstance()
    {
        if (!instance_)
        {
            instance_ = new Stage();
        }
        return instance_;
    }
    std::unordered_map<Point, Node> stage_;
    std::vector<std::vector<int>> distances_;
    std::vector<RouteTile> routeTiles_;
    ~Stage();
    void Update() override;
    void Draw() override;
    void DrawDistance();
    bool IsWall(Point point);
    
    void Dig();
    void DigRecursive(Point start);

    Point GetRandRoadPos();

    void LoadMapData();
    Point start_;
    Point end_;
};