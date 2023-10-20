#pragma once
#include "OS-ImGui/OS-ImGui.h"

namespace MenuConfig
{
	inline float ComboWidth = 100.f;
	inline float SliderWidth = 150.f;

	inline int MenuStyle = 0;
	inline bool ShowMenu = true;
	inline bool BypassOBS = false;
}

namespace CrosshairConfig
{
	inline float CrossHairSize = 75;

	inline bool ShowCrossHair = false;
	inline bool drawDot = true;
	inline bool drawCrossline = true;
	inline bool tStyle = false;
	inline bool drawCircle = false;
	inline bool drawOutLine = true;
	inline bool showTargeting = false;
	inline bool DynamicGap = false;

	inline int crosshairPreset = 0;
	inline int Gap = 8;
	inline int HorizontalLength = 6;
	inline int VerticalLength = 6;
	inline float DotSize = 1.0f;
	inline float CircleRadius = 3.f;
	
	inline ImColor CrossHairColor = ImColor(0, 255, 0, 255);
	inline ImColor TargetedColor = ImColor(255, 0, 0, 255);
}