#pragma once

#include"window.h" // window
#include"clock.h" // Delta-time
#include"debug_log.h"
#include"config.h"
#include"color.h"

namespace terr {
	class TerrEngine {
	public:
		// Constructor
		TerrEngine();

		// Destructor
		~TerrEngine();

		void Start();

		virtual void OnUserStart() = 0;
		virtual void OnUserUpdate(float dt) = 0;
		virtual void OnUserRender() = 0;
		virtual void OnUserExit() = 0;
		virtual void OnUserEvent(terr::Event event) = 0;

	private:
		terr::Window* window;
		terr::Clock deltaClock;
	};
}

/*

class Application : TerrEngine{
public:
	
	// User-end methods
	void OnUserStart();
	void OnUserUpdate(float dt);
	void OnUserRender();
	void OnUserExit();
}

*/