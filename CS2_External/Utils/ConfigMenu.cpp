#include "ConfigMenu.hpp"
#include "../MenuConfig.hpp"
#include "ConfigSaver.hpp"
#include <filesystem>
#include <string>

namespace ConfigMenu {

	void RenderConfigMenu() {
		// Config
		if (ImGui::BeginTabItem("Config"))
		{
			ImGui::Columns(2, nullptr, false);
			ImGui::SetColumnOffset(1, 170.0f);

			ImGui::PushItemWidth(160.0f);

			static char configNameBuffer[128] = "NewConfig";

			static int selectedConfig = -1;

			const std::string configDir = std::filesystem::current_path().string();
			static std::vector<std::string> configFiles;
			std::vector<const char*> configFilesCStr;

			configFiles.clear();
			for (const auto& entry : std::filesystem::directory_iterator(configDir))
			{
				if (entry.is_regular_file() && entry.path().extension() == ".config")
				{
					configFiles.push_back(entry.path().filename().string());
				}
			}

			// 将vector转到const char*数组
			for (const auto& file : configFiles)
			{
				configFilesCStr.push_back(file.c_str());
			}

			// 创建列表框并载入配置文件数组
			ImGui::ListBox("##ConfigFiles", &selectedConfig, configFilesCStr.data(), configFilesCStr.size());

			ImGui::NextColumn();
			ImGui::PushItemWidth(100.0f);

			if (ImGui::Button("Load Selected", { 100.0f, 25.0f }) && selectedConfig >= 0 && selectedConfig < configFiles.size())
			{
				std::string selectedConfigFile = configFiles[selectedConfig];
				MyConfigSaver::LoadConfig(selectedConfigFile);
				// Because the style is switched when Combo is activated, the style should be manually updated here
				// Render::UpdateStyle(MenuConfig::MenuStyle);
				// Umm...Some problem occured
			}

			if (ImGui::Button("Save Selected", { 100.0f, 25.0f }) && selectedConfig >= 0 && selectedConfig < configFiles.size())
			{
				std::string selectedConfigFile = configFiles[selectedConfig];
				MyConfigSaver::SaveConfig(selectedConfigFile);
			}

			if (ImGui::Button("Delete Selected", { 100.0f, 25.0f }) && selectedConfig >= 0 && selectedConfig < configFiles.size())
				ImGui::OpenPopup("##reallyDelete");

			if (ImGui::BeginPopup("##reallyDelete"))
			{
				ImGui::TextUnformatted("Are you sure?");
				if (ImGui::Button("No", { 45.0f, 0.0f }))
					ImGui::CloseCurrentPopup();
				ImGui::SameLine();
				if (ImGui::Button("Yes", { 45.0f, 0.0f }))
				{
					// Delete
					std::string selectedConfigFile = configFiles[selectedConfig];
					std::string fullPath = configDir + "/" + selectedConfigFile;
					if (std::remove(fullPath.c_str()) == 0)
					{
						configFiles.erase(configFiles.begin() + selectedConfig);
						selectedConfig = -1;
					}
					else
					{
					}
					ImGui::CloseCurrentPopup();
				}
			ImGui::EndPopup();
			}

			if (ImGui::Button("Reset Config", { 100.0f, 25.0f }))
				ImGui::OpenPopup("##reallyReset");
			if (ImGui::BeginPopup("##reallyReset"))
			{
				ImGui::TextUnformatted("Are you sure?");
				if (ImGui::Button("No", { 45.0f, 0.0f }))
					ImGui::CloseCurrentPopup();
				ImGui::SameLine();
				if (ImGui::Button("Yes", { 45.0f, 0.0f }))
				{
					ConfigMenu::ResetToDefault();
					ImGui::CloseCurrentPopup();
				}	
				ImGui::EndPopup();
			}
			ImGui::Columns(1);

			ImGui::Separator();
			ImGui::InputText(" ", configNameBuffer, sizeof(configNameBuffer));
			ImGui::SameLine();
			if (ImGui::Button("Create Config", { 100.0f, 25.0f }))
			{
				std::string configFileName = std::string(configNameBuffer) + ".config";
				MyConfigSaver::SaveConfig(configFileName);
			}

			ImGui::EndTabItem();
		}
	}

	void ResetToDefault() {
		MenuConfig::ShowMenu = true;
		CrosshairConfig::ShowCrossHair = false;
		CrosshairConfig::CrossHairColor = ImColor(0, 255, 0, 255);
		CrosshairConfig::CrossHairSize = 75;
		CrosshairConfig::drawDot = true;
		CrosshairConfig::tStyle = false;
		CrosshairConfig::HorizontalLength = 6;
		CrosshairConfig::VerticalLength = 6;
		CrosshairConfig::drawOutLine = true;
		CrosshairConfig::Gap = 8;
		CrosshairConfig::drawCrossline = true;
		CrosshairConfig::drawCircle = false;
		CrosshairConfig::showTargeting = false;
		CrosshairConfig::TargetedColor = ImColor(255, 0, 0, 255);
		CrosshairConfig::CircleRadius = 3.f;
		CrosshairConfig::DynamicGap = false;
		CrosshairConfig::DotSize = 1.0f;
	}
}
