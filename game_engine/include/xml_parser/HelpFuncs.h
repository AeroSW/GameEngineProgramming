#ifndef HELPFUNCS_H_
#define HELPFUNCS_H_

#include <string>
#include <fstream>

std::string trim_ws(const std::string &str);
std::string parse_by_tags(std::ifstream &file, std::string &line, std::string &beg_tag, std::string &end_tag);

#endif