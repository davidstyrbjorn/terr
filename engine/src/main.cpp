#include"../include/core/window.h"

#include"../include/core/debug_log.h"
#include"../include/core/config.h"
#include"../include/core/clock.h"

#include<iostream>
#include<sstream>
#include<math.h>

int main() {

	float ticker = 0.0f;

	// This goes through the config files and gets the data 
	terr::Config::ParseFromConfigFile();

	// Open the DebugLog file
	terr::DebugLog::OpenDebugLog();

	// Create window
	terr::Window window = terr::Window(400, 300, "Terr", false);

	terr::Clock clock;
	clock.reset();
	clock.start();

	int fps = 0;

	while (window.IsOpen()) {
		
		if (clock.getTicks() >= 1000) {
			std::cout << fps << std::endl;
			fps = 0;
			clock.reset();
			clock.start();
		}

		/* Input would happen here */
		
		window.Clear(sin(ticker), cos(ticker), 1);
		
		/* Render would go here */
	
		window.Display();

		fps++;
	}
	
	// Close the DebugLog file! (not really needed)
	terr::DebugLog::CloseDebugLog();
	// Important call!
	terr::Config::ClearAllocatedMemory();
}