#include "NameParse.h"
#include "Trimmer.h"

std::string name_parser::parse_tag(std::ifstream &file, std::string &line){
	static std::string beg_tag = "<name>";
	static std::string end_tag = "</name>";
	
	if(line.size() == beg_tag.size()){
		std::string next_line;
		file >> next_line;
		next_line = trim_ws(next_line);
		if(next_line.find(end_tag) != -1 && next_line.size() == end_tag.size()){
			return "";
		}
		else if(next_line.find(end_tag) != -1){
			
		}
		return next_line; // It is the name.
	}
	else{
		
	}
}