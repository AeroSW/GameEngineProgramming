#include "LevelParse.h"
#include "Trimmer.h"

std::string lvl_parse::parse_tag(std::ifstream &file, std::string line){
	static std::string beg_tag = "<layer>";
	static std::string end_tag = "</layer>";
	if(line.size() == beg_tag.size()){ // If they are the same size.
		std::string next_line; // We need to grab the next line.
		file >> next_line;
		next_line = trim_ws(next_line); // Remove any whitespace from it.
		if(next_line.find(end_tag) != -1 && next_line.size() == end_tag.size()){
			// If the next line contains the end tag and is the same size as the
			// end tag, then, we need to return "end parsing".
			return "end parsing"; // Signals controller to stop parsing the file.
		}
		else if(next_line.find(end_tag) != -1){
			uint32 endex = next_line.size() - end_tag.size();
			std::string info = next_line.substr(0, endex);
			info = trim_ws(info);
			return info;
		}
		return next_line; // Return the contents of this line.
	}
	else{
		std::string sub_line = line.substr(beg_tag.size(),line.size());
		sub_line = trim_ws(sub_line); // Remove any whitespace from it.
		if(sub_line.find(end_tag) != -1 && sub_line.size() == end_tag.size()){
			// If the next line contains the end tag and is the same size as the
			// end tag, then, we need to return "end parsing".
			return "end parsing"; // Signals controller to stop parsing the file.
		}
		else if(sub_line.find(end_tag) != -1){
			uint32 endex = sub_line.size() - end_tag.size();
			std::string info = sub_line.substr(0, endex);
			info = trim_ws(info);
			return info;
		}
		return sub_line; // Return the contents of this line.
	}
	return line;
}