#include "Parser.h"
#include "Level.h"
#include <string>
#include <memory>
#include <iostream>
using namespace std;
int main(){
	const string file("/home/uge/Documents/Projects/Class/4903_GE/GameEngineProgramming/tinyxml_parser/files/level_example.xml");
	std::shared_ptr<level> lvl = parse_level(file);
	std::cout << "Made it out" << std::endl;
	std::vector<shared_ptr<camera> > * cams = lvl->get_cams();
	std::vector<shared_ptr<mesh> > * meshes = lvl->get_meshes();
	std::vector<shared_ptr<light> > * lights = lvl->get_lights();
	unsigned int ms = meshes->size();
	unsigned int ls = lights->size();
	unsigned int cs = cams->size();
	std::cout << "cam count:   " << cs << std::endl;
	std::cout << "light count: " << ls << std::endl;
	std::cout << "mesh count:  " << ms << std::endl;
	std::cout << (*cams)[0]->get_name() << std::endl;
	std::cout << (*lights)[0]->get_name() << std::endl;
	std::cout << (*meshes)[0]->get_name() << std::endl;
	return 0; // Memory Error Occurs on Test Ending
}