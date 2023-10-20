#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <map>
#include <Windows.h>
#include "MenuConfig.hpp"
#include "OS-ImGui/imgui/imgui.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "OS-ImGui/imgui/imgui_internal.h"

namespace Render
{

	void DrawCrossHair(ImDrawList* drawList, const ImVec2& pos, ImU32 color) noexcept
	{
		int BorderWidth = 2;
		int DotSize = 1;
		int gap = CrosshairConfig::Gap / 2;

		int outlineGap = gap - 1;

		ImVec2 offset1{ CrosshairConfig::DotSize,CrosshairConfig::DotSize };
		ImVec2 offset2{ CrosshairConfig::DotSize + 1,CrosshairConfig::DotSize + 1 };

		/*
		===== Outline =====
		*/
		if (CrosshairConfig::drawOutLine)
		{
			//dot
			if (CrosshairConfig::drawDot)
				drawList->AddRectFilled(ImVec2(pos.x - offset1.x, pos.y - offset1.y), ImVec2(pos.x + offset2.x, pos.y + offset2.y), color & IM_COL32_A_MASK);

			if (CrosshairConfig::drawCrossline)
			{
				//left
				drawList->AddRectFilled(ImVec2(pos.x - (outlineGap + BorderWidth + CrosshairConfig::HorizontalLength), pos.y - 1), ImVec2(pos.x - outlineGap, pos.y + 2), color & IM_COL32_A_MASK);
				//right
				drawList->AddRectFilled(ImVec2(pos.x + (outlineGap + DotSize), pos.y - 1), ImVec2(pos.x + (outlineGap + DotSize + BorderWidth + CrosshairConfig::HorizontalLength), pos.y + 2), color & IM_COL32_A_MASK);
				//top
				if (!CrosshairConfig::tStyle)
					drawList->AddRectFilled(ImVec2(pos.x - 1, pos.y - (outlineGap + BorderWidth + CrosshairConfig::VerticalLength)), ImVec2(pos.x + 2, pos.y - outlineGap), color & IM_COL32_A_MASK);
				//bottom
				drawList->AddRectFilled(ImVec2(pos.x - 1, pos.y + outlineGap + DotSize), ImVec2(pos.x + 2, pos.y + (outlineGap + DotSize + BorderWidth + CrosshairConfig::VerticalLength)), color & IM_COL32_A_MASK);
			}
						
			//circle
			if (CrosshairConfig::drawCircle)
				drawList->AddCircle(ImVec2(pos.x, pos.y), CrosshairConfig::CircleRadius, color & IM_COL32_A_MASK, 0, 3.0f);
		}

		/*
		===== Crosshair =====
		*/
		// dot
		if (CrosshairConfig::drawDot)
			drawList->AddRectFilled(ImVec2(pos.x - offset1.x + DotSize, pos.y - offset1.y + DotSize), ImVec2(pos.x + offset1.x, pos.y + offset1.y), color);

		if (CrosshairConfig::drawCrossline)
		{
			// left
			drawList->AddRectFilled(ImVec2(pos.x - (gap + CrosshairConfig::HorizontalLength), pos.y), ImVec2(pos.x - gap, pos.y + 1), color);
			// right
			drawList->AddRectFilled(ImVec2(pos.x + gap + DotSize, pos.y), ImVec2(pos.x + (gap + DotSize + CrosshairConfig::HorizontalLength), pos.y + 1), color);
			// top
			if (!CrosshairConfig::tStyle)
				drawList->AddRectFilled(ImVec2(pos.x, pos.y - (gap + CrosshairConfig::VerticalLength)), ImVec2(pos.x + 1, pos.y - gap), color);
			// bottom
			drawList->AddRectFilled(ImVec2(pos.x, pos.y + gap + DotSize), ImVec2(pos.x + 1, pos.y + (gap + DotSize + CrosshairConfig::VerticalLength)), color);
		}
		
		// circle
		if (CrosshairConfig::drawCircle)
			drawList->AddCircle(ImVec2(pos.x, pos.y), CrosshairConfig::CircleRadius, color, 0, 1.0f);
	}

