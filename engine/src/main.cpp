#include"../include/window.h"

#include"../include/debug_log.h"

#include<iostream>

int main() {

	terr::Window* window = new terr::Window(800, 600, "Terr");
	
	while (window->IsOpen()) {
	
		/* Input would happen here */
	
		window->Clear();
	
		/* Render would go here */
	
		window->Display();
	}
	
	terr::CloseDebugLog();
	delete window;
}