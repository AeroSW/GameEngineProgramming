#include "LevelParseController.h"
#include <iostream>
#include "Level.h"
#include <string>

using namespace std;

int main(){
	string file = "/home/uge/Documents/Projects/Class/4903_GE/GameEngineProgramming/game_engine/files/xml/game/level/level_example.xml";
	lpcontroller * controller = lpcontroller::get_controller();
	cout << "Parsing Level" << endl;
	std::shared_ptr<level> lvl = controller->parse_lvl(file);
	cout << "Finished Parsing" << endl;
	return 0;
}