// Functions.cpp
#include "Functions.h"

#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
#include <sstream>

#include <codecvt>

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

void ltrim(std::string &s){
	s.erase(s.begin(), std::find_if(s.begin(), s.end(),
			std::not1(std::ptr_fun<int, int>(std::isspace))));
}

void rtrim(std::string &s){
	s.erase(std::find_if(s.rbegin(), s.rend(),
			std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

std::wstring string2wstring(const std::string &str){
	typedef std::codecvt_utf8<wchar_t> convert_type;
	std::wstring_convert<convert_type, wchar_t> converter;
	return converter.from_bytes(str);
}
