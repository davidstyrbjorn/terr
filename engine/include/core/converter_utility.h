#pragma once

#include<string>
#include<sstream>

namespace terr {

	class ConverterUtility {
	public:
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