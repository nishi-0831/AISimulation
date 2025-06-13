#pragma once
#include "Library/GameObject.h"
#include "global.h"
#include <vector>
class RouteSearch :
    public GameObject
{
private:
    //�n�_(S)����I�_(E)���󂯎��
    //S����E�܂ł̍ŒZ�o�H���ЂƂ����v�Z
    //�i�s�s�\�̕ǂ͈�U�l���Ȃ�
    //�e��n�_��Point�\���̂ŕ\��
    Point startTile_;
    Point endTile_;

    std::vector<Point> tiles_;

public:
    //���������P�[�W������^���܂ރV���{���͒�`����Ă��܂���
    void SetStartTile(Point startTile);
    void SetEndTile(Point endTile);
    Point CalculateRoute();
    Point GetMovement();
};

