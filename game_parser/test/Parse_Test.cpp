#include "LevelParseIncludes.h"
#include "HelpFuncs.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){
	string filepath = "/home/uge/Documents/Projects/Class/4903_GE/GameEngineProgramming/game_parser/test_xml.xml";
	ifstream file(filepath);
	string tag;
	file >> tag;
	tag = trim_ws(tag);
	tag_parser * parser = new transforms_parser();
	std::string result = parser->parse_tag(file, tag);
	cout << "Result 1:\t" << result << endl;
	delete parser;
	parser = new scale_parser();
	result = parser->parse_tag(file, result);
	cout << "Result 2:\t" << result << endl;
	delete parser;
	return 0;
}