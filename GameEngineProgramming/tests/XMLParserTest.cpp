/*
 * XMLParserTest.cpp
 *
 *  Created on: Feb 9, 2017
 *      Author: uge
 */
#include "GameXMLParser.h"

#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

int main(){
	cout << "Hello Test World" << endl;
	cout << "XML PARSING TEST" << endl;
	cout << endl << endl;
	string filepath = "/home/uge/Documents/Projects/Class/4903_GE/GameEngineProgramming/GameEngineProgramming/examples/game_example.xml";
	xml_parser xp;
	xp.parse_game(filepath);



	return 0;
}
