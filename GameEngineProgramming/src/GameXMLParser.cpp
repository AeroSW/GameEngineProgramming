/*
 * GameXMLParser.cpp
 *
 *  Created on: Feb 6, 2017
 *      Author: uge
 */

#include "GameXMLParser.h"
#include <fstream>
#include <iostream>

xml_parser::xml_parser(){}
xml_parser::~xml_parser(){}

std::vector<std::shared_ptr<level> > xml_parser::parse_game(std::string &filepath){
	uint32 num_levels = 0;
	std::vector<std::string> *files;
	std::vector<std::shared_ptr<level> > * game_levels = new std::vector<std::shared_ptr<level> >();

	std::ifstream in_file(filepath);
	std::string tag;
	if(in_file.is_open()){
		files = retrieve_files(in_file);
		in_file.close();
		uint32 num_files = files->size();
		for(uint32 c = 0; c < num_files; c++){
			game_levels->push_back(parse_level((*files)[c]));
		}
	}
	else{
		std::cerr << "Could not open file" << std::endl;
		std::exit(1);
	}
	return game_levels;
}



std::vector<std::string> * xml_parser::retrieve_files(std::ifstream &in_file){
	std::vector<std::string> * files = new std::vector<std::string>();
	bool count_flag = false;
	std::string tag;
	std::string search_str = "";
	uint32 count = 0;
	uint32 num_levels = 0;
	std::cout << "Hello Segfault" << std::endl;
	while(!in_file.eof() || count <= num_levels){
		if(in_file.eof()){
			in_file.clear();
			in_file.seekg(in_file.beg);
		}
		std::cout << "FEED_1_" << std::endl;
		in_file /*>> std::noskipws*/ >> tag;
		tag = trim_ws(tag);
		if(count_flag && count <= num_levels){
			search_str = "<Level_" + std::to_string(count) + ">";
		}
		else if(count > num_levels){
			break;
		}
		// Time to search for tags.
		if(tag.find("<Level_Count>") == 0 && !count_flag){
			num_levels = parse_level_count(in_file, tag);
			std::cout << "NUMLEVELS\t" << num_levels << std::endl;
			count_flag = true;
			count++;
		}
		else if(count_flag && tag.find(search_str) == 0 && count <= num_levels){
			files->push_back(parse_level_file(in_file, tag, search_str));
			std::cout << "FILE:\t" << (*files)[0] << std::endl;
			count++;
		}
	}
	return files;
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
	std::cout << "Inside before err" << std::endl;
	uint32 search_length = search_tag.size();
	std::string lvl_file_path;

	std::cout << "TAG:\t" << tag << std::endl;
	std::cout << "Search\t" << search_tag << std::endl;

	std::string end_tag = "</" + search_tag.substr(1,search_length);
	if(tag.size() == search_length){
		std::string str;
		file >> str;
		str = trim_ws(str);
		int end_tag_loc = str.find(end_tag);
		if(end_tag_loc != -1){
			std::string file_name = str.substr(0, (unsigned) end_tag_loc);
			file_name = trim_ws(file_name);
			return file_name;
		}
		else{
			std::string tmp;
			file >> tmp; // Grab the end tag loc
			return str;
		}
	}
	else{
		uint32 str_size = tag.size();
		std::string sub_str = tag.substr(search_length, str_size);
		sub_str = trim_ws(sub_str);
		int end_tag_loc = sub_str.find(end_tag);
		if(end_tag_loc != -1){
			std::string file_name = sub_str.substr(0, (unsigned) end_tag_loc);
			file_name = trim_ws(file_name);
			return file_name;
		}
		else{
			std::string tmp;
			file >> tmp; // Grab the end tag loc
			return sub_str;
		}
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
