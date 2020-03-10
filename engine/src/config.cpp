#include "..\include\core\config.h"

#include<fstream>
#include<iostream>
#include<vector>
#include<algorithm>
#include<regex>

#include"../include/core/converter_utility.h"
#include"../include/core/debug_log.h"

// Initalize static members
std::map<std::string, float> terr::Config::floatValues = std::map<std::string, float>();
std::map<std::string, std::string> terr::Config::stringValues = std::map<std::string, std::string>();
std::map<std::string, int> terr::Config::intValues = std::map<std::string, int>();

void terr::Config::ParseFromConfigFile()
{
	// Parse lines from the config file
	std::ifstream ofstream("terr_config.txt", std::ios::beg);

	std::string line;
	std::vector<std::string> lines;

	// Get all the lines from the file and store inside a vector 
	while (std::getline(ofstream, line)) {
		if (!line.empty()) {
			lines.push_back(line);
		}
	} 
	
	// Iterate over the vector and use regex to extract the stuff
	for (int i = 1; i < lines.size() - 1; i++) {
		std::string x = lines[i];
		try {
			std::regex re("<(.*)>(.*)</(.*)>");
			std::smatch match;
			if (std::regex_search(x, match, re) && match.size() == 4 && match.str(1) == match.str(3)) {				
				// Check if string is integer using the converter utility 
				if (terr::ConverterUtility::IsType<int>(match.str(2))) {
					intValues.insert(std::make_pair<std::string, int>(match.str(1), std::stoi(match.str(2))));
				}
				// Check if string is float using the converter utility
				else if (terr::ConverterUtility::IsType<float>(match.str(2))) {
					floatValues.insert(std::make_pair<std::string, float>(match.str(1), std::stof(match.str(2))));
				}
				// None of the checks passed, it's a string value
				else {
					stringValues.insert(std::make_pair<std::string, std::string>(match.str(1), match.str(2)));
				}
			}
			else {
				std::string errorMsg = "Config parsing error! on line: " + x;
				DebugLog::Log<terr::Config>(errorMsg);
			}
		}
		catch (std::regex_error& err) {
			std::cout << "REGEX ERROR: " << err.what() << std::endl;
		}
	}
}

const float terr::Config::GetFloatValue(const std::string& key)
{
	return floatValues[key];
}

const std::string terr::Config::GetStringValue(const std::string& key)
{
	return stringValues[key];
}
