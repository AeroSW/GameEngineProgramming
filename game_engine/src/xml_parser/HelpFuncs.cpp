#include "HelpFuncs.h"

std::string trim_ws(const std::string &str){
	std::string sub_str(str);
	unsigned int str_length = sub_str.size();
	while(sub_str[0] == '	' || sub_str[0] == ' '){ // Remove front whitespace
		sub_str = sub_str.substr(1, str_length);
		str_length = sub_str.size();
	}
	while(sub_str[str_length-1] == '	' || sub_str[str_length-1] == ' '){ // Remove end whitespace
		sub_str = sub_str.substr(0, str_length-1);
		str_length = sub_str.size();
	}
	return sub_str;
}

std::string parse_by_tags(std::ifstream &file, std::string &line, std::string &beg_tag, std::string &end_tag){
	if(line.size() == beg_tag.size()){ // If they are the same size.
		std::string next_line; // We need to grab the next line.
		file >> next_line;
		next_line = trim_ws(next_line); // Remove any whitespace from it.
		if(next_line.find(end_tag) != -1 && next_line.size() == end_tag.size()){
			// If the next line contains the end tag and is the same size as the
			// end tag, then, we need to return "end parsing".
			return end_tag; // Signals controller to stop parsing the file.
		}
		else if(next_line.find(end_tag) != -1){
			unsigned int endex = next_line.size() - end_tag.size();
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
			return end_tag; // Signals controller to stop parsing the file.
		}
		else if(sub_line.find(end_tag) != -1){
			unsigned int endex = sub_line.size() - end_tag.size();
			std::string info = sub_line.substr(0, endex);
			info = trim_ws(info);
			return info;
		}
		return sub_line; // Return the contents of this line.
	}
	return line;
}