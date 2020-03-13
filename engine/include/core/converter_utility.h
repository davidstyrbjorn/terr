#pragma once

#include<string>
#include<sstream>

namespace terr {

	class ConverterUtility {
	public:
		// Check if string is either int, float etc
		// Tested for: int and float
		template<typename T>
		static bool IsType(std::string string) {
			std::istringstream iss(string);
			T _t;
			iss >> std::noskipws >> _t;
			// Check the entire string was consumed and if either failbit or badbit is set
			return iss.eof() && !iss.fail();
		}
	};

}