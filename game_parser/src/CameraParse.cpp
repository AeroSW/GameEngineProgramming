#include "CameraParse.h"
#include "HelpFuncs.h"

std::string cam_parser::beg_tag = "<camera>";
std::string cam_parser::end_tag = "</camera>";
std::string target_parser::beg_tag = "<target>";
std::string target_parser::end_tag = "</target>";
std::string clip_parser::beg_tag = "<clip>";
std::string clip_parser::end_tag = "</clip>";
std::string cam_parser::parse_tag(std::ifstream &file, std::string &line){
	return parse_by_tags(file, line, beg_tag, end_tag);
}
std::string target_parser::parse_tag(std::ifstream &file, std::string &line){
	return parse_by_tags(file, line, beg_tag, end_tag);
}
std::string clip_parser::parse_tag(std::ifstream &file, std::string &line){
	return parse_by_tags(file, line, beg_tag, end_tag);
}
std::string cam_parser::get_beg_tag(){
	return beg_tag;
}
std::string cam_parser::get_end_tag(){
	return end_tag;
}
std::string clip_parser::get_beg_tag(){
	return beg_tag;
}
std::string clip_parser::get_end_tag(){
	return end_tag;
}
std::string target_parser::get_beg_tag(){
	return beg_tag;
}
std::string target_parser::get_end_tag(){
	return end_tag;
}