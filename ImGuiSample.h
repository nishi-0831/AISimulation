#pragma once
#include <string>
#include "ImGui/imgui.h"
//Enemy‚ÆPlayer‚Ìtile‚ð•\Ž¦‚·‚é
class ImGuiSample
{
private:
	std::string name_;
	int x_;
	int y_;
public:
	void SetName(std::string name) { name_ = name; }
	void SetTile(int x, int y) 
	{ 
		x_ = x; 
		y_ = y;
	}
	void Draw() const
	{
		ImGui::Begin("SampleWindow");

		ImGui::Text("Name:%s", name_.c_str());
		ImGui::Text("Tile:(%d,%d", x_, y_);

		ImGui::End();
	}
};

