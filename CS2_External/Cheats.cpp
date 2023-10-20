#include <string>
#include "Cheats.h"
#include "Render.hpp"
#include "MenuConfig.hpp"
#include "Utils/ConfigMenu.hpp"
#include "Utils/ConfigSaver.hpp"

void Cheats::Menu()
{
	ImGui::Begin("External Crosshair Tool",nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse);
	
	{
		ImGui::BeginTabBar("TabBar", ImGuiTabBarFlags_Reorderable | ImGuiTabBarFlags_FittingPolicyScroll | ImGuiTabBarFlags_NoTooltip);

		//Crosshair
		if (ImGui::BeginTabItem("Crosshair"))
		{

			ImGui::Checkbox("Enabled", &CrosshairConfig::ShowCrossHair);
			ImGui::Checkbox("Bypass OBS", &MenuConfig::BypassOBS);

			ImGui::SetNextItemWidth(MenuConfig::ComboWidth + 50);
			if (ImGui::Combo("Presets", &CrosshairConfig::crosshairPreset, "Custom\0Dot\0Circle Dot 1\0Circle Dot 2\0Crosshair Small\0Crosshair Medium\0Crosshair Dot"))
				Render::UpdateCrosshairPreset(CrosshairConfig::crosshairPreset);

			ImGui::Text("Crosshair Color");
			ImGui::SameLine();
			ImGui::ColorEdit4("##CrossHairColor", reinterpret_cast<float*>(&CrosshairConfig::CrossHairColor), ImGuiColorEditFlags_NoInputs);

			ImGui::Checkbox("Center Dot", &CrosshairConfig::drawDot);
			if (CrosshairConfig::drawDot)
			{
				ImGui::SliderFloat("Dot Size", &CrosshairConfig::DotSize, 1.f, 50.f, "%.f");
			}

			ImGui::Checkbox("Outline", &CrosshairConfig::drawOutLine);
			ImGui::Checkbox("Crossline", &CrosshairConfig::drawCrossline);
			if (CrosshairConfig::drawCrossline)
			{
				ImGui::SliderInt("Horizontal Length", &CrosshairConfig::HorizontalLength, 1, 100, "%d");
				ImGui::SliderInt("Vertical Length", &CrosshairConfig::VerticalLength, 1, 100, "%d");
				ImGui::SliderInt("Gap", &CrosshairConfig::Gap, 1, 50, "%d");
				ImGui::Checkbox("T Style", &CrosshairConfig::tStyle);
			}

			ImGui::Separator();
			ImGui::Checkbox("Circle", &CrosshairConfig::drawCircle);
			if(CrosshairConfig::drawCircle)
				ImGui::SliderFloat("Circle Radius", &CrosshairConfig::CircleRadius, 0.0f, 50.0f, "%.1f");

			ImGui::Separator();
			ImGui::Checkbox("Target Crosshair", &CrosshairConfig::showTargeting);
			ImGui::SameLine();
			ImGui::ColorEdit4("##CrosshairColor", reinterpret_cast<float*>(&CrosshairConfig::TargetedColor), ImGuiColorEditFlags_NoInputs);

			ImGui::EndTabItem();
		}

		// Config
		ConfigMenu::RenderConfigMenu();

	}ImGui::End();
}

void Cheats::RenderCrossHair(ImDrawList* drawList) noexcept
{
	if (!CrosshairConfig::ShowCrossHair)
		return;

	Render::DrawCrossHair(drawList, ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2), ImGui::ColorConvertFloat4ToU32(CrosshairConfig::CrossHairColor));
}

void Cheats::Run()
{	
	// Show menu
	static DWORD lastTick = 0; 
	DWORD currentTick = GetTickCount(); 
	if ((GetAsyncKeyState(VK_DELETE) & 0x8000) && currentTick - lastTick >= 150){
		MenuConfig::ShowMenu = !MenuConfig::ShowMenu;
		lastTick = currentTick; 
	}
	if(MenuConfig::ShowMenu)
		Menu();

	RenderCrossHair(ImGui::GetBackgroundDrawList());	
}
