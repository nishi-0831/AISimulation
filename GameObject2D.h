#pragma once
#include "Library/GameObject.h"
#include "global.h"
#include <array>

class GameObject2D :
	public GameObject
{
protected:
	Point pos_;
	int hImage_;
	Point tile_;
	DIR nowDir_;
	int nowFrame_ = 0;// ���݂̃A�j���[�V�����t���[��
	int index_ = 0; 
	float animTimer_;
	std::array<int,4> animTip_;//�A�j���[�V�����̃R�}�ԍ�
	float animInterval_ = 0.3f;
	int imageSize_;
	std::array<int,(int)DIR::MAX_DIR> dirArray_;
public:
	GameObject2D();
	~GameObject2D();
	virtual void SetDir() {};
	void TurnLeft();
	void TurnRight();
	void TurnBack();
	//�X�e�[�W�͈̔͊O��
	bool IsOutOfStage(int x,int y);
	virtual void Anim() {};
	virtual void Move() {};
	virtual void Update() override;
	virtual void Draw() override;
};

