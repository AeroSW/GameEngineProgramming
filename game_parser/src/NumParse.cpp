#include "NumParse.h"
#include "HelpFuncs.h"

std::string num_parser::beg_tag = "<num>";
std::string num_parser::end_tag = "</num>";
std::string num_parser::parse_tag(std::ifstream &file, std::string &line){
	return parse_by_tags(file, line, beg_tag, end_tag);
}
std::string num_parser::get_beg_tag(){
	return beg_tag;
}
std::string num_parser::get_end_tag(){
	return end_tag;
}