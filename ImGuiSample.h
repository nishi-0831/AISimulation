#pragma once
#include <string>
#include <vector>
#include <list>
#include <map>
#include "ImGui/imgui.h"
//EnemyとPlayerのtileを表示する
class ImGuiSample
{
private:
	std::string name_;
	int x_;
	int y_;
	bool flag_;
	std::list<std::string> log_;
	std::vector<std::string> parameter_;

	int currentSelect_;
	std::vector<std::string> selects_;
	

public:
	void SetName(std::string name) { name_ = name; }
	void SetTile(int x, int y) 
	{ 
		x_ = x; 
		y_ = y;
	}
	void Draw() 
	{
		
		ImGui::Begin("SampleWindow");

		flag_ = ImGui::Button("button");
		
		ImGui::BeginChild("parameters");
		for(int i = 0; i < parameter_.size(); i++)
		{
			ImGui::Text("%s", parameter_[i].c_str());
		}
		ImGui::EndChild();

		ImGui::BeginChild("logs");
		
		ImGui::Text("log:%s",log_.back().c_str());
		
		ImGui::EndChild();

		if (!selects_.empty())
		{
			std::vector<const char*> items;
			for (const auto& s : selects_)
			{
				items.push_back(s.c_str());
			}
            ImGui::Combo("select:", &currentSelect_, items.data(), (int)items.size());
		}
		ImGui::Text("Select:%s", currentSelect_);

		ImGui::End();
	}
	
	

	bool IsButtonDown()
	{
		return flag_;
	}
	void Log(std::string log)
	{
		log_.push_back(log);
		if (log_.size() >= 100)
		{
			log_.pop_front();
		}
	}
	void Log(char* log)
	{
		std::string logs = log;
		Log(logs);
	}

	//同じ変数の値でも毎回push_backで追加しているので、どんどん増えていく。
	//ログをたどるのでなく最新の値を表示したいだけなら別の方法がいいかもしれない
	void AddParameter(std::string parameter)
	{
		parameter_.push_back(parameter);
		if (parameter_.size() >= 100)
		{
			parameter_.erase(parameter_.begin());
		}
	}

	void AddSelect(std::string select)
	{
		selects_.push_back(select);
	}
};

