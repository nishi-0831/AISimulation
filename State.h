#pragma once
#include <string>
#include <functional>
class State
{
public:
	//�f�o�b�O�ŕ\�����邽�߂̕�����
	std::string name_;
	//���ʎq
	unsigned int id_;
	//�֐�
	std::function<void(void)> func_;
public:
	State();
	State(std::string name, unsigned int id, std::function<void(void)> func);
	~State();

	bool operator==(const State& rhs) const
	{
		return id_ == rhs.id_;
	}
	bool operator<(const State& rhs) const
	{
		return id_ < rhs.id_;
	}

	void SetFunc(std::function<void(void)> &func)
	{
		func_ = func;
	}
	const std::function<void(void)> GetFunc() { func_; }
	int ID() { return id_; }


};

