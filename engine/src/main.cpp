#include"../include/core/window.h"

#include"../include/core/debug_log.h"
#include"../include/core/config.h"

#include<iostream>
#include<sstream>

int main() {

	terr::Config::ParseFromConfigFile();

	terr::Window* window = new terr::Window(800, 600, "Terr");

	terr::DebugLog::Log<terr::Config>("Some error");
	
	while (window->IsOpen()) {

		/* Input would happen here */
		
		window->Clear();
		
		/* Render would go here */
	
		window->Display();
	}
	
	terr::DebugLog::CloseDebugLog();
	delete window;
}