	// Update window style color
	void UpdateStyle(int Style)
	{
		switch (Style) {
		case 0:
			ImGui::StyleColorsDark();
			break;
		case 1:
			ImGui::StyleColorsEnemyMouse();
			break;
		case 2:
			ImGui::StyleColorsClassic();
			break;
		}
	}

	// Update crosshair preset
	void UpdateCrosshairPreset(int style)
	{
		switch (style) {
		case 1:
			CrosshairConfig::drawDot = true;
			CrosshairConfig::DotSize = 2;
			CrosshairConfig::drawOutLine = true;
			CrosshairConfig::drawCrossline = false;
			CrosshairConfig::drawCircle = false;
			CrosshairConfig::showTargeting = true;
			break;
		case 2:
			CrosshairConfig::drawDot = true;
			CrosshairConfig::DotSize = 2;
			CrosshairConfig::drawOutLine = true;
			CrosshairConfig::drawCrossline = false;
			CrosshairConfig::drawCircle = true;
			CrosshairConfig::CircleRadius = 10.f;
			CrosshairConfig::showTargeting = true;
			break;
		case 3:
			CrosshairConfig::drawDot = true;
			CrosshairConfig::DotSize = 1;
			CrosshairConfig::drawOutLine = true;
			CrosshairConfig::drawCrossline = true;
			CrosshairConfig::HorizontalLength = 5;
			CrosshairConfig::VerticalLength = 5;
			CrosshairConfig::Gap = 18;
			CrosshairConfig::tStyle = false;
			CrosshairConfig::drawCircle = true;
			CrosshairConfig::CircleRadius = 10.f;
			CrosshairConfig::showTargeting = true;
			break;
		case 4:
			CrosshairConfig::drawDot = true;
			CrosshairConfig::DotSize = 1;
			CrosshairConfig::drawOutLine = true;
			CrosshairConfig::drawCrossline = true;
			CrosshairConfig::HorizontalLength = 5;
			CrosshairConfig::VerticalLength = 5;
			CrosshairConfig::Gap = 1;
			CrosshairConfig::tStyle = false;
			CrosshairConfig::drawCircle = false;
			CrosshairConfig::showTargeting = true;
			break;
		case 5:
			CrosshairConfig::drawDot = false;
			CrosshairConfig::drawOutLine = true;
			CrosshairConfig::drawCrossline = true;
			CrosshairConfig::HorizontalLength = 7;
			CrosshairConfig::VerticalLength = 7;
			CrosshairConfig::Gap = 10;
			CrosshairConfig::tStyle = false;
			CrosshairConfig::drawCircle = false;
			CrosshairConfig::showTargeting = true;
			break;
		case 6:
			CrosshairConfig::drawDot = true;
			CrosshairConfig::DotSize = 2;
			CrosshairConfig::drawOutLine = true;
			CrosshairConfig::drawCrossline = true;
			CrosshairConfig::HorizontalLength = 8;
			CrosshairConfig::VerticalLength = 8;
			CrosshairConfig::Gap = 20;
			CrosshairConfig::tStyle = false;
			CrosshairConfig::drawCircle = false;
			CrosshairConfig::showTargeting = true;
			break;
		default:
			break;
		}
	}

	// Convert RGBA to ImVec4
	// Why not use "ImColor()"? Because I forgot about this.
	ImVec4 rgba2ImVec(int r, int g, int b, int a)
	{
		ImVec4 color;
		color.x = static_cast<float>(r) / 255.0f;
		color.y = static_cast<float>(g) / 255.0f;
		color.z = static_cast<float>(b) / 255.0f;
		color.w = static_cast<float>(a) / 255.0f;

		return color;
	}
}