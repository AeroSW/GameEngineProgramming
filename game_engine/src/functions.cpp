// Functions.cpp
#include "include/functions.h"

#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

#include <codecvt>

void asw::trim(std::string &str){
	leftTrim(str);
	rightTrim(str);
}

void asw::leftTrim(std::string &s){
	s.erase(s.begin(), std::find_if(s.begin(), s.end(),
			std::not1(std::ptr_fun<int, int>(std::isspace))));
}

void asw::rightTrim(std::string &s){
	s.erase(std::find_if(s.rbegin(), s.rend(),
			std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

std::wstring asw::stringToWideString(const std::string &str){
	typedef std::codecvt_utf8<wchar_t> convert_type;
	std::wstring_convert<convert_type, wchar_t> converter;
	return converter.from_bytes(str);
}
