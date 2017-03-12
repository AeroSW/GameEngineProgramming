// Functions.cpp
#include "Functions.h"

#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <sstream>

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

void trim(std::string &str){
	ltrim(str);
	rtrim(str);
}

void ltrim(std::string &str){
	s.erase(s.begin(), std::find_if(s.begin(), s.end(),
			std::not1(std::ptr_fun<int, int>(std::isspace))));
}

void rtrim(std::string &str){
	s.erase(std::find_if(s.rbegin(), s.rend(),
			std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}