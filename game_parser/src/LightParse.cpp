#include "LightParse.h"
#include "HelpFuncs.h"

std::string light_parser::beg_tag = "<light>";
std::string light_parser::end_tag = "</light>";
std::string light_parser::parse_tag(std::ifstream &file, std::string &line){
	return parse_by_tags(file, line, beg_tag, end_tag);
}
std::string light_parser::get_beg_tag(){
	return beg_tag;
}
std::string light_parser::get_end_tag(){
	return end_tag;
}