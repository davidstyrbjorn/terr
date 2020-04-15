#include "..\include\core\engine.h"

#define GLEW_STATIC
#include<GL/glew.h>

terr::TerrEngine::TerrEngine()
{
	// This goes through the config files and gets the data 
	terr::Config::ParseFromConfigFile();

	// Open the DebugLog file
	terr::DebugLog::OpenDebugLog();

	// Create window 
	window = new terr::Window(800, 600, "terr Window", false);

	// Initalize GLEW!
	if (glewInit() != GLEW_OK) {
		terr::DebugLog::Log<terr::TerrEngine>("Failed to initalize GLEW!");
	}
	//bgColor
	clearColor = Color(0, 0, 0, 1);
}

terr::TerrEngine::~TerrEngine()
{
	delete window;

	terr::DebugLog::CloseDebugLog();
	terr::Config::ClearAllocatedMemory();
}

void terr::TerrEngine::Start()
{
	this->OnUserStart();
	
	float deltaTime = 0;

	float temp = 0;

	deltaClock.start();

	while (window->IsOpen()) {
		
		// Record time
		temp = deltaClock.getTicks();
		             
		// Handle events
		for (auto _event : window->GetEvents()) {
			// Pass them to the user!
			OnUserEvent(_event);
		}
		window->FlushEvents();

		/* Application logic should be processed here! */

		// User update method should be called!
		OnUserUpdate(deltaTime/1000.0f); // Send deltaTime as seconds /1000.0f 

		/* Application rendering can start now! */
		
		window->Clear(clearColor); // @ Should be a clear color, it should be a variable inside the TerrEngine class!

		// User render method should now be called!
		OnUserRender();

		window->Display();
		


		/* Last things before we start over! */

		// Calculate delta time and reset deltaClock
		deltaTime = deltaClock.getTicks() - temp;
		deltaClock.reset();
	}

	// Window is closed notify user!
	OnUserExit();
}
