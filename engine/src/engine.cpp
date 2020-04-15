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

	while (window->IsOpen()) {
		// Handle events
		for (auto _event : window->GetEvents()) {
			// Pass them to the user!
			OnUserEvent(_event);
		}
		window->FlushEvents();

		deltaClock.start();

		/* Application logic should be processed here! */

		// User update method should be called!
		OnUserUpdate(1.0f); // @ Pass delta time instead of 1.0f!!

		/* Application rendering can start now! */
		window->Clear({ 0, 0, 0 }); // @ Should be a clear color, it should be a variable inside the TerrEngine class!

		// User render method should now be called!
		OnUserRender();

		window->Display();

		/* Last things before we start over! */

	}

	// Window is closed notify user!
	OnUserExit();
}
