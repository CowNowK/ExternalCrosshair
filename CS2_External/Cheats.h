#pragma once
#include "OS-ImGui/OS-ImGui.h"

namespace Cheats
{
	void RenderCrossHair(ImDrawList* drawList) noexcept;

	void Menu();
	void Run();
}

struct {
	ImFont* normal15px = nullptr;
} fonts;