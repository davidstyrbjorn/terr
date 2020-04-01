#include"../include/core/window.h"

#include"../include/core/debug_log.h"
#include"../include/core/config.h"
#include"../include/core/clock.h"
#include"../include/core/vec3.h"
#include"../include/core/color.h"
#include"../include/core/Input.h"

#include<iostream>
#include<sstream>
#include<math.h>

#define GLEW_STATIC
#include<GL/glew.h>

int main() {

	// This goes through the config files and gets the data 
	terr::Config::ParseFromConfigFile();

	// Open the DebugLog file
	terr::DebugLog::OpenDebugLog();

	// Create window
	terr::Window window = terr::Window(900, 630, "Terr", false);

	// GLEW init
	if (glewInit() != GLEW_OK) {
		std::cout << "glew failed to init" << std::endl;
	}

	terr::Color color;

	while (window.IsOpen()) {
	
		// Input here
		for(auto _event : window.GetEvents()){

		}
		window.FlushEvents();

		// Program logic
		

		// Render starts here
		window.Clear(color);
		

		window.Display();
	}
	
	// Close the DebugLog file! (not really needed)
	terr::DebugLog::CloseDebugLog();
	// Important call!
	terr::Config::ClearAllocatedMemory();
}