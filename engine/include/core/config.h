#pragma once

#include<map>
#include<string>

namespace terr {
	class Config {
	public:

		static void ParseFromConfigFile();
		static void ClearAllocatedMemory();
		static const float GetFloatValue(const std::string& key);
		static const std::string GetStringValue(const std::string& key);
		static const int GetIntValue(const std::string& key);

	private:
		// This is where the different config values will be actually stored
		static std::map<std::string, float>* float_values;
		static std::map<std::string, std::string>* string_values;
		static std::map<std::string, int>* int_values;

		Config(); // Private constructor
	};
}