#pragma once  
#include "Library/GameObject.h"  
#include "Source/Screen.h"  
#include "global.h"  
#include <vector>  
#include <map> 
#include <unordered_map>
#include <functional>  

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
    std::unordered_map<Point, Tile> stage_;
    
    ~Stage();
    void Update() override;
    void Draw() override;
};