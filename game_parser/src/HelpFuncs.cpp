#include "HelpFuncs.h"
#include <sstream>
#include <iostream>
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
	std::cout << "Inside Parse Function" << std::endl;
	std::cout << "Line:\t" << line << std::endl;
	std::cout << "Beg:\t" << beg_tag << std::endl;
	if(line.size() == beg_tag.size()){ // If they are the same size.
		std::cout << "Should be in here" << std::endl;
		std::string next_line; // We need to grab the next line.
		std::cout << "NEXT LINE:\t" << next_line << std::endl;
		std::getline(file, next_line);
		if(next_line.find("\n")){
			std::getline(file, next_line);
		}
		std::cout << "Does it crash on getline?" << std::endl;
		next_line = trim_ws(next_line); // Remove any whitespace from it
		std::cout << "Does not crash on trim_ws" << std::endl;
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
	std::cout << "Finished with Functions" << std::endl;
	return line;
}

std::vector<double> parse_vector(const std::string &vect_str){
	static char delim = ',';
	std::stringstream ss;
	ss.str(vect_str);
	std::string buffer;
	std::vector<double> value;
	while (std::getline(ss, buffer, delim)) {
        value.push_back(std::stod(buffer));
    }
}