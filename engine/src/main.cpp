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

int main() {

	// This goes through the config files and gets the data 
	terr::Config::ParseFromConfigFile();

	// Open the DebugLog file
	terr::DebugLog::OpenDebugLog();

	// Create window
	terr::Window window = terr::Window(400, 300, "Terr", true);

	terr::Color color;

	while (window.IsOpen()) {
	
		// Input here
		for(auto _event : window.GetEvents()){
			if(_event.eventType == terr::EventType::KEY_PRESSED){
				if (_event.key == TERR_KEY_R)
					color.r = 1;
				if (_event.key == TERR_KEY_G)
					color.g = 1;
				if (_event.key == TERR_KEY_B)
					color.b = 1;
			}
			if (_event.eventType == terr::EventType::KEY_RELEASED) {
				if (_event.key == TERR_KEY_R)
					color.r = 0;
				if (_event.key == TERR_KEY_G)
					color.g = 0;
				if (_event.key == TERR_KEY_B)
					color.b = 0;
			}
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