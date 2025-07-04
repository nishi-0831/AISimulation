#pragma once
#include <string>
#include <functional>
class State
{
public:
	//デバッグで表示するための文字列
	std::string name_;
	//識別子
	unsigned int id_;
	//関数
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

