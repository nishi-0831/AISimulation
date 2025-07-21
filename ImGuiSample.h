#pragma once
#include <string>
#include "ImGui/imgui.h"
#include "global.h"
#include "visit_struct/visit_struct.hpp"
#include <refl.hpp>
#include "Player.h"
#include <type_traits>
#include <assert.h>
#include <typeinfo>

REFL_AUTO(
	type(Point),
	field(x),
	field(y)
)

class Entity;
class Plane;
//Enemy‚ÆPlayer‚Ìtile‚ð•\Ž¦‚·‚é
namespace ImGuiSample
{
	void Show(const char* name, Entity* point);
	void Show(const char* name, Plane* point);
	void Show(const char* name, Point* point);
	void Show(const char* name, int* val);
	void Show(const char* name, float* val);
	template<typename T>
	void ShowInspector(T* val, const char* name = "");

	
};

template <typename T>
struct has_custom_show {
private:
    template <typename U>
    static auto test(int) -> decltype(ImGuiSample::Show(std::declval<const char*>(), std::declval<U>()), std::true_type{});

    template <typename>
    static std::false_type test(...);

    using V = refl::trait::remove_qualifiers_t<T>;
public:
    static constexpr bool value = decltype(test<V>(0))::value;
};

template <typename T>
void ImGuiSample::ShowInspector(T* val, const char* name)
{
	static_assert(std::is_pointer_v<T*>);
	static_assert(refl::is_reflectable<T>());

	constexpr refl::descriptor::type_descriptor<T> type = refl::reflect<T>();
	//refl::descriptor::has_bases<type>

	if (type.bases.size > 0)
	{
		refl::util::for_each(type.bases, [&](auto&& base)
			{
				using BaseType = typename decltype(base)::type;
				ImGuiSample::ShowInspector(static_cast<BaseType*>(val), BaseType::name);
			});
	}

	//ImGui::Text(typeid(type).name());
	if constexpr (has_custom_show<T*>::value)
	{
		ImGuiSample::Show(name, val);
	}
	else
	{
		refl::util::for_each(type.members, [&](auto&& member)
		{
			ImGui::Text(name);
			ImGui::Separator();
			ImGuiSample::ShowInspector(&(member(*val)), member.name.c_str());
		});
	}
	
	
}

