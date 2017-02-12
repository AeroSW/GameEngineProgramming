#ifndef HELPFUNCS_H_
#define HELPFUNCS_H_

#include <string>
#include <vector>
#include <fstream>

std::string trim_ws(const std::string &str);
std::string parse_by_tags(std::ifstream &file, std::string &line, std::string &beg_tag, std::string &end_tag);
std::vector<double> parse_vector(const std::string &vect_str);

#endif