#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "ConfigSaver.hpp"
#include "../MenuConfig.hpp"

namespace MyConfigSaver {

    // Function to save the configuration to a file
    void SaveConfig(const std::string& filename) {
        std::ofstream configFile(filename);
        if (!configFile.is_open()) {
            std::cerr << "[Info] Error: Could not open the configuration file." << std::endl;
            return;
        }

        // Example: Save global settings to the file
        configFile << "ShowCrossHair " << CrosshairConfig::ShowCrossHair << std::endl;
        configFile << "CrossHairColor " << CrosshairConfig::CrossHairColor.Value.x << " " << CrosshairConfig::CrossHairColor.Value.y << " " << CrosshairConfig::CrossHairColor.Value.z << " " << CrosshairConfig::CrossHairColor.Value.w << std::endl;
        configFile << "CrossHairSize " << CrosshairConfig::CrossHairSize << std::endl;
        configFile << "drawDot " << CrosshairConfig::drawDot << std::endl;
        configFile << "tStyle " << CrosshairConfig::tStyle << std::endl;
        configFile << "HorizontalLength " << CrosshairConfig::HorizontalLength << std::endl;
        configFile << "VerticalLength " << CrosshairConfig::VerticalLength << std::endl;
        configFile << "drawOutLine " << CrosshairConfig::drawOutLine << std::endl;
        configFile << "drawCrossline " << CrosshairConfig::drawCrossline << std::endl;
        configFile << "drawCircle " << CrosshairConfig::drawCircle << std::endl;
        configFile << "showTargeting " << CrosshairConfig::showTargeting << std::endl;
        configFile << "CircleRadius " << CrosshairConfig::CircleRadius << std::endl;
        configFile << "TargetedColor " << CrosshairConfig::TargetedColor.Value.x << " " << CrosshairConfig::TargetedColor.Value.y << " " << CrosshairConfig::TargetedColor.Value.z << " " << CrosshairConfig::TargetedColor.Value.w << std::endl;
        configFile << "Gap " << CrosshairConfig::Gap << std::endl;
        configFile << "DynamicGap" << CrosshairConfig::DynamicGap << std::endl;
        configFile << "DotSize" << CrosshairConfig::DotSize << std::endl;


        configFile.close();
        std::cout << "[Info] Configuration saved to " << filename << std::endl;
    }

    // Function to load the configuration from a file
    void LoadConfig(const std::string& filename) {
        std::ifstream configFile(filename);
        if (!configFile.is_open()) {
            std::cerr << "[Info] Error: Could not open the configuration file." << std::endl;
            return;
        }

        std::string line;
        while (std::getline(configFile, line)) {
            std::istringstream iss(line);
            std::string key;
            if (iss >> key) {
                if (key == "ShowCrossHair") iss >> CrosshairConfig::ShowCrossHair;
                else if (key == "CrossHairColor") iss >> CrosshairConfig::CrossHairColor.Value.x >> CrosshairConfig::CrossHairColor.Value.y >> CrosshairConfig::CrossHairColor.Value.z >> CrosshairConfig::CrossHairColor.Value.w;
                else if (key == "CrossHairSize") iss >> CrosshairConfig::CrossHairSize;
                else if (key == "drawDot") iss >> CrosshairConfig::drawDot;
                else if (key == "tStyle") iss >> CrosshairConfig::tStyle;
                else if (key == "HorizontalLength") iss >> CrosshairConfig::HorizontalLength;
                else if (key == "VerticalLength") iss >> CrosshairConfig::VerticalLength;
                else if (key == "drawOutLine") iss >> CrosshairConfig::drawOutLine;
                else if (key == "Gap") iss >> CrosshairConfig::Gap;
                else if (key == "drawCrossline") iss >> CrosshairConfig::drawCrossline;
                else if (key == "drawCircle") iss >> CrosshairConfig::drawCircle;
                else if (key == "showTargeting") iss >> CrosshairConfig::showTargeting;
                else if (key == "CircleRadius") iss >> CrosshairConfig::CircleRadius;
                else if (key == "TargetedColor") iss >> CrosshairConfig::TargetedColor.Value.x >> CrosshairConfig::TargetedColor.Value.y >> CrosshairConfig::TargetedColor.Value.z >> CrosshairConfig::TargetedColor.Value.w;
                else if (key == "DynamicGap") iss >> CrosshairConfig::DynamicGap;
                else if (key == "DotSize") iss >> CrosshairConfig::DotSize;

                else if (key == "MenuStyle") iss >> MenuConfig::MenuStyle;

            }
        }

        configFile.close();
        std::cout << "[Info] Configuration loaded from " << filename << std::endl;
    }
} // namespace ConfigSaver
