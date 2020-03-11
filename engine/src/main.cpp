#include"../include/core/window.h"

#include"../include/core/debug_log.h"
#include"../include/core/config.h"

#include<iostream>
#include<sstream>

int main() {

	// This goes through the config files and gets the data 
	terr::Config::ParseFromConfigFile();

	// Open the DebugLog file
	terr::DebugLog::OpenDebugLog();

	// Create window
	terr::Window window = terr::Window(800, 600, "Terr");
	
	while (window.IsOpen()) {

		/* Input would happen here */
		
		window.Clear();
		
		/* Render would go here */
	
		window.Display();
	}
	
	// Close the DebugLog file! (not really needed)
	terr::DebugLog::CloseDebugLog();
}