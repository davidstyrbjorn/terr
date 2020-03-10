#pragma once

#include<iostream>
#include<fstream>

namespace terr {
				
	class DebugLog {
	public:
		static std::ofstream ofstream;

		template<typename T>
		static void Log(const std::string& message, std::ostream& outputstream = std::cout) {
			// Write to output stream
			outputstream << "DEBUG LOG MESSAGE SENT FROM: " << typeid(T).name() << std::endl;
			outputstream << message << '\n';

			// Write to file stream
			if (!ofstream.is_open()) {
				ofstream.open("terr_debug.txt", std::ios::trunc);
			}
			ofstream << "DEBUG LOG MESSAGE SENT FROM: " << typeid(T).name() << std::endl;
			ofstream << message << std::endl << "=======================================" << std::endl;
		}

		static void CloseDebugLog() {
			ofstream.close();
		}
	};

}