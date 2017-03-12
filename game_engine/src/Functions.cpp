// Functions.cpp
#include "Functions.h"

std::vector<double> parse_vector(const std::string &vect_str){
	static char delim = ',';
	std::stringstream ss;
	ss.str(vect_str);
	std::string buffer;
	std::vector<double> value;
	while (std::getline(ss, buffer, delim)) {
		value.push_back(std::stod(buffer));
	}
	return value;
}

std::vector<float> parse_fvector(const std::string &vect_str){
	static char delim = ',';
	std::stringstream ss;
	ss.str(vect_str);
	std::string buffer;
	std::vector<float> value;
	while (std::getline(ss, buffer, delim)) {
		value.push_back(std::stof(buffer));
	}
	return value;
}
