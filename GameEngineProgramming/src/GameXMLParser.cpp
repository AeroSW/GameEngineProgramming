/*
 * GameXMLParser.cpp
 *
 *  Created on: Feb 6, 2017
 *      Author: uge
 */

#include "GameXMLParser.h"
#include <fstream>

std::vector<std::shared_ptr<level> > xml_parser::parse_game(std::string filename){
	uint32 num_levels = 0;
	std::vector<std::string> files;
	std::vector<std::shared_ptr<level> > game_levels;

	std::ifstream in_file(filename);
	std::string tag;
	if(in_file.is_open()){
		bool count_flag = false;
		std::string search_str;
		uint32 count = 0;
		while(!in_file.eof() || count <= num_levels){
			in_file >> std::noskipws >> tag;
			tag = trim_ws(tag);
			if(count_flag){
				search_str = "<Level_" + std::to_string(count) + ">";
			}
			if(tag.find("<Level_Count>") == 0 && !count_flag){
				num_levels = parse_level_count(in_file, tag);
				count_flag = true;
				count++;
			}
			else if(count_flag && tag.find(search_str) && count <= num_levels){
				files.push_back(parse_level_file(in_file, tag, search_str));
				count++;
			}
		}
	}
}

uint64 xml_parser::parse_level_count(std::ifstream &file, const std::string &tag){
	uint64 num_levels;
	if(tag.size() == 13){
		std::string str;
		file >> std::noskipws >> str;
		str = trim_ws(str);
		int end_tag_loc = str.find("</Level_Count>");
		if(end_tag_loc != -1){
			std::string count_str = str.substr(0, (unsigned) end_tag_loc);
			count_str = trim_ws(count_str);
			num_levels = std::stoul(count_str);
		}
		else{
			num_levels = std::stoul(str);
			file >> std::noskipws >> str; // Grab the end tag loc
		}
	}
	else{
		uint32 str_size = tag.size();
		std::string sub_str = tag.substr(13, str_size);
		sub_str = trim_ws(sub_str);
		int end_tag_loc = sub_str.find("</Level_Count>");
		if(end_tag_loc != -1){
			std::string count_str = sub_str.substr(0, (unsigned) end_tag_loc);
			count_str = trim_ws(count_str);
			num_levels = std::stoul(count_str);
		}
		else{
			num_levels = std::stoul(sub_str);
			file >> std::noskipws >> sub_str; // Grab the end tag loc
		}
	}
	return num_levels;
}

std::string xml_parser::parse_level_file(std::ifstream &file, const std::string &tag, const std::string &search_tag){
	uint32 search_length = search_tag.size();
	std::string lvl_file_path;
	if(tag.size() == search_length){

	}
	else{

	}
}

std::string xml_parser::trim_ws(const std::string &str){
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
