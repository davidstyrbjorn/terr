#pragma once

#include<map>
#include<string>

namespace terr {
	class Config {
	public:

		static void ParseFromConfigFile();
		static const float GetFloatValue(const std::string& key);
		static const std::string GetStringValue(const std::string& key);

	private:
		// This is where the different config values will be actually stored
		static std::map<std::string, float> floatValues;
		static std::map<std::string, std::string> stringValues;
		static std::map<std::string, int> intValues;

		Config(); // Private constructor
	};
}