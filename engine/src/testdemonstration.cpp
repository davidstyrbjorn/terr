
#include"../include/core/engine.h"

#include"../include/imgui/imgui.h"

#include<iostream>

class Main : public terr::TerrEngine {
public:
	Main() : TerrEngine() {

	}

	void OnUserStart() override {
		std::cout << "Program started" << std::endl;
	}

	void OnUserUpdate(float dt) {

	}

	void OnUserRender() {
		ImGui::ShowTestWindow();
	}

	void OnUserExit() {
		std::cout << "Exit caled" << std::endl;
	}

	void OnUserEvent(terr::Event event) {
	
	}

};

int main() {

	Main main;
	main.Start();

	return 0;
}