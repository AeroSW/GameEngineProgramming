#include "TransformsParse.h"
#include "HelpFuncs.h"

std::string transforms_parser::beg_tag = "<transforms>";
std::string transforms_parser::end_tag = "</transforms>";
std::string trans_parser::beg_tag = "<trans>";
std::string trans_parser::end_tag = "</trans>";
std::string rotat_parser::beg_tag = "<rotat>";
std::string rotat_parser::end_tag = "</rotat>";
std::string scale_parser::beg_tag = "<scale>";
std::string scale_parser::end_tag = "</scale>";
// Constructors
transforms_parser::transforms_parser(){}
trans_parser::trans_parser(){}
rotat_parser::rotat_parser(){}
scale_parser::scale_parser(){}

// parse_tag(s)
std::string transforms_parser::parse_tag(std::ifstream &file, std::string &line){
	return parse_by_tags(file, line, beg_tag, end_tag);
}
std::string trans_parser::parse_tag(std::ifstream &file, std::string &line){
	return parse_by_tags(file, line, beg_tag, end_tag);
}
std::string rotat_parser::parse_tag(std::ifstream &file, std::string &line){
	return parse_by_tags(file, line, beg_tag, end_tag);
}
std::string scale_parser::parse_tag(std::ifstream &file, std::string &line){
	return parse_by_tags(file, line, beg_tag, end_tag);
}