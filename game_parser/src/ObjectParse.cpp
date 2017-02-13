#include "ObjectParse.h"
#include "HelpFuncs.h"

std::string object_parser::beg_tag = "<object>";
std::string object_parser::end_tag = "</object>";
std::string mesh_parser::beg_tag = "<mesh>";
std::string mesh_parser::end_tag = "</mesh>";
std::string mat_parser::beg_tag = "<mat>";
std::string mat_parser::end_tag = "</mat>";
std::string object_parser::parse_tag(std::ifstream &file, std::string &line){
	return parse_by_tags(file, line, beg_tag, end_tag);
}
std::string mesh_parser::parse_tag(std::ifstream &file, std::string &line){
	return parse_by_tags(file, line, beg_tag, end_tag);
}
std::string mat_parser::parse_tag(std::ifstream &file, std::string &line){
	return parse_by_tags(file, line, beg_tag, end_tag);
}
std::string object_parser::get_beg_tag(){
	return beg_tag;
}
std::string object_parser::get_end_tag(){
	return end_tag;
}
std::string mesh_parser::get_beg_tag(){
	return beg_tag;
}
std::string mesh_parser::get_end_tag(){
	return end_tag;
}
std::string mat_parser::get_beg_tag(){
	return beg_tag;
}
std::string mat_parser::get_end_tag(){
	return end_tag;
}