#pragma once

#include<iostream>
#include<fstream>

namespace terr {
				
	class DebugLog {
	public:
		static std::ofstream ofstream;

		enum Type {
			SYSTEM,
			ERROR
		};

		template<typename T>
		static void Log(const std::string& message, Type type = Type::SYSTEM) {
			// Make sure stream is open!
			if (!ofstream.is_open()) {
				OpenDebugLog();
			}
			// Write to file stream
			std::string from = "[" + std::string(typeid(T).name()) + "]";
			std::string typeLiteral = type == Type::SYSTEM ? "[SYSTEM]" : "[ERROR]";
			std::string _literal = typeLiteral + " " + from + " " + message;
			ofstream << _literal << std::endl;
		}

		static void OpenDebugLog() {
			ofstream.open("terr_log.txt", std::ios::trunc);
		}

		static void CloseDebugLog() {
			ofstream.close();
		}
	};

}