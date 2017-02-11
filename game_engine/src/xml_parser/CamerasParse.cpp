#include "CamerasParse.h"
#include "HelpFuncs.h"

std::string cams_parser::beg_tag = "<cameras>";
std::string cams_parser::end_tag = "</cameras>";
std::string cams_parser::parse_tag(std::ifstream &file, std::string &line){
	return parse_by_tags(file, line, beg_tag, end_tag);
}