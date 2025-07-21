#include "ImGuiSample.h"

class Entity
{
private:
public :
	int id;
	//void Show(const char* name) { ImGui::InputInt(name, &id); }
};
REFL_AUTO(
	type(Entity),
	field(id)
)

class Plane : public Entity
{
public:
	int hp;
	float speed;
};
REFL_AUTO(
	type(Plane,bases<Entity>),
	field(hp),
	field(speed)
)

namespace ImGuiSample
{

}

//struct ShowVisitor
//{
//	template <typename T>
//	void operator()(const char* name, const T& value)
//	{
//		ImGuiSample::Show(name, value);
//	}
//};


//void ImGuiSample::Show(const char* name, Entity* point)
//{
//	ImGui::InputInt(name, &(point->id));
//}

void ImGuiSample::Show(const char* name, Plane* plane)
{
	//ImGui::InputInt(name)
}

void ImGuiSample::Show(const char* name, Point* point)
{
	int array[2] = { point->x,point->y };
	if (ImGui::InputInt2(name, array, ImGuiInputTextFlags_CharsDecimal || ImGuiInputTextFlags_EnterReturnsTrue))
	{
		point->x = array[0];
		point->y = array[1];
	}
}

void ImGuiSample::Show(const char* name, int* val)
{
	ImGui::InputInt(name, val);
}
void ImGuiSample::Show(const char* name, float* val)
{
	ImGui::InputFloat(name, val);
}
//template<typename EntityT>
//void operator()(const char* name, const EntityT& value)
//{
//	if (std::is_base_of<Entity, EntityT>::value == true)
//	{
//		//()(name, value);
//		//std::cout << name << " " << value;
//		//std::cout << std::endl;
//		show_visitor(name, value);
//	}
//